/*
motor_controller.cpp
This exercise consists in design:
- a 1-motor speed controller,
- with the ability to switch speed/position controller,
- with the ability to switch between `PathFollow` and `LineFollow`.
*/

// motor_controller.cpp
// Single-file example: 1-motor controller with switchable Speed/Position control
// and switchable PathFollow / LineFollow strategies.
// Compile: g++ -std=c++17 motor_controller.cpp -O2 -o motor_controller
// Run: ./motor_controller

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <cassert>

// --------------------------- Utility: PID ---------------------------
struct PID {
    double kp{0}, ki{0}, kd{0};
    double integrator{0};
    double last_error{0};
    double integrator_limit{1e6};

    PID() = default;
    PID(double Kp, double Ki, double Kd) : kp(Kp), ki(Ki), kd(Kd) {}

    double reset() {
        integrator = 0;
        last_error = 0;
        return 0;
    }

    double update(double error, double dt) {
        if (dt <= 0) return 0;
        integrator += error * dt;
        // anti-windup
        if (integrator > integrator_limit) integrator = integrator_limit;
        if (integrator < -integrator_limit) integrator = -integrator_limit;
        double derivative = (error - last_error) / dt;
        last_error = error;
        return kp * error + ki * integrator + kd * derivative;
    }
};

// --------------------------- Simple Motor Model ---------------------------
// A trivial point-mass like motor model: torque -> acceleration of rotor
struct Motor {
    double position{0};   // rad or m (abstract)
    double velocity{0};   // rad/s or m/s
    double torque_constant{1.0}; // relates control output to torque
    double damping{0.1};  // viscous friction
    double inertia{1.0};  // rotational inertia

    // Apply a control effort (interpreted as torque) for dt seconds
    void apply_torque(double torque, double dt) {
        // simple dynamics: J * dv/dt = torque - b*v
        double accel = (torque - damping * velocity) / inertia;
        velocity += accel * dt;
        position += velocity * dt;
    }
};

// --------------------------- Controller Interfaces ---------------------------
struct IController {
    virtual ~IController() = default;
    virtual void setTarget(double target) = 0; // speed (m/s) or position (m)
    virtual void update(Motor &m, double dt) = 0; // compute & apply command to motor
};

// Speed controller: single-loop PID on velocity
class SpeedController : public IController {
public:
    SpeedController() { speed_pid = PID(5.0, 1.0, 0.01); }
    void setTarget(double target) override { target_speed = target; }
    void update(Motor &m, double dt) override {
        double error = target_speed - m.velocity;
        double effort = speed_pid.update(error, dt);
        // Here effort is interpreted directly as torque
        m.apply_torque(effort * m.torque_constant, dt);
    }
private:
    double target_speed{0};
    PID speed_pid;
};

// Position controller: outer PID on position -> desired speed -> inner speed PID cascaded
class PositionController : public IController {
public:
    PositionController() {
        pos_pid = PID(8.0, 0.0, 0.1);   // outer loop
        inner_speed_pid = PID(6.0, 0.5, 0.02); // used to compute final torque from speed error
    }
    void setTarget(double target) override { target_position = target; }
    void update(Motor &m, double dt) override {
        double pos_error = target_position - m.position;
        // outer loop produces a desired speed (simple P or PID)
        double desired_speed = pos_pid.update(pos_error, dt);
        // limit desired speed
        double max_speed = 10.0;
        if (desired_speed > max_speed) desired_speed = max_speed;
        if (desired_speed < -max_speed) desired_speed = -max_speed;
        // inner loop: speed tracking -> torque
        double speed_error = desired_speed - m.velocity;
        double effort = inner_speed_pid.update(speed_error, dt);
        m.apply_torque(effort * m.torque_constant, dt);
    }
private:
    double target_position{0};
    PID pos_pid;
    PID inner_speed_pid;
};

// --------------------------- Following Strategies --------------------------- 

struct IFollowStrategy {
    virtual ~IFollowStrategy() = default;
    // strategy updates controller target and may do other bookkeeping
    virtual void step(Motor &m, IController &ctrl, double dt) = 0;
};

// Very simple LineFollow: follow a 1D line represented by positions along x-axis.
// The "line" here is simply a segment from x0 to x1; the strategy will set a target position
// marching along the line at a commanded path speed.
class LineFollow : public IFollowStrategy {
public:
    LineFollow(double x0, double x1, double path_speed)
    : a(x0), b(x1), speed(path_speed) {
        assert(a != b && "line endpoints must differ");
        direction = (b > a) ? 1.0 : -1.0;
        current_target = a;
    }

    void step(Motor &m, IController &ctrl, double dt) override {
        // advance current_target along the line
        double travel = speed * dt * direction;
        current_target += travel;
        // clamp to segment
        if (direction > 0 && current_target > b) current_target = b;
        if (direction < 0 && current_target < b) current_target = b;
        // we assume the controller is a position controller (if speed controller, we send speed)
        // We'll probe with dynamic_cast to decide which to set.
        if (auto *pc = dynamic_cast<PositionController*>(&ctrl)) {
            pc->setTarget(current_target);
        } else {
            // controller is speed-type: set speed in sign towards b
            ctrl.setTarget(speed * direction);
        }
    }

private:
    double a{0}, b{1};
    double speed{1};
    double direction{1};
    double current_target{0};
};

// PathFollow: follow a list of waypoints (1D positions). Moves from waypoint to waypoint.
class PathFollow : public IFollowStrategy {
public:
    PathFollow(std::vector<double> waypoints, double path_speed)
    : pts(std::move(waypoints)), speed(path_speed) {
        assert(!pts.empty());
        idx = 0;
    }

    void step(Motor &m, IController &ctrl, double dt) override {
        if (idx >= pts.size()) return; // finished
        double target_pos = pts[idx];
        // If controller is position controller, set the waypoint. If speed, set speed towards it.
        if (auto *pc = dynamic_cast<PositionController*>(&ctrl)) {
            pc->setTarget(target_pos);
            // consider waypoint reached when within tolerance
            double tol = 0.02;
            if (std::abs(m.position - target_pos) < tol && std::abs(m.velocity) < 0.05) {
                idx++;
            }
        } else {
            double dir = (target_pos > m.position) ? 1.0 : -1.0;
            ctrl.setTarget(speed * dir);
            // simple check: if we passed waypoint, advance
            if ((dir>0 && m.position >= target_pos) || (dir<0 && m.position <= target_pos)) idx++;
        }
    }

private:
    std::vector<double> pts;
    size_t idx{0};
    double speed{1.0};
};

// --------------------------- Controller Manager ---------------------------
// Keeps a single active controller (speed or position) and a following strategy.
class ControllerManager {
public:
    enum class Mode { Speed, Position };

    ControllerManager() {
        // default: speed controller
        setMode(Mode::Speed);
        follow_strategy = nullptr;
    }

    void setMode(Mode m) {
        mode = m;
        if (mode == Mode::Speed) {
            controller = std::make_unique<SpeedController>();
        } else {
            controller = std::make_unique<PositionController>();
        }
    }

    Mode getMode() const { return mode; }

    void setFollowStrategy(std::unique_ptr<IFollowStrategy> strat) {
        follow_strategy = std::move(strat);
    }

    IController &getController() { return *controller; }

    void update(Motor &motor, double dt) {
        if (follow_strategy) follow_strategy->step(motor, *controller, dt);
        controller->update(motor, dt);
    }

private:
    Mode mode{Mode::Speed};
    std::unique_ptr<IController> controller;
    std::unique_ptr<IFollowStrategy> follow_strategy;
};

// --------------------------- Demo / Main ---------------------------
int main() {
    Motor motor;
    motor.inertia = 0.5;
    motor.damping = 0.05;
    motor.torque_constant = 1.0;

    ControllerManager mgr;

    // Start with Position mode and a simple path
    mgr.setMode(ControllerManager::Mode::Position);
    std::vector<double> waypoints = {0.0, 2.0, -1.0, 0.5};
    mgr.setFollowStrategy(std::make_unique<PathFollow>(waypoints, 1.0));

    double sim_t = 0.0;
    double dt = 0.01;
    double end_t = 12.0;

    std::cout << "time, position, velocity, controller_mode" << std::endl;
    while (sim_t < end_t) {
        // switch mode mid-run as a demonstration
        if (sim_t > 5.0 && mgr.getMode() == ControllerManager::Mode::Position) {
            std::cout << "-- switching to Speed mode at t=" << sim_t << "s\n";
            mgr.setMode(ControllerManager::Mode::Speed);
            // switch to line follow for speed demo
            mgr.setFollowStrategy(std::make_unique<LineFollow>(0.0, 3.0, 1.5));
        }

        mgr.update(motor, dt);

        // print every 0.05s
        if (static_cast<int>(sim_t*100) % 5 == 0) {
            std::cout << sim_t << ", " << motor.position << ", " << motor.velocity << ", "
                      << (mgr.getMode() == ControllerManager::Mode::Speed ? "Speed" : "Position") << std::endl;
        }

        sim_t += dt;
    }

    std::cout << "Simulation finished." << std::endl;
    return 0;
}

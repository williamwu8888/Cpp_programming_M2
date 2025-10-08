#include <iostream>
#include <iomanip>   // for std::setprecision
#include <vector>    // for std::vector
using namespace std;

// Exercise 3

// std::cin, std::cout  -> https://en.cppreference.com/w/cpp/io/basic_istream
// std::setprecision    -> https://en.cppreference.com/w/cpp/io/manip/setprecision
// while (cin >> grade) -> https://en.cppreference.com/w/cpp/io/basic_istream/operator_gtgt
// std::vector          -> https://en.cppreference.com/w/cpp/container/vector

int main() {
    string name;
    double exam, finalExam;
    vector<double> homework;
    double grade, sum = 0.0;

    cout << "Enter the student's name: ";
    cin >> name;

    cout << "Enter the mid-term and final exam grades: ";
    cin >> exam >> finalExam;

    // Without homework
    double result_no_hw = 0.4 * exam + 0.6 * finalExam;
    cout << "Average (exam + final exam): " << result_no_hw << endl;

    // Set output precision
    cout << fixed << setprecision(4);

    // Add homework grades
    cout << "Enter homework grades (Ctrl+D to end): ";

    // Read until end of input (Ctrl+D)
    while (cin >> grade) {
        homework.push_back(grade);
    }
    // If there are homework grades, compute the average
    double homework_avg = 0.0;
    if (!homework.empty()) {
        for (double h : homework) sum += h;
        homework_avg = sum / homework.size();
    } else {
        cout << "\nNo homework grades entered — homework average set to 0." << endl;
    }

    // Compute the final average
    double final_grade = 0.2 * exam + 0.4 * finalExam + 0.4 * homework_avg;

    cout << "\nStudent: " << name << endl;
    cout << "First exam grade: " << exam << endl;
    cout << "Final exam grade: " << finalExam << endl;
    cout << "Homework average: " << homework_avg << endl;
    cout << "Final EU average: " << final_grade << endl;

    return 0;
}

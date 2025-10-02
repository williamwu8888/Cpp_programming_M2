# Copilot Instructions for AI Coding Agents

## Project Structure & Philosophy
- This repository is a personal C programming learning environment, organized for progressive mastery.
- Key directories:
  - `_lectures/`: PDF lecture slides and reference materials
  - `_notebooks/`: Jupyter notebooks with code, explanations, and diagrams
  - `_practicals/`: Hands-on exercises, each in its own subfolder (e.g., `tp1_password`, `tp2_ternary_logic`, `tp4_molecules`)
  - `labs/`: Standalone C++ exercises
  - Root: `test.c` (basic C demo), `README.md` (setup and overview)

## Build & Development Workflow
- **Primary build system:** VS Code tasks using MinGW-w64 GCC (`D:\mingw64\bin\gcc.exe`).
- **To build the active file:** Use the VS Code build task `C/C++: gcc.exe build active file` (Ctrl+Shift+B by default).
- **Each practical** may have its own `Makefile` for more complex builds (see e.g., `_practicals/tp1_password/files/Makefile`).
- **Debugging:** Use VS Code's built-in debugger, configured for MinGW-w64.
- **Testing:**
  - Unit tests are provided in `tests/` subfolders within each practical (e.g., `TestCase.cc`, `doctest.h`, `catch.hpp`).
  - Run tests using the provided Makefile or by compiling test files directly with GCC.

## Project-Specific Conventions
- **C and C++ separation:**
  - C exercises are in `.c` files; C++ exercises and OOP content are in `.cpp`/`.cc` files (see `labs/` and some practicals).
- **Header organization:**
  - Headers for practicals are in `headers/` subfolders (e.g., `Atom.hh`, `ExpLog.hh`).
- **Naming:**
  - Follow the naming conventions in the provided exercises and match class/function names to those in the problem statements.
- **Test frameworks:**
  - `doctest.h` and `catch.hpp` are used for C++ unit testing; see test files for usage patterns.

## Integration & External Dependencies
- No external dependencies beyond MinGW-w64 and standard C/C++ libraries.
- All test frameworks are vendored in the repo (no need to install separately).

## Examples
- To build and run a test for `tp1_password`:
  1. `cd _practicals/tp1_password/files`
  2. `make` (or use the VS Code build task for individual files)
  3. Run the resulting executable(s) in the `tests/` directory
- To add a new exercise, follow the structure of existing practicals: create a new subfolder, add a `Makefile`, and place source, header, and test files accordingly.

## Key Files & Directories
- `_practicals/tp1_password/files/Makefile` — Example of a practical's build system
- `_practicals/tp1_password/files/tests/doctest.h` — Vendored C++ test framework
- `labs/CPP_2_exercise.cpp` — Example of a standalone C++ exercise
- `_notebooks/CPP_1.ipynb` — Example of a notebook with code and explanations

---
For any unclear conventions or missing documentation, consult the `README.md` or the structure of similar practicals. When in doubt, match the style and organization of existing files.

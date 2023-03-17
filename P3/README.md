# Compilers project 2023

## Requirements

- If using VSCode, C/C++ and CMake extensions by microsoft.
- A C compiler. Any should work fine.


- Make (which make in terminal)

or
- CMake 3.24 or better (bundled with CLion by default, see https://cmake.org/download/ for instructions if using VSCode).

### To configure:

#### VSCode:
- Make sure you have downloaded CMake. Open "how to install for command line" use and find the CMake path executable.
- Install Microsoft's C/C++ and CMake extensions.
- go to .vscode/settings.json and add fill the "cmake.cmakePath" field with your cmake executable path.
- Restart VSCode. It should now idenfity the project as a CMake project.
#### CLion:


### To compile the project:
### CMake
#### VSCode:
- open the CMake menu (left toolbar, looks like a folder with a triangle).
- search and build apps/gb_project.
#### CLion:
- Select gb_project in the build configuration menu (top left).
### Make
Execute the make command in the root directory of the project


### To run the project:
### CMake
- VSCode: use the launch button in the status bar of VSCode.
- CLion: use the run button at the top right menu of CLion.
### Make
Execute the binary in binaries/gb_project

## Limitations
The project runs best in CLion (linting, terminal output, cmake build configurations).
VSCode will not understand where the includes come from, but will compile them correctly.

### Additional information:
- https://code.visualstudio.com/docs/cpp/cmake-linux (step-by-step guide with images, plus CMake custom configurations).
- https://github.com/microsoft/vscode-cmake-tools/issues/685 (possible error in VSCode and how to fix it).
- https://stackoverflow.com/questions/49056000/all-of-my-json-files-have-problems-loading-reference-schema-from-schemastore-az (VSCode should work even without fixing this).
- https://www.jetbrains.com/help/clion/cmake-profile.html#CMakeProfileSwitcher (custom CMake configurations for CLion).

I can't guarantee it works on other IDEs (it should, it's a CMake project) nor can I give a guide on how to set them up properly (VSCode is already scuffed).
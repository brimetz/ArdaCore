# ArdaCore

[![GitLab Pipeline](https://gitlab.com/brimetz/ArdaCore/badges/main/pipeline.svg)](https://gitlab.com/brimetz/ArdaCore/-/pipelines)
![C++](https://img.shields.io/badge/-C++-00599C?logo=cplusplus&logoColor=white)
![CI/CD](https://img.shields.io/badge/-CI%2FCD-0A0FFF?logo=azuredevops&logoColor=white)

Custom C++ Minimal Library to learn programming things.
I will use it in other project when the time comes.

## Build

To locally build the project with CMake and Ninja :
```bash
mkdir -p build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Tests

To launch the unit tests:
```bash
cd build
ctest --output-on-failure
```

## Project folders
ArdaCore/
├── ArdaCore/        # Code source principal
├── Tests/           # Tests unitaires
├── CMakeLists.txt   # Fichier CMake principal
└── README.md        # Ce fichier

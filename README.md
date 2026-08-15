# Student Portal

Student Portal is a command-line C++ application for managing a student's academic account. It started as a small legacy program and is being rebuilt into a full portal with login, profile, dashboard, and settings.

## Features

- Sign in and sign out with a local user store
- View and edit a student profile
- See enrolled courses, GPA, and announcements on a dashboard
- Change password and notification preferences in settings

## Prerequisites

- A C++ compiler that supports C++17 (`g++` from MinGW-w64, MSYS2, or WSL)
- Git
- Make (optional; `mingw32-make` on Windows if GNU Make is not on PATH)

## Build

From the `student-portal` directory:

```bash
make
```

Or compile directly:

```bash
g++ -std=c++17 -Iinclude -o student-portal src/main.cpp src/student.cpp src/student_portal.cpp src/console_io.cpp src/login.cpp
```

This produces `student-portal.exe` on Windows, or `student-portal` on Linux/macOS. The `-Iinclude` flag lets source files keep `#include "student.h"` after the header move. Object files and binaries are ignored by Git.

## Run

After a successful build:

```bash
./student-portal
```

On Windows Command Prompt you can also run `student-portal.exe`. Sign in before viewing or editing a record. Sample accounts created in `users.dat` on first run:

- `nehal` / `portal123`
- `student` / `student123`

## Repository layout

```text
student-portal/
  include/
    student.h      Student data model
    portal.h       Portal application class
    login.h        Session types and user-store login
    console_io.h   Shared console input helpers
  src/
    main.cpp            Program entry point
    student.cpp         Student field validation
    student_portal.cpp  Menu loop and profile actions
    login.cpp           Credential checks against users.dat
    console_io.cpp      Console input helpers
  Makefile         Build rules
  README.md        Setup and usage guide
  .gitignore       Build artifacts, IDE files, and runtime data
```

Headers live in `include/` and implementations live in `src/` so the public API stays separate from the build sources.

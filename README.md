# Student Portal

Student Portal is a command-line C++ application for managing a student's academic account. This build is release candidate 2, ready for the annotated v1.0 tag after a final docs pass.

## Features

- Sign in and sign out with a local user store
- View and edit a student profile
- See enrolled courses, GPA, and announcements on a dashboard
- Change password and notification preferences in settings
- Open Help for an about blurb and a command list

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
g++ -std=c++17 -Iinclude -o student-portal src/main.cpp src/student.cpp src/student_portal.cpp src/console_io.cpp src/login.cpp src/profile.cpp src/dashboard.cpp src/settings.cpp src/help.cpp
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

Three failed sign-in attempts lock the login for the rest of that program run. Restart the portal to try again.

Menu option 14 opens Help, which works without signing in.

## Repository layout

```text
student-portal/
  include/
    student.h      Student data model
    portal.h       Portal application class
    login.h        Session types and user-store login
    profile.h      Profile records and field validation
    dashboard.h    Courses, GPA, and announcements
    settings.h     Notifications, theme, and password change
    help.h         About text and command list
    console_io.h   Shared console input helpers
  src/
    main.cpp            Program entry point
    student.cpp         Student field validation
    student_portal.cpp  Menu loop and profile actions
    login.cpp           Credential checks against users.dat
    profile.cpp         Profile load/save and validation
    dashboard.cpp       Enrollment list, GPA, and announcements
    settings.cpp        Settings persistence and toggles
    help.cpp            Help about and command list
    console_io.cpp      Console input helpers
  Makefile         Build rules
  README.md        Setup and usage guide
  .gitignore       Build artifacts, IDE files, and runtime data
```

Headers live in `include/` and implementations live in `src/` so the public API stays separate from the build sources.

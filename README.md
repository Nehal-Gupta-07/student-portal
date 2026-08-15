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

## Build

From the `student-portal` directory:

```bash
g++ -std=c++17 -o student-portal main.cpp student.cpp portal.cpp
```

This produces `student-portal.exe` on Windows, or `student-portal` on Linux/macOS. Object files and binaries are ignored by Git.

## Run

After a successful build:

```bash
./student-portal
```

On Windows Command Prompt you can also run `student-portal.exe`. The portal loads a sample student record and opens a menu to view or edit profile fields.

## Repository layout

```text
student-portal/
  main.cpp       Program entry point
  student.h      Student data model
  student.cpp    Student field validation
  portal.h       Portal application class
  portal.cpp     Menu loop and profile actions
  README.md      Setup and usage guide
  .gitignore     Build artifacts, IDE files, and runtime data
```

Source files will later move into `src/` and `include/` as the portal grows.

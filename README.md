# University Management System

## Overview

This project is a simplified University Management System developed using C++ with Object-Oriented Programming (OOP) principles, file handling for data storage, and Raylib for the user interface. It provides functionalities to manage students, courses, and faculty members, including adding, updating, deleting, and displaying information. The project also includes a login system with different functionalities for admin and student users.

## Features

- **User Authentication**:
  - Admin: Username - `admin`, Password - `admin`
  - Student: Username - `student`, Password - `student`
- **Admin Functionalities**:
  - Manage Students: Add, Update, Delete, Display, Take Attendance, Display Attendance
  - Manage Courses: Add, Update, Delete, Display
  - Manage Faculty: Add, Update, Delete, Display
- **Student Functionalities**:
  - View Student Information
  - View Course Information
  - View Faculty Information
  - View Attendance

## Requirements

- MinGW-w64 (for Windows)
- Visual Studio Code

## Building the Project

1. **Clone the repository**:
    ```sh
    git clone <repository_url>
    cd <project_directory>
    ```

5. **Build the project**:
    - Open the terminal in Visual Studio Code.
    ```sh
    cd build
    mingw32-make
    ```

## Running the Project

1. **Navigate to the build directory**:
    ```sh
    cd build
    ```

2. **Run the executable**:
    ```sh
    ./ums
    ```
    OR, Open the `ums.exe` file inside the `build` folder.

## Usage

### Login

- **Admin**:
  - Username: `admin`
  - Password: `admin`
- **Student**:
  - Username: `student`
  - Password: `student`

### Admin Menu

- **Manage Students**:
  - Add Student
  - Update Student
  - Delete Student
  - Display Students
  - Take Attendance
  - Display Attendance
- **Manage Courses**:
  - Add Course
  - Update Course
  - Delete Course
  - Display Courses
- **Manage Faculty**:
  - Add Faculty
  - Update Faculty
  - Delete Faculty
  - Display Faculty

### Student Menu

- View Students
- View Courses
- View Faculty
- View Attendance

## Contributing

1. Fork the repository.
2. Create a new branch: `git checkout -b feature-branch`
3. Make your changes and commit them: `git commit -m 'Add new feature'`
4. Push to the branch: `git push origin feature-branch`
5. Submit a pull request.

## License

This project is licensed under the MIT License.

## Acknowledgments

- Thanks to the `raylib` developers for providing an easy-to-use library for game and graphical application development.
- Special thanks to the C++ community for their valuable resources and support.

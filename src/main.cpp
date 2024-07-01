#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "FileHandler.h"
#include <fstream>
#include <map>

enum Screen {
    LOGIN,
    MENU,
    STUDENT_MENU,
    COURSE_MENU,
    FACULTY_MENU,
    ADD_STUDENT,
    DISPLAY_STUDENTS,
    UPDATE_STUDENT,
    DELETE_STUDENT,
    ADD_COURSE,
    DISPLAY_COURSES,
    UPDATE_COURSE,
    DELETE_COURSE,
    ADD_FACULTY,
    DISPLAY_FACULTY,
    UPDATE_FACULTY,
    DELETE_FACULTY,
    TAKE_ATTENDANCE,
    DISPLAY_ATTENDANCE
};

bool Button(Rectangle rect, const char* text) {
    bool clicked = false;
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clicked = true;
        DrawRectangleRec(rect, LIGHTGRAY);
    } else {
        DrawRectangleRec(rect, GRAY);
    }
    DrawText(text, rect.x + 10, rect.y + 10, 20, BLACK);
    return clicked;
}

void TextInput(char* buffer, int bufferSize, Rectangle rect, bool active) {
    DrawRectangleRec(rect, active ? LIGHTGRAY : DARKGRAY);
    DrawText(buffer, rect.x + 5, rect.y + 5, 20, BLACK);

    if (active) {
        int key = GetCharPressed();
        while (key > 0) {
            int length = strlen(buffer);
            if (length < bufferSize - 1) {
                buffer[length] = (char)key;
                buffer[length + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            int length = strlen(buffer);
            if (length > 0) buffer[length - 1] = '\0';
        }
    }
}

bool PasswordInput(char* buffer, int bufferSize, Rectangle rect, bool active) {
    DrawRectangleRec(rect, active ? LIGHTGRAY : DARKGRAY);
    std::string masked(buffer, strlen(buffer));
    std::fill(masked.begin(), masked.end(), '*');
    DrawText(masked.c_str(), rect.x + 5, rect.y + 5, 20, BLACK);

    if (active) {
        int key = GetCharPressed();
        while (key > 0) {
            int length = strlen(buffer);
            if (length < bufferSize - 1) {
                buffer[length] = (char)key;
                buffer[length + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            int length = strlen(buffer);
            if (length > 0) buffer[length - 1] = '\0';
        }
    }
    return true;
}

// Use nested maps to track attendance by date and student ID
std::map<std::string, std::map<std::string, bool>> attendance; // date -> (student ID -> present)

char attendanceDate[11] = {0}; // Format: YYYY-MM-DD
bool dateActive = false;

// Add a function to input dates
void DateInput(char* buffer, int bufferSize, Rectangle rect, bool active) {
    DrawRectangleRec(rect, active ? LIGHTGRAY : DARKGRAY);
    DrawText(buffer, rect.x + 5, rect.y + 5, 20, BLACK);

    if (active) {
        int key = GetCharPressed();
        while (key > 0) {
            int length = strlen(buffer);
            if (length < bufferSize - 1) {
                buffer[length] = (char)key;
                buffer[length + 1] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            int length = strlen(buffer);
            if (length > 0) buffer[length - 1] = '\0';
        }
    }
}


void LoadAttendance(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string date, id;
        bool present;
        while (file >> date >> id >> present) {
            attendance[date][id] = present;
        }
        file.close();
    }
}

void SaveAttendance(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& dateEntry : attendance) {
            for (const auto& entry : dateEntry.second) {
                file << dateEntry.first << " " << entry.first << " " << entry.second << "\n";
            }
        }
        file.close();
    }
}


bool Checkbox(Rectangle rect, bool checked) {
    bool clicked = false;
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicked = true;
            checked = !checked;
        }
    }

    DrawRectangleLinesEx(rect, 2, DARKGRAY);
    if (checked) {
        DrawLine(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, DARKGRAY);
        DrawLine(rect.x + rect.width, rect.y, rect.x, rect.y + rect.height, DARKGRAY);
    }
    return checked;
}

int main() {
    std::vector<Student> students = FileHandler::loadStudents("students.txt");
    std::vector<Course> courses = FileHandler::loadCourses("courses.txt");
    std::vector<Faculty> faculty = FileHandler::loadFaculty("faculty.txt");

    LoadAttendance("attendance.txt");

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "University Management System");

    Screen currentScreen = LOGIN;
    char inputId[10] = {0};
    char inputName[50] = {0};
    char username[20] = {0};
    char password[20] = {0};
    bool idActive = true;
    bool usernameActive = true;
    bool isAdmin = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGIN:
                DrawText("Login", 370, 50, 20, DARKGRAY);
                DrawText("Username:", 200, 150, 20, DARKGRAY);
                TextInput(username, sizeof(username), {400, 150, 200, 40}, usernameActive);
                DrawText("Password:", 200, 200, 20, DARKGRAY);
                PasswordInput(password, sizeof(password), {400, 200, 200, 40}, !usernameActive);

                if (Button({300, 300, 200, 40}, "Login")) {
                    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                        isAdmin = true;
                        currentScreen = MENU;
                    } else if (strcmp(username, "student") == 0 && strcmp(password, "student") == 0) {
                        isAdmin = false;
                        currentScreen = MENU;
                    } else {
                        DrawText("Invalid credentials", 300, 400, 20, RED);
                    }
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 150, 200, 40})) {
                        usernameActive = true;
                    } else if (CheckCollisionPointRec(mousePoint, {400, 200, 200, 40})) {
                        usernameActive = false;
                    }
                }
                break;

            case MENU:
                if (isAdmin) {
                    DrawText("Admin Menu", 350, 50, 20, DARKGRAY);
                    if (Button({300, 100, 200, 40}, "Students"))
                        currentScreen = STUDENT_MENU;
                    if (Button({300, 150, 200, 40}, "Courses"))
                        currentScreen = COURSE_MENU;
                    if (Button({300, 200, 200, 40}, "Faculty"))
                        currentScreen = FACULTY_MENU;
                    if (Button({300, 300, 200, 40}, "Logout"))
                        currentScreen = LOGIN;
                } else {
                    DrawText("Student Menu", 350, 50, 20, DARKGRAY);
                    if (Button({340, 150, 200, 40}, "Display Students")) currentScreen = DISPLAY_STUDENTS;
                    if (Button({340, 200, 200, 40}, "Display Courses")) currentScreen = DISPLAY_COURSES;
                    if (Button({340, 250, 200, 40}, "Display Faculty")) currentScreen = DISPLAY_FACULTY;
                    if (Button({340, 300, 200, 40}, "Display Attendance")) currentScreen = DISPLAY_ATTENDANCE;
                }
                break;

            case STUDENT_MENU:
                DrawText("Student Menu", 350, 50, 20, DARKGRAY);
                if (Button({300, 100, 200, 40}, "Add Student"))
                    currentScreen = ADD_STUDENT;
                if (Button({300, 150, 200, 40}, "Display Students"))
                    currentScreen = DISPLAY_STUDENTS;
                if (Button({300, 200, 200, 40}, "Update Student"))
                    currentScreen = UPDATE_STUDENT;
                if (Button({300, 250, 200, 40}, "Delete Student"))
                    currentScreen = DELETE_STUDENT;
                if (Button({300, 300, 200, 40}, "Take Attendance"))
                    currentScreen = TAKE_ATTENDANCE;
                if (Button({300, 350, 200, 40}, "Display Attendance"))
                    currentScreen = DISPLAY_ATTENDANCE;
                if (Button({300, 400, 200, 40}, "Back"))
                    currentScreen = MENU;
                break;

            case COURSE_MENU:
                DrawText("Course Menu", 350, 50, 20, DARKGRAY);
                if (Button({300, 100, 200, 40}, "Add Course"))
                    currentScreen = ADD_COURSE;
                if (Button({300, 150, 200, 40}, "Display Courses"))
                    currentScreen = DISPLAY_COURSES;
                if (Button({300, 200, 200, 40}, "Update Course"))
                    currentScreen = UPDATE_COURSE;
                if (Button({300, 250, 200, 40}, "Delete Course"))
                    currentScreen = DELETE_COURSE;
                if (Button({300, 300, 200, 40}, "Back"))
                    currentScreen = MENU;
                break;

            case FACULTY_MENU:
                DrawText("Faculty Menu", 350, 50, 20, DARKGRAY);
                if (Button({300, 100, 200, 40}, "Add Faculty"))
                    currentScreen = ADD_FACULTY;
                if (Button({300, 150, 200, 40}, "Display Faculty"))
                    currentScreen = DISPLAY_FACULTY;
                if (Button({300, 200, 200, 40}, "Update Faculty"))
                    currentScreen = UPDATE_FACULTY;
                if (Button({300, 250, 200, 40}, "Delete Faculty"))
                    currentScreen = DELETE_FACULTY;
                if (Button({300, 300, 200, 40}, "Back"))
                    currentScreen = MENU;
                break;

            case ADD_STUDENT:
                DrawText("Add Student", 350, 50, 20, DARKGRAY);
                DrawText("Student ID:", 200, 150, 20, DARKGRAY);
                TextInput(inputId, sizeof(inputId), {400, 150, 200, 40}, idActive);
                DrawText("Student Name:", 200, 200, 20, DARKGRAY);
                TextInput(inputName, sizeof(inputName), {400, 200, 200, 40}, !idActive);

                if (Button({300, 300, 200, 40}, "Save"))
                {
                    if (strlen(inputId) > 0 && strlen(inputName) > 0)
                    {
                        students.emplace_back(inputId, inputName);
                        FileHandler::saveStudents("students.txt", students);
                        // Initialization of attendance can be skipped or managed when dates are handled
                        memset(inputId, 0, sizeof(inputId));
                        memset(inputName, 0, sizeof(inputName));
                        currentScreen = MENU;
                    }
                }

                if (Button({300, 350, 200, 40}, "Back"))
                {
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 150, 200, 40}))
                    {
                        idActive = true;
                    }
                    else if (CheckCollisionPointRec(mousePoint, {400, 200, 200, 40}))
                    {
                        idActive = false;
                    }
                }
                break;

            case ADD_COURSE:
                DrawText("Add Course", 350, 50, 20, DARKGRAY);
                DrawText("Course ID:", 200, 150, 20, DARKGRAY);
                TextInput(inputId, sizeof(inputId), {400, 150, 200, 40}, idActive);
                DrawText("Course Name:", 200, 200, 20, DARKGRAY);
                TextInput(inputName, sizeof(inputName), {400, 200, 200, 40}, !idActive);

                if (Button({300, 300, 200, 40}, "Save")) {
                    if (strlen(inputId) > 0 && strlen(inputName) > 0) {
                        courses.emplace_back(inputId, inputName);
                        FileHandler::saveCourses("courses.txt", courses);
                        memset(inputId, 0, sizeof(inputId));
                        memset(inputName, 0, sizeof(inputName));
                        currentScreen = MENU;
                    }
                }

                if (Button({300, 350, 200, 40}, "Back")) {
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 150, 200, 40})) {
                        idActive = true;
                    } else if (CheckCollisionPointRec(mousePoint, {400, 200, 200, 40})) {
                        idActive = false;
                    }
                }
                break;

            case ADD_FACULTY:
                DrawText("Add Faculty", 350, 50, 20, DARKGRAY);
                DrawText("Faculty ID:", 200, 150, 20, DARKGRAY);
                TextInput(inputId, sizeof(inputId), {400, 150, 200, 40}, idActive);
                DrawText("Faculty Name:", 200, 200, 20, DARKGRAY);
                TextInput(inputName, sizeof(inputName), {400, 200, 200, 40}, !idActive);

                if (Button({300, 300, 200, 40}, "Save")) {
                    if (strlen(inputId) > 0 && strlen(inputName) > 0) {
                        faculty.emplace_back(inputId, inputName);
                        FileHandler::saveFaculty("faculty.txt", faculty);
                        memset(inputId, 0, sizeof(inputId));
                        memset(inputName, 0, sizeof(inputName));
                        currentScreen = MENU;
                    }
                }

                if (Button({300, 350, 200, 40}, "Back")) {
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 150, 200, 40})) {
                        idActive = true;
                    } else if (CheckCollisionPointRec(mousePoint, {400, 200, 200, 40})) {
                        idActive = false;
                    }
                }
                break;

            case DISPLAY_STUDENTS:
                DrawText("Student List", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < students.size(); i++) {
                    DrawText((students[i].getId() + " - " + students[i].getName()).c_str(), 200, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) currentScreen = MENU;
                break;

            case DISPLAY_COURSES:
                DrawText("Course List", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < courses.size(); i++) {
                    DrawText((courses[i].getId() + " - " + courses[i].getName()).c_str(), 200, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) currentScreen = MENU;
                break;

            case DISPLAY_FACULTY:
                DrawText("Faculty List", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < faculty.size(); i++) {
                    DrawText((faculty[i].getId() + " - " + faculty[i].getName()).c_str(), 200, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) currentScreen = MENU;
                break;

            case TAKE_ATTENDANCE:
                DrawText("Take Attendance", 350, 50, 20, DARKGRAY);
                DrawText("Date (YYYY-MM-DD):", 200, 100, 20, DARKGRAY);
                DateInput(attendanceDate, sizeof(attendanceDate), {400, 100, 200, 40}, dateActive);

                if (strlen(attendanceDate) == 10)
                { // Ensure date is entered
                    for (int i = 0; i < students.size(); i++)
                    {
                        DrawText((students[i].getId() + " - " + students[i].getName()).c_str(), 200, 150 + i * 30, 20, DARKGRAY);
                        attendance[attendanceDate][students[i].getId()] = Checkbox({500.0f, 150.0f + i * 30.0f, 20.0f, 20.0f}, attendance[attendanceDate][students[i].getId()]);
                    }
                }

                if (Button({300, 500, 200, 40}, "Save & Back"))
                {
                    SaveAttendance("attendance.txt");
                    memset(attendanceDate, 0, sizeof(attendanceDate));
                    currentScreen = MENU;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 100, 200, 40}))
                    {
                        dateActive = true;
                    }
                    else
                    {
                        dateActive = false;
                    }
                }
                break;

            case DISPLAY_ATTENDANCE:
                DrawText("Display Attendance", 350, 50, 20, DARKGRAY);
                DrawText("Date (YYYY-MM-DD):", 200, 100, 20, DARKGRAY);
                DateInput(attendanceDate, sizeof(attendanceDate), {400, 100, 200, 40}, dateActive);

                if (strlen(attendanceDate) == 10)
                { // Ensure date is entered
                    for (int i = 0; i < students.size(); i++)
                    {
                        DrawText((students[i].getId() + " - " + students[i].getName() + " - " + (attendance[attendanceDate][students[i].getId()] ? "Present" : "Absent")).c_str(), 200, 150 + i * 30, 20, DARKGRAY);
                    }
                }

                if (Button({300, 500, 200, 40}, "Back"))
                {
                    memset(attendanceDate, 0, sizeof(attendanceDate));
                    currentScreen = MENU;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, {400, 100, 200, 40}))
                    {
                        dateActive = true;
                    }
                    else
                    {
                        dateActive = false;
                    }
                }
                break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

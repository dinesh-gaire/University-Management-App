#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstring>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "FileHandler.h"

enum Screen { MENU, ADD_STUDENT, ADD_COURSE, ADD_FACULTY, DISPLAY_STUDENTS, DISPLAY_COURSES, DISPLAY_FACULTY };

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

int main() {
    std::vector<Student> students = FileHandler::loadStudents("students.txt");
    std::vector<Course> courses = FileHandler::loadCourses("courses.txt");
    std::vector<Faculty> faculty = FileHandler::loadFaculty("faculty.txt");

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "University Management System");

    Screen currentScreen = MENU;
    char inputId[10] = {0};
    char inputName[50] = {0};
    bool idActive = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case MENU:
                DrawText("University Management System", 190, 50, 20, DARKGRAY);
                if (Button({340, 150, 200, 40}, "Add Student")) currentScreen = ADD_STUDENT;
                if (Button({340, 200, 200, 40}, "Add Course")) currentScreen = ADD_COURSE;
                if (Button({340, 250, 200, 40}, "Add Faculty")) currentScreen = ADD_FACULTY;
                if (Button({340, 300, 200, 40}, "Display Students")) currentScreen = DISPLAY_STUDENTS;
                if (Button({340, 350, 200, 40}, "Display Courses")) currentScreen = DISPLAY_COURSES;
                if (Button({340, 400, 200, 40}, "Display Faculty")) currentScreen = DISPLAY_FACULTY;
                break;

            case ADD_STUDENT:
                DrawText("Add Student", 350, 50, 20, DARKGRAY);
                DrawText("Student ID:", 200, 150, 20, DARKGRAY);
                TextInput(inputId, sizeof(inputId), {400, 150, 200, 40}, idActive);
                DrawText("Student Name:", 200, 200, 20, DARKGRAY);
                TextInput(inputName, sizeof(inputName), {400, 200, 200, 40}, !idActive);

                if (Button({300, 300, 200, 40}, "Save")) {
                    if (strlen(inputId) > 0 && strlen(inputName) > 0) {
                        students.emplace_back(inputId, inputName);
                        FileHandler::saveStudents("students.txt", students);
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
                DrawText("Students", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < students.size(); i++) {
                    std::string studentInfo = "ID: " + students[i].getId() + " Name: " + students[i].getName();
                    DrawText(studentInfo.c_str(), 100, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) {
                    currentScreen = MENU;
                }
                break;

            case DISPLAY_COURSES:
                DrawText("Courses", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < courses.size(); i++) {
                    std::string courseInfo = "ID: " + courses[i].getId() + " Name: " + courses[i].getName();
                    DrawText(courseInfo.c_str(), 100, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) {
                    currentScreen = MENU;
                }
                break;

            case DISPLAY_FACULTY:
                DrawText("Faculty", 350, 50, 20, DARKGRAY);
                for (int i = 0; i < faculty.size(); i++) {
                    std::string facultyInfo = "ID: " + faculty[i].getId() + " Name: " + faculty[i].getName();
                    DrawText(facultyInfo.c_str(), 100, 100 + i * 30, 20, DARKGRAY);
                }
                if (Button({300, 500, 200, 40}, "Back")) {
                    currentScreen = MENU;
                }
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

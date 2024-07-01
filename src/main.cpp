#include "raylib.h"
#include <iostream>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "Faculty.h"
#include "FileHandler.h"

enum Screen { MENU, ADD_STUDENT, ADD_COURSE, ADD_FACULTY, DISPLAY_STUDENTS, DISPLAY_COURSES, DISPLAY_FACULTY };

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
    int inputIndex = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case MENU:
                DrawText("University Management System", 190, 50, 20, LIGHTGRAY);
                DrawText("1. Add Student", 340, 150, 20, LIGHTGRAY);
                DrawText("2. Add Course", 340, 200, 20, LIGHTGRAY);
                DrawText("3. Add Faculty", 340, 250, 20, LIGHTGRAY);
                DrawText("4. Display Students", 340, 300, 20, LIGHTGRAY);
                DrawText("5. Display Courses", 340, 350, 20, LIGHTGRAY);
                DrawText("6. Display Faculty", 340, 400, 20, LIGHTGRAY);

                if (IsKeyPressed(KEY_ONE)) currentScreen = ADD_STUDENT;
                if (IsKeyPressed(KEY_TWO)) currentScreen = ADD_COURSE;
                if (IsKeyPressed(KEY_THREE)) currentScreen = ADD_FACULTY;
                if (IsKeyPressed(KEY_FOUR)) currentScreen = DISPLAY_STUDENTS;
                if (IsKeyPressed(KEY_FIVE)) currentScreen = DISPLAY_COURSES;
                if (IsKeyPressed(KEY_SIX)) currentScreen = DISPLAY_FACULTY;

                break;

            case ADD_STUDENT:
                DrawText("Add Student", 350, 50, 20, LIGHTGRAY);
                DrawText("Student ID:", 200, 150, 20, LIGHTGRAY);
                DrawText("Student Name:", 200, 200, 20, LIGHTGRAY);
                DrawText(inputId, 400, 150, 20, BLACK);
                DrawText(inputName, 400, 200, 20, BLACK);

                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                if (IsKeyPressed(KEY_ENTER)) {
                    students.emplace_back(inputId, inputName);
                    FileHandler::saveStudents("students.txt", students);
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsKeyPressed(KEY_TAB)) inputIndex = (inputIndex + 1) % 2;
                if (inputIndex == 0) {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputId) < sizeof(inputId) - 1) {
                        inputId[strlen(inputId)] = key;
                        key = GetCharPressed();
                    }
                } else {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputName) < sizeof(inputName) - 1) {
                        inputName[strlen(inputName)] = key;
                        key = GetCharPressed();
                    }
                }

                break;

            case ADD_COURSE:
                DrawText("Add Course", 350, 50, 20, LIGHTGRAY);
                DrawText("Course ID:", 200, 150, 20, LIGHTGRAY);
                DrawText("Course Name:", 200, 200, 20, LIGHTGRAY);
                DrawText(inputId, 400, 150, 20, BLACK);
                DrawText(inputName, 400, 200, 20, BLACK);

                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                if (IsKeyPressed(KEY_ENTER)) {
                    courses.emplace_back(inputId, inputName);
                    FileHandler::saveCourses("courses.txt", courses);
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsKeyPressed(KEY_TAB)) inputIndex = (inputIndex + 1) % 2;
                if (inputIndex == 0) {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputId) < sizeof(inputId) - 1) {
                        inputId[strlen(inputId)] = key;
                        key = GetCharPressed();
                    }
                } else {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputName) < sizeof(inputName) - 1) {
                        inputName[strlen(inputName)] = key;
                        key = GetCharPressed();
                    }
                }

                break;

            case ADD_FACULTY:
                DrawText("Add Faculty", 350, 50, 20, LIGHTGRAY);
                DrawText("Faculty ID:", 200, 150, 20, LIGHTGRAY);
                DrawText("Faculty Name:", 200, 200, 20, LIGHTGRAY);
                DrawText(inputId, 400, 150, 20, BLACK);
                DrawText(inputName, 400, 200, 20, BLACK);

                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                if (IsKeyPressed(KEY_ENTER)) {
                    faculty.emplace_back(inputId, inputName);
                    FileHandler::saveFaculty("faculty.txt", faculty);
                    memset(inputId, 0, sizeof(inputId));
                    memset(inputName, 0, sizeof(inputName));
                    currentScreen = MENU;
                }

                if (IsKeyPressed(KEY_TAB)) inputIndex = (inputIndex + 1) % 2;
                if (inputIndex == 0) {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputId) < sizeof(inputId) - 1) {
                        inputId[strlen(inputId)] = key;
                        key = GetCharPressed();
                    }
                } else {
                    int key = GetCharPressed();
                    while (key > 0 && strlen(inputName) < sizeof(inputName) - 1) {
                        inputName[strlen(inputName)] = key;
                        key = GetCharPressed();
                    }
                }

                break;

            case DISPLAY_STUDENTS: {
                int y = 100;
                for (const auto& student : students) {
                    DrawText(("Student ID: " + student.getId() + ", Name: " + student.getName()).c_str(), 100, y, 20, LIGHTGRAY);
                    y += 30;
                }
                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                break;
            }

            case DISPLAY_COURSES: {
                int y = 100;
                for (const auto& course : courses) {
                    DrawText(("Course ID: " + course.getId() + ", Name: " + course.getName()).c_str(), 100, y, 20, LIGHTGRAY);
                    y += 30;
                }
                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                break;
            }

            case DISPLAY_FACULTY: {
                int y = 100;
                for (const auto& member : faculty) {
                    DrawText(("Faculty ID: " + member.getId() + ", Name: " + member.getName()).c_str(), 100, y, 20, LIGHTGRAY);
                    y += 30;
                }
                if (IsKeyPressed(KEY_BACKSPACE)) currentScreen = MENU;
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

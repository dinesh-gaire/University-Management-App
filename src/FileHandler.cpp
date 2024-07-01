#include "FileHandler.h"
#include <fstream>
#include <sstream>

std::vector<Student> FileHandler::loadStudents(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string id, name;
            iss >> id >> name;
            students.emplace_back(id, name);
        }
        file.close();
    }
    return students;
}

void FileHandler::saveStudents(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& student : students) {
            file << student.getId() << " " << student.getName() << std::endl;
        }
        file.close();
    }
}

std::vector<Course> FileHandler::loadCourses(const std::string& filename) {
    std::vector<Course> courses;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string id, name;
            iss >> id >> name;
            courses.emplace_back(id, name);
        }
        file.close();
    }
    return courses;
}

void FileHandler::saveCourses(const std::string& filename, const std::vector<Course>& courses) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& course : courses) {
            file << course.getId() << " " << course.getName() << std::endl;
        }
        file.close();
    }
}

std::vector<Faculty> FileHandler::loadFaculty(const std::string& filename) {
    std::vector<Faculty> faculty;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string id, name;
            iss >> id >> name;
            faculty.emplace_back(id, name);
        }
        file.close();
    }
    return faculty;
}

void FileHandler::saveFaculty(const std::string& filename, const std::vector<Faculty>& faculty) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& member : faculty) {
            file << member.getId() << " " << member.getName() << std::endl;
        }
        file.close();
    }
}

#include "Student.h"

Student::Student(const std::string& id, const std::string& name) : id(id), name(name) {}

std::string Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

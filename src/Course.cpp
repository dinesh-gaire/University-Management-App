#include "Course.h"

Course::Course(const std::string& id, const std::string& name) : id(id), name(name) {}

std::string Course::getId() const {
    return id;
}

std::string Course::getName() const {
    return name;
}

void Course::setName(const std::string& name) {
    this->name = name;
}

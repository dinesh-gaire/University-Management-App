#include "Faculty.h"

Faculty::Faculty(const std::string& id, const std::string& name) : id(id), name(name) {}

std::string Faculty::getId() const {
    return id;
}

std::string Faculty::getName() const {
    return name;
}

void Faculty::setName(const std::string& name) {
    this->name = name;
}

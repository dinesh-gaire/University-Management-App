#pragma once

#ifndef FACULTY_H
#define FACULTY_H

#include <string>

class Faculty {
public:
    Faculty(const std::string& id, const std::string& name);

    std::string getId() const;
    std::string getName() const;
    void setName(const std::string& name);

private:
    std::string id;
    std::string name;
};

#endif // FACULTY_H


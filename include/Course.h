#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
public:
    Course(const std::string& id, const std::string& name);

    std::string getId() const;
    std::string getName() const;
    void setName(const std::string& name);

private:
    std::string id;
    std::string name;
};

#endif // COURSE_H

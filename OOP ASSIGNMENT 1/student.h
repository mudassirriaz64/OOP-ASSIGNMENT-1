#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <fstream> // Add this for ifstream and ofstream
#include "person.h" // Assuming person.h contains the definition of the person class
#include "teacher.h" // Assuming teacher.h contains the definition of the teacher class
#include"section.h"

class teacher; // Forward declaration to resolve circular dependency
class section;

class student : public person , public section
{
private:
    std::string enroll;
    std::vector<teacher*> teachers;

public:
    std::string getEnroll() const;
    void setEnroll(const std::string& newEnroll);
    std::vector<teacher*>& getTeachers();
    const std::vector<teacher*>& getTeachers() const;
    void displayTimetable() const;
};

#endif // STUDENT_H

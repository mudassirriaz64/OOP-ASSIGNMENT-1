#pragma once

#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include <fstream> // Add this for ifstream and ofstream
#include "person.h" // Assuming person.h contains the definition of the person class

class student; // Forward declaration to resolve circular dependency

class teacher : public person
{
private:
    std::string application_id;
    std::vector<student*> students;

public:
    std::string getApplicationId() const;
    void setApplicationId(const std::string& ID);
    std::vector<student*>& getStudents();
    const std::vector<student*>& getStudents() const;
    void displayTimetable() const;
    void modifyTimetable();
};

#endif // TEACHER_H

#pragma once

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <vector>
#include <string>
#include "student.h"
#include "teacher.h"
#include "section.h"

extern std::vector<student> students_list;
extern std::vector<teacher> teachers_list;
extern std::vector<section> sections_list;

const std::string TEACHER_FILE = "teacher.txt";
const std::string STUDENT_FILE = "student.txt";
const std::string FILE_PREFIX = "timetable_";

void load_data(std::vector<student>& students_list, std::vector<teacher>& teachers_list);
void load_timetable_data();
void saveTeachers();
void removeTeacher(const std::string& application_id);
void displayTeachers();
void displayTimetable(const student& s);
void displayTeacherTimetable(const std::string& application_id);

#endif

#pragma once

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <vector>
#include <string>
#include "student.h"
#include "teacher.h"
#include "section.h"

extern std::vector<student> students_list;

const std::string STUDENT_FILE = "student.txt";
const std::string FILE_PREFIX = "timetable_";

void load_data(std::vector<student>& students_list);
void load_timetable_data();
void displayTimetable(const student& s);

#endif
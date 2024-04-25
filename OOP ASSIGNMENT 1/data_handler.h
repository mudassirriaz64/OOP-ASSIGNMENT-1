#pragma once

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <vector>
#include <string>
#include "student.h"
#include "teacher.h"
#include "section.h"

using namespace std;

extern std::vector<student> students_list;
extern std::vector<teacher> teachers_list;
extern std::vector<section> sections_list;

const std::string TEACHER_FILE = "teacher.txt";
const std::string STUDENT_FILE = "student.txt";
const std::string FILE_PREFIX = "timetable_";

//FUNCTION PROTOTYPES FOR STUDENT RELATED FUNCTIONS
void displayAllStudents();
void addStudentToFile(const string& name, const string& enrollID, const string& section);

//FUNCTION PROTOTYPES FOR TEACHER RELATED FUNCTIONS
void saveTeachers();
void removeTeacher(const string& application_id);
void displayTeachers();
void displayAllTeachers();

//FUNCTION PROTOTYPES FOR SECTION RELATED FUNCTIONS
void modifySectionTimetable(const string& section_choice);

//FUNCTION PROTOTYPES FOR ROOM RELATED FUNCTIONS
void modifyRoomTimetable(const string& room_choice);

//FUNCTION PROTOTYPES FOR FILE OPERATIONS
void load_data();

#endif

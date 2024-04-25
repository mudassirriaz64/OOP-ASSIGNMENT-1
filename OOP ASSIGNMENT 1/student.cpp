#include "student.h"
#include "teacher.h" 
#include <iostream>
#include"section.h"
#include<iostream>

using namespace std;

string student::getEnroll() const
{
	return enroll;
}
void student::setEnroll(const string& newEnroll)
{
	enroll = newEnroll;
}
vector<teacher*>& student::getTeachers()
{
	return teachers;
}
vector<teacher*> const& student::getTeachers() const
{
	return teachers;
}
void student::displayTimetable() const
{
    string filename = "timetable_" + getSectionName() + ".txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        cout << "Timetable for Student: " << getName() << " (Enrollment ID: " << getEnroll() << ")\n\n";
        while (getline(file, line))
        {
            cout << line << endl << endl;
        }
        file.close();
    }
    else
    {
        cout << "Timetable file not found for Section: " << getSectionName() << endl;
    }
}
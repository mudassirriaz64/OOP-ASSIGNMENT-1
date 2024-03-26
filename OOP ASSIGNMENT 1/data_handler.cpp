#include "data_handler.h"
#include <fstream>
#include <iostream>

using namespace std;

std::vector<student> students_list;
std::vector<section> sections_list;

void load_data(vector<student>& students_list)
{
    // Load student data
    ifstream studentfile(STUDENT_FILE);
    if (studentfile.is_open())
    {
        string name;
        string enroll;
        string section;
        while (getline(studentfile, name) && getline(studentfile, enroll) && getline(studentfile, section)) {
            student s; // Object of class student
            s.name = name;
            s.enroll = enroll;
            s.section_name = section;
            students_list.push_back(s);
        }
        studentfile.close();
    }
}

void load_timetable_data()
{
    for (auto& student : students_list)
    {
        string filename = FILE_PREFIX + student.section_name + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            string day;
            section sec;
            sec.section_name = student.section_name;

            while (getline(file, line))
            {
                if (!line.empty())
                {
                    if (line.back() == ':')
                    {
                        // Colon indicates the start of a new day
                        if (!day.empty())
                        {
                            day = line;
                        }
                        else
                        {
                            day = day + line;
                        }
                    }
                    else {
                        // Add the timetable entry for the current day
                        sec.addTimetableEntry(day, line);
                    }
                }
            }
            sections_list.push_back(sec);

            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }
}
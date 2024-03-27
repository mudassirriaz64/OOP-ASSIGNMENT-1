#include "data_handler.h"
#include <fstream>
#include <iostream>

using namespace std;

std::vector<student> students_list;
std::vector<teacher> teachers_list;
std::vector<section> sections_list;

void load_data(vector<student>& students_list, vector<teacher>& teachers_list)
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

    // Load teacher data
    ifstream tfile(TEACHER_FILE);
    if (tfile.is_open())
    {
        string id;
        string name;
        while (getline(tfile, id) && getline(tfile, name))
        {
            teacher t;
            t.name = name;
            t.application_id = id;
            teachers_list.push_back(t);
        }
        tfile.close();
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
                            // Add the timetable entry for the previous day to the section
                            day = line; // Set the day for the new day
                        }
                        else
                        {
                            day = day + line; // Set the day for the first entry of the day
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
    for (const auto& teacher : teachers_list)
    {
        string filename = FILE_PREFIX + teacher.application_id + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            string current_day;
            section section;
            section.section_name = teacher.application_id;

            while (getline(file, line))
            {
                if (line.empty()) continue;
                if (line.back() == ':')
                {
                    current_day = line;
                }
                else
                {
                    section.addTimetableEntry(current_day, line);
                }
            }
            sections_list.push_back(section);
            file.close();
        }
        else {
            cout << "Unable to open section file: " << filename << endl;
        }
    }
}

void saveTeachers()
{
    ofstream teacherFile(TEACHER_FILE);
    if (teacherFile.is_open()) {
        for (const auto& teacher : teachers_list) {
            teacherFile << teacher.application_id << endl;
            teacherFile << teacher.name << endl;
        }
        teacherFile.close();
    }
    else {
        cout << "Unable to open teacher file for writing: " << TEACHER_FILE << endl;
    }
}

void displayTimetable(const student& s)
{
    for (const auto& sec : sections_list)
    {
        if (sec.section_name == s.section_name)
        {
            cout << "Section: " << sec.section_name << "\n";
            string currentDay = ""; // Keep track of the current day
            bool isFirstEntry = true; // Flag to track the first entry
            for (const auto& entry : sec.timetable)
            {
                string day = entry.first;
                // Remove the extra colon if present
                if (day.back() == ':')
                {
                    day.pop_back();
                }
                // Check if it's a new day
                if (day != currentDay)
                {
                    // If it's not the first entry, print the row of asterisks
                    if (!isFirstEntry)
                    {
                        cout << "****************************************\n";
                    }
                    currentDay = day; // Update current day
                }
                // Print the entry without an additional colon
                cout << day << ": " << entry.second << "\n";
                isFirstEntry = false;
            }
            // Print a row of asterisks after all entries for the last day
            if (!sec.timetable.empty())

            {
                cout << "****************************************\n";
            }
            break;
        }
    }
}

void displayTeacherTimetable(const string& application_id)
{
    for (const auto& section : sections_list)
    {
        if (section.section_name == application_id)
        {
            teacher t1;
            if (application_id == "191441")
            {
                t1.name = "Dr. Tamim Ahmed Khan";
            }
            else if (application_id == "191442")
            {
                t1.name = "Dr. Awais Majeed";
            }
            else
            {
                break;
            }
            cout << "Teacher: " << t1.name << endl;
            string current_day = "";
            for (const auto& entry : section.timetable)
            {
                if (entry.first != current_day)
                {
                    cout << "****************************************\n";
                    current_day = entry.first;
                }
                cout << entry.first << ": " << entry.second << endl;
            }
            cout << "****************************************\n";
            return;
        }
    }
    cout << "Timetable not found for Teacher with this Application ID : " << application_id << endl;
}

void displayTeachers()
{
    cout << "Teachers:\n";
    for (const auto& teacher : teachers_list)
    {
        cout << "ID: " << teacher.application_id << ", Name: " << teacher.name << endl;
    }
}

void removeTeacher(const string& application_id)
{
    auto it = find_if(teachers_list.begin(), teachers_list.end(), [&](const teacher& t) { return t.application_id == application_id; });
    if (it != teachers_list.end())
    {
        teachers_list.erase(it);
        cout << "Teacher with Application ID " << application_id << " removed successfully." << endl;
        saveTeachers();
    }
    else
    {
        cout << "Teacher with Application ID " << application_id << " not found." << endl;
    }
}
// Path: OOP%20Assign/section.cpp


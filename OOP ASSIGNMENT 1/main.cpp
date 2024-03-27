#include <iostream>
#include<string>
#include <vector>
#include <fstream>
#include "data_handler.h"
#include "main.h"

using namespace std;

int main()
{
    load_data(students_list, teachers_list);
    load_timetable_data();
    int choice;
start:
    system("cls");
    cout << "\tTime Table Management System\n\n";
    cout << "1. Teacher Wise Time Table\n2. Student Wise Time Table\n3. Section Wise Time Table\n4. Room Wise Time Table\n5. Remove Teacher\n6. View Teachers\n\nSelect Your Option: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        string id; // temporary id to compare it with the teacher enroll id stored in txt.file
        cout << "Enter your Application ID : ";
        cin >> id;
        cin.ignore();
        bool teacher_found = false;
        for (auto& teacher : teachers_list)
        {
            if (teacher.application_id == id)
            {
                system("cls");
                teacher_found = true;
                string teacher_choice;
                cout << "Teacher information\n*******************\nTeacher Name : " << teacher.name << "\nApplication ID : " << teacher.application_id << endl;
                cout << "\n\n1. View Time Table\n2. Log out\n\nSelect your choice : ";
                do
                {
                    getline(cin, teacher_choice);
                    if (teacher_choice == "1")
                    {
                        system("cls");
                        displayTeacherTimetable(id);
                        system("pause");
                        system("cls");
                        goto start;
                    }
                    else if (teacher_choice == "2")
                    {
                        return 0;
                    }
                    else {
                        cout << "Invalid Selection, Try again : ";
                        getline(cin, teacher_choice);
                    }
                } while (teacher_choice != "1" && teacher_choice != "2");
                break;
            }
        }
        if (teacher_found != true)
        {
            cout << "Teacher ID not Found\n";
            system("pause");
            goto start;
        }
    }
    case 2:
    {
        system("cls");
        string id; // temporary id to compare it with the student enroll id stored in txt.file
        cout << "Enter your Enrollment ID : ";
        cin >> id;
        cin.ignore();
        bool student_found = false;
        for (auto& student : students_list)
        {
            if (student.enroll == id)
            {
                system("cls");
                student_found = true;
                string student_choice;
                cout << "Student Information\n*******************\nStudent Name : " << student.name << "\nEnrollment ID : " << student.enroll << "\nSection : " << student.section_name << endl;
                cout << "\n\n1. View time table\n2. Log out\n\nSelect your Choice : ";
                do
                {
                    getline(cin, student_choice);
                    if (student_choice == "1")
                    {
                        system("cls");
                        displayTimetable(student);
                        system("pause");
                        system("cls");
                        goto start;
                    }
                    else if (student_choice == "2")
                    {
                        return 0;
                    }
                    else
                    {
                        cout << "Invalid Selection, Try again : ";
                        getline(cin, student_choice);
                    }
                } while (student_choice != "1" && student_choice != "2");
                break;
            }
        }
        if (student_found != true)
        {
            cout << "Student ID not Found\n";
            system("pause");
            goto start;
        }
    }
    case 3:
    {
        system("cls");
        string section_choice;
        cout << "Enter Section (2-A, 2-B, 4-A, 6-A, 8-A): ";
        cin.ignore();
        getline(cin, section_choice);
        string filename = FILE_PREFIX + section_choice + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            system("cls");
            cout << "Timetable for Section " << section_choice << ":\n";
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open timetable file for Section " << section_choice << endl;
            system("pause");
            goto start;
        }
        break;
    }
    case 4:
        // Room Function would be called
        break;
    case 5:
    {
        string id;
        cout << "Enter Application ID of Teacher to remove: ";
        cin >> id;
        removeTeacher(id);
        break;
    }
    case 6:
    {
        system("cls");
        displayTeachers();
        system("pause");
        goto start;
    }
    }
    return 0;
}

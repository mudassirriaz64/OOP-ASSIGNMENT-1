#include <iostream>
#include<string>
#include <vector>
#include <fstream>
#include "data_handler.h"
#include "main.h"

using namespace std;

int main()
{
    load_data();
    int choice;
start:
    system("cls");
    cout << "\tTime Table Management System\n\n";
    cout << "1. Teacher Wise Time Table\n2. Student Wise Time Table\n3. Section Wise Time Table\n4. Room Wise Time Table\n5. Add Student\n6. Display All Students\n7. Add Teacher\n8. Remove Teachern\n9. Display All Teachers\n\nSelect Your Option: ";
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
            if (teacher.getApplicationId() == id)
            {
                system("cls");
                teacher_found = true;
                string teacher_choice;
                cout << "Teacher information\n*******************\nTeacher Name : " << teacher.getName() << "\nApplication ID : " << teacher.getApplicationId() << endl;
                cout << "\n\n1. View Time Table\n2. Log out\n\nSelect your choice : ";
                do
                {
                    getline(cin, teacher_choice);
                    if (teacher_choice == "1")
                    {
                        system("cls");
                        teacher.displayTimetable();
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
            if (student.getEnroll() == id)
            {
                system("cls");
                student_found = true;
                string student_choice;
                cout << "Student Information\n*******************\nStudent Name : " << student.getName() << "\nEnrollment ID : " << student.getEnroll() << "\nSection : " << student.getSectionName() << endl;
                cout << "\n\n1. View time table\n2. Log out\n\nSelect your Choice : ";
                do
                {
                    getline(cin, student_choice);
                    if (student_choice == "1")
                    {
                        system("cls");
                        student.displayTimetable();
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
            cout << "Timetable for Section " << section_choice << ":\n\n";
            string line;
            bool TimeSlotFound = false;
            while (getline(file, line))
            {
                if (line != "")
                {
                    cout << line << endl;
                    TimeSlotFound = true;
                }
            }
            if (!TimeSlotFound)
            {
                cout << "No timeslots found for Section " << section_choice << endl << endl;
            }
            file.close();
            char modify_choice;
            cout << "\n\nDo you want to add or modify timeslots (Y/N) : ";
            cin >> modify_choice;
            if (toupper(modify_choice) == 'Y')
            {
                modifySectionTimetable(section_choice);
            }
            else if (toupper(modify_choice) == 'N')
            {
                system("pause");
                goto start;
            }
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
    {
        system("cls");
        string room_choice;
        cout << "Enter Room ( 4-17, 4-18, 4-19 ): ";
        cin.ignore();
        getline(cin, room_choice);
        string filename = FILE_PREFIX + room_choice + ".txt";
        ifstream file(filename);
        if (file.is_open())
        {
            system("cls");
            cout << "Timetable for Room " << room_choice << ":\n\n";
            string line;
            bool TimeSlotFound = false;
            while (getline(file, line))
            {
                if (line != "")
                {
                    cout << line << endl;
                    TimeSlotFound = true;
                }
            }
            if (!TimeSlotFound)
            {
                cout << "No timeslots found for Section " << room_choice << endl << endl;
            }
            file.close();
            char modify_choice;
            cout << "\n\nDo you want to add or modify timeslots (Y/N) : ";
            cin >> modify_choice;
            if (toupper(modify_choice) == 'Y')
            {
                modifyRoomTimetable(room_choice);
            }
            else if (toupper(modify_choice) == 'N')
            {
                system("pause");
                goto start;
            }
        }
        else
        {
            cout << "Unable to open timetable file for Section " << room_choice << endl;
            system("pause");
            goto start;
        }
        break;
    }
    case 5:
    {
        system("cls");
        string name, enrollID;
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Enrollment ID: ";
        cin >> enrollID;
        string section;
        cout << "Enter Section (2-A, 2-B, 4-A, 6-A, 8-A): ";
        cin.ignore();
        getline(cin, section);
        addStudentToFile(name, enrollID, section);
        system("pause");
        goto start;
    }
    case 6:
    {
        system("cls");
        displayAllStudents();
        system("pause");
        system("cls");
        goto start;
    }
    case 7:
    {
        system("cls");
        string name, id;
        cout << "Enter Teacher Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Application ID: ";
        cin >> id;
        teacher newTeacher;
        newTeacher.setName(name);
        newTeacher.setApplicationId(id);
        teachers_list.push_back(newTeacher);

        // Create an empty timetable file for the new teacher
        ofstream timetableFile(FILE_PREFIX + id + ".txt");
        timetableFile.close();
        goto start;
    }
    case 8:
    {
        string id;
        cout << "Enter Application ID of Teacher to remove: ";
        cin >> id;
        removeTeacher(id);
        system("pause");
        goto start;
    }
    case 9:
        // Display all teachers with their application ID
        displayAllTeachers();
        break;
    }
    return 0;
}

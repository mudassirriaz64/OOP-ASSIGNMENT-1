#include <iostream>
#include<string>
#include <vector>
#include <fstream>
#include "data_handler.h"
#include "main.h"

using namespace std;

int main()
{
    load_data(students_list);
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
            // Teacher Function would be called
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
       //Section Function would be called
    }
    case 4:
        // Room Function would be called
        break;
    case 5:
    {
       //Remove Teacher Functionality
    }
    case 6:
    {
        //View Teachers Functionality
    }
    }
    return 0;
}
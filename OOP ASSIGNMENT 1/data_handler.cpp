#include "data_handler.h"
#include"section.h"
#include <fstream>
#include <iostream>

using namespace std;

std::vector<student> students_list;
std::vector<teacher> teachers_list;
std::vector<section> sections_list;

void load_data()
{
    // Load student data
    ifstream studentfile(STUDENT_FILE);
    if (studentfile.is_open())
    {
        string name;
        string enroll;
        string section_name;
        while (getline(studentfile, name) && getline(studentfile, enroll) && getline(studentfile, section_name))
        {
            student s; // Object of class student
            s.setName(name);
            s.setEnroll(enroll);
            s.setSectionName(section_name);

            // Associate student with teachers
            for (auto& teacher : teachers_list)
            {
                s.getTeachers().push_back(&teacher);
                teacher.getStudents().push_back(&s);
            }

            students_list.push_back(s);
        }
        studentfile.close();
    }


    // Load teacher data
    ifstream tfile("teacher.txt");
    if (tfile.is_open())
    {
        string id;
        string name;
        while (getline(tfile, id) && getline(tfile, name))
        {
            teacher t;
            t.setApplicationId(id);
            t.setName(name);

            // Associate teacher with students
            for (auto& student : students_list)
            {
                student.getTeachers().push_back(&t);
                t.getStudents().push_back(&student);
            }

            teachers_list.push_back(t);
        }
        tfile.close();
    }
}

void saveTeachers()
{
    ofstream teacherFile(TEACHER_FILE);
    if (teacherFile.is_open()) {

        for (const auto& teacher : teachers_list)
        {
            teacherFile << teacher.getApplicationId() << endl;
            teacherFile << teacher.getName() << endl;
        }
        teacherFile.close();
    }
    else {
        cout << "Unable to open teacher file for writing: " << TEACHER_FILE << endl;
    }
}


void displayTeachers()
{
    cout << "Teachers:\n";
    for (const auto& teacher : teachers_list)
    {
        cout << "ID: " << teacher.getApplicationId() << ", Name: " << teacher.getName() << endl;
    }
}

void removeTeacher(const string& application_id)
{
    auto it = find_if(teachers_list.begin(), teachers_list.end(), [&](const teacher& t) { return t.getApplicationId() == application_id; });
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

void addStudentToFile(const string& name, const string& enrollID, const string& section)
{
    ofstream outfile(STUDENT_FILE, ios::app); // Open file in append mode

    if (outfile.is_open())
    {
        // Write student details to the file
        outfile << name << endl;
        outfile << enrollID << endl;
        outfile << section << endl;
        cout << "Student added successfully." << endl;
        outfile.close();
    }
    else {
        cout << "Unable to open student file for writing." << endl;
    }
}

void displayAllStudents()
{
    ifstream infile(STUDENT_FILE);

    if (infile.is_open())
    {
        string name, enrollID, section;
        int count = 0;
        cout << "List of Students:\n";
        while (getline(infile, name) && getline(infile, enrollID) && getline(infile, section))
        {
            cout << "Name: " << name << "\nEnrollment ID: " << enrollID << "\nSection: " << section << "\n\n";
            count++;
        }
        cout << "Total Students: " << count << endl;
        infile.close();
    }
    else {
        cout << "Unable to open student file for reading." << endl;
    }
}

void displayAllTeachers()
{
    system("cls");
    ifstream teacherFile(TEACHER_FILE);
    int count = 0; // Count variable to track the total number of teachers

    if (teacherFile.is_open())
    {
        cout << "List of Teachers:\n\n";
        string id, name;
        while (getline(teacherFile, id) && getline(teacherFile, name))
        {
            cout << "Application ID: " << id << ", Name: " << name << endl << endl;
            count++;
        }
        cout << "Total Teachers: " << count << endl;
        teacherFile.close();
    }
    else {
        cout << "Unable to open teacher file for reading." << endl;
    }
}

void modifyRoomTimetable(const string& room_name)
{
    string originalFilename = FILE_PREFIX + room_name + ".txt";
    string tempFilename = "temp.txt";

    ifstream infile(originalFilename);
    ofstream outfile(tempFilename); // Open in overwrite mode

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Error: Unable to open timetable file for modification." << endl;
        return;
    }

    string day, startTime, endTime, classInfo, section, room;
    char choice;

    cout << "Do you want to modify an existing entry (M) or add a new entry (A)? ";
    cin >> choice;

    if (toupper(choice) == 'M')
    { // Modify existing entry
        bool found = false;
        string newDay, newStartTime, newEndTime, newClassInfo;
        cout << "Enter Day Of Which You Want To Modify : ";
        cin >> day;
        cout << "Enter Starting Time of the Class you want to Modify (e.g., 08:30): ";
        cin.ignore(); // Ignore the newline character left in the input buffer
        getline(cin, startTime);

        // Read the file line by line and modify the entry if found
        while (infile >> newDay >> newStartTime >> newEndTime)
        {
            // Read the rest of the line (class information) into newClassInfo
            getline(infile, newClassInfo);

            if (newDay == day && newStartTime == startTime)
            { // Check both day and starting time
                cout << "Enter Day of New Class : ";
                cin >> newDay;
                cout << "Enter Starting time of New Class (e.g., 08:30): ";
                cin.ignore(); // Ignore the newline character left in the input buffer
                getline(cin, newStartTime);
                cout << "Enter Ending time of New Class (e.g., 09:30): ";
                cin >> newEndTime;
                cout << "Enter Class Information ( Course Name - Teacher Name - SECTION - ) : ";
                cin.ignore();
                getline(cin, newClassInfo);

                // Write the modified entry to the file
                outfile << newDay << " " << newStartTime << " " << newEndTime << " " << newClassInfo << endl;
                found = true;
            }
            else
            {
                // Rewrite the existing entry to the file
                outfile << newDay << " " << newStartTime << " " << newEndTime << " " << newClassInfo << endl;
            }

        }


        if (!found)
        {
            cout << "Timetable Entry not found." << endl;

        }
    }
    else if (toupper(choice) == 'A')
    { // Add new entry
        infile.close();
        outfile.close();
        cout << "Enter Day of New Class : ";
        cin >> day;
        cout << "Enter Starting Time of New Class (e.g., 08:30): ";
        cin >> startTime;
        cout << "Enter Ending Time of the new Class (e.g., 09:30): ";
        cin >> endTime;
        cout << "Enter Class Information ( Course Name - Teacher Name - SECTION - ROOM ) : ";
        cin.ignore();
        getline(cin, classInfo);


        // Write the new entry to the file
        outfile.open(originalFilename, ios::app);
        outfile << day << " " << startTime << " " << endTime << " " << classInfo << " " << section << " " << room << endl;
        cout << "New class added successfully." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

    infile.close();
    outfile.close();

    if (toupper(choice) == 'M')
    {
        remove(originalFilename.c_str());
        if (rename(tempFilename.c_str(), originalFilename.c_str()) != 0)
        {
            cout << "Error: Unable to rename temporary file to original filename." << endl;
            // Handle the error, such as logging the failure or informing the user.
        }
    }
}
// Path: OOP%20Assign/section.cpp


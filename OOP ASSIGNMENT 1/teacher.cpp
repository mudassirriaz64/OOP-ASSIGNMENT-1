#include "teacher.h"
#include"section.h"
#include"student.h"
#include"data_handler.h"
#include<iostream>

using namespace std;

string teacher::getApplicationId() const
{
	return application_id;
}

void teacher::setApplicationId(const string& ID)
{
	application_id = ID;
}

vector<student*>& teacher::getStudents()
{
	return students;
}

const vector<student*>& teacher::getStudents() const
{
	return students;
}

void teacher::displayTimetable() const
{
    for (auto& teacher : teachers_list)
    {
        if (teacher.getApplicationId() == application_id)
        {
            string filename = FILE_PREFIX + application_id + ".txt";
            ifstream file(filename);
            if (file.is_open())
            {
                string line;
                cout << "Teacher: " << teacher.getName() << endl << endl << endl;;
                bool timeslotFound = false; // Flag to track if any timeslots are found
                while (getline(file, line))
                {
                    cout << line << endl;
                    timeslotFound = true; // Set flag to true if any timeslot is found
                }
                file.close();

                if (!timeslotFound)
                {
                    cout << "No timeslots available for this teacher. Please add one." << endl;
                }

                int choice;
                do
                {
                    cout << "\n\n\n1. Modify timetable\n2. Exit\n\nSelect your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        teacher.modifyTimetable();
                        break;
                    case 2:
                        return;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
                } while (true);
            }
            else
            {
                cout << "Timetable file not found for Teacher with this Application ID: " << application_id << endl;
            }
            return;
        }
    }
    cout << "Teacher with Application ID: " << application_id << " not found." << endl;
}

void teacher::modifyTimetable()
{
    string originalFilename = FILE_PREFIX + getApplicationId()
        + ".txt";
    string tempFilename = "temp.txt";

    ifstream infile(originalFilename);
    ofstream outfile(tempFilename); // Open in overwrite mode

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Error: Unable to open timetable file for modification." << endl;
        return;
    }

    string day, startTime, endTime, classInfo, section, room;
    char choice;

    cout << "Modify an Existing TimeSlot (M) OR Add a New Entry (A)? ";
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
                cout << "Enter Class Information ( Course Name - SECTION - ROOM ) : ";
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
        cout << "Enter Class Information ( Course Name - SECTION - ROOM ) : ";
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
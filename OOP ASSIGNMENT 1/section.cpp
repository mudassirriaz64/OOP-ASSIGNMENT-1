#include "section.h"
#include"data_handler.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

string section::getSectionName() const
{
	return section_name;
}

void section::setSectionName(const string& newSectionName)
{
	section_name = newSectionName;
}


void modifySectionTimetable(const string& section_name)
{
    string originalFilename = FILE_PREFIX + section_name + ".txt";
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
                cout << "Enter Class Information ( Course Name - Teacher Name - ROOM ) : ";
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
        cout << "Enter Class Information ( Course Name - Teacher Name - ROOM ) : ";
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

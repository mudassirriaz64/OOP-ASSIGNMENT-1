#pragma once

#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include <string>
#include <utility>

class section
{
public:
	std::string section_name;
	std::vector<std::pair<std::string, std::string>> timetable; // Vector to store timetable for each day (time, class info)

	// Function to add a timetable entry for a day because we already created the program in one single main file then divided it in different cpp and .h files with the help of chat gpt
	void addTimetableEntry(const std::string& time, const std::string& classInfo);
};

#endif
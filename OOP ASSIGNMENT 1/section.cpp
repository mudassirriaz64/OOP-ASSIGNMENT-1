#include "section.h"

void section::addTimetableEntry(const std::string& time, const std::string& classInfo)
{
	timetable.push_back(std::make_pair(time, classInfo));
}
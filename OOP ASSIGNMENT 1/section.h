#pragma once

#ifndef SECTION_H
#define SECTION_H

#include <string>

class section
{
private:
    std::string section_name;

public:
    std::string getSectionName() const;
    void setSectionName(const std::string& newSectionName);
};

#endif // SECTION_H

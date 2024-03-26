#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "section.h"

class student : public person, public section
{
public:
    std::string enroll;
};

#endif // STUDENT_H

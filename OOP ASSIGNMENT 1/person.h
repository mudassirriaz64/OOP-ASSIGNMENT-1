#pragma once

#ifndef PERSON_H
#define PERSON_H

#include <string>

class person
{
private:
    std::string name;

public:
    std::string getName() const
    {
        return name;
    }

    void setName(const std::string& name)
    {
        this->name = name;
    }
};

#endif // PERSON_H

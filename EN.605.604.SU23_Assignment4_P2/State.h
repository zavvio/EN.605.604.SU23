#pragma once

#include "DevUtil.h"

class State
{
public:
    State(std::string stateName = "", std::string capitalCityName = "");
    std::string getStateName() const;
    void setStateName(std::string name);
    std::string getCapitalCityName() const;
    void setCapitalCityName(std::string name);

private:
    std::string stateName;
    std::string capitalCityName;
};
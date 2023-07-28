#include "State.h"

State::State(std::string stateName, std::string capitalCityName)
    : stateName{ stateName }, capitalCityName{ capitalCityName }
{}

std::string State::getStateName() const
{
    return stateName;
}

void State::setStateName(std::string name)
{
    stateName = name;
}

std::string State::getCapitalCityName() const
{
    return capitalCityName;
}

void State::setCapitalCityName(std::string name)
{
    capitalCityName = name;
}
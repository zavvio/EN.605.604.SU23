#pragma once
#include <iostream>
#include <deque>
#include "Drink.h"
#include "DevUtil.h"

class DrinkStorage
{
public:
    DrinkStorage(unsigned count = 5) : maxCount{count} {};
    virtual ~DrinkStorage();
    bool isFull() const;
    bool isEmpty() const;
    unsigned getMaxCount() const;
    unsigned getCurrentCount() const;
    void insert(std::unique_ptr<Drink>& drink);
    std::unique_ptr<Drink> dispense();

protected:
    std::deque<std::unique_ptr<Drink>> drinks;

private:
    const unsigned maxCount;
};
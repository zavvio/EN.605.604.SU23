#pragma once
#include <iostream>
#include <deque>
#include "Drink.h"
#include "DevUtil.h"

// This is the base class capable of storing drinks,
// it supports functional components like dispensing column and delivery slot in a vending machine.
class DrinkStorage
{
public:
    DrinkStorage(unsigned count = 5) : maxCount{count} {};
    virtual ~DrinkStorage();
    void insert(std::unique_ptr<Drink>& drink);
    bool isEmpty() const;
    std::unique_ptr<Drink> dispense();

    // The followings are useful as info for user interface but not required for minimal functionality.
    bool isFull() const;
    unsigned getMaxCount() const;
    unsigned getCurrentCount() const;

protected:
    std::deque<std::unique_ptr<Drink>> drinks;

private:
    const unsigned maxCount;
};
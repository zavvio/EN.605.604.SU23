#pragma once

#include <iostream>
#include "Date.h"
#include "DevUtil.h"

template <class T>
class Array
{
private:
    T* arrayElements;           // Array of type T
    long size;                  // Size of array

public:
    Array(long asize);          // Constructor
    Array(const Array<T>& rhs); // Copy constructor
    ~Array();                   // Destructor
    long getSize() const;
    void display() const;

    // Operator function
    T& operator[](long s);                      // Indexing
    Array<T>& operator=(const Array<T>& rhs);   // Assignment
    Array<T> operator+(const Array<T>& rhs);    // Addition
    Array<T> operator-();                       // Negate
};

// Template specialization
template <> Array<std::string> Array<std::string>::operator+(const Array<std::string>& rhs);
template <> Array<std::string> Array<std::string>::operator-() = delete;
template <> void Array<Date>::display() const;
template <> Array<Date> Array<Date>::operator+(const Array<Date>& rhs) = delete;
template <> Array<Date> Array<Date>::operator-() = delete;
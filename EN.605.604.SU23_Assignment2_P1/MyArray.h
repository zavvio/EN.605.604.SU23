#pragma once

#include <iostream>

class MyArray
{
public:
    MyArray(int sz = 0);
    MyArray(MyArray& array);
    ~MyArray();
    bool getDataByIndex(const int index, int& value);
    bool setDataByIndex(const int index, const int value);
    int getSize() const;
    bool createData(const int size);
    void deleteData();
    void displayData();

private:
    int* data { nullptr };
    int size { 0 };
};
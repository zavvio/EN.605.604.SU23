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
    bool createData(const int size); // Public to allow late creation
    void deleteData(); // Public to allow clean and re-creation
    void displayData();

private:
    int* data { nullptr };
    int size { 0 };
};
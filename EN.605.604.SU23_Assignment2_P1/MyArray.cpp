#include "MyArray.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

// The constructor is modified slightly from as defined in the problem
// statement in order to perform some basic input error check.
MyArray::MyArray(int sz)
{
    if (!createData(sz))
    {
        std::cout << "[ERROR] MyArray initialization failed, defaulting members to 0." << std::endl;
    }
}

// Copy constructor perform deep copy on dynamically allocated data array.
// Source MyArray only provides interface to retrieve data by index,
// thus ensure encapsulation and data hiding without returning raw pointer.
MyArray::MyArray(MyArray& array)
{
    std::cout << "MyClass copy constructor is called." << std::endl;
    size = array.getSize();
    if (size == 0)
    {
        data = nullptr;
    }
    else
    {
        createData(size);
        for (int i = 0; i < size; i++)
        {
            if (!array.getDataByIndex(i, data[i]))
            {
                std::cout << "[ERROR] Failed to copy data at index " << i << std::endl;
            }
        }
    }
}

MyArray::~MyArray()
{
    deleteData();
}

// Only return one data element to prevent direct manipulation on array.
bool MyArray::getDataByIndex(const int index, int& value)
{
    std::cout << "Getting data at index " << index << std::endl;
    if (index >= size)
    {
        std::cout << "[ERROR] Failed to retrieve data for index " << index << ". Out of bound." << std::endl;
        return false;
    }
    value = data[index];
    return true;
}

bool MyArray::setDataByIndex(const int index, const int value)
{
    std::cout << "Setting data at index " << index << std::endl;
    if (index >= size)
    {
        std::cout << "[ERROR] Failed to set data for index " << index << ". Out of bound." << std::endl;
        return false;
    }
    data[index] = value;
    return true;
}

int MyArray::getSize() const
{
    return size;
}

// This is a public function to allow allocating memory later in case MyArray
// was given an invalid array size during object instantiation.
bool MyArray::createData(const int size)
{
    if (size <= 0)
    {
        std::cout << "[ERROR] Failed to create array of size " << size << std::endl;
        data = nullptr;
        this->size = 0;
        return false;
    }
    else
    {
        data = new int[size];
        this->size = size;
        memset(data, 0, sizeof(int) * size);
        return true;
    }
}

// This is a public function to provide capability of array re-creation
void MyArray::deleteData()
{
    std::cout << "Deleting data." << std::endl;
    delete[] data;
    data = nullptr;
    size = 0;
}

void MyArray::displayData()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << data[i] << ", ";
    }
    std::cout << std::endl;
}

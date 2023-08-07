#include "SerializableDate.h"

using namespace std;

// ==================== HELPER FUNCTIONS ====================

void __writeDatesToTextFile(std::vector<Date>& dates, std::string filePath);
void __readDatesFromTextFile(std::vector<Date>& dates, std::string filePath);
void __writeDatesToBinaryFile(std::vector<Date>& dates, std::string filePath);
void __readDatesFromBinaryFile(std::vector<Date>& dates, std::string filePath);
void __displayDates(std::vector<Date>& dates);

// Template instantiation
template class SerializableDate<std::vector<Date>>;

// ==================== BASIC TEMPLATE DEFINITION ====================

template <class T> void SerializableDate<T>::read(bool isBinary) const
{}

template <class T> void SerializableDate<T>::write(bool isBinary) const
{}

template <class T> void SerializableDate<T>::display() const
{}

// ==================== TEMPLATE SPECIALIZATION ====================

template <> void SerializableDate<std::vector<Date>>::read(bool isBinary) const
{
    if (isBinary)
    {
        __readDatesFromBinaryFile(object, filePath);
    }
    else
    {
        __readDatesFromTextFile(object, filePath);
    }
}

template <> void SerializableDate<std::vector<Date>>::write(bool isBinary) const
{
    if (isBinary)
    {
        __writeDatesToBinaryFile(object, filePath);
    }
    else
    {
        __writeDatesToTextFile(object, filePath);
    }
}

// Specialized display function for vector<Date> class.
template <> void SerializableDate<std::vector<Date>>::display() const
{
    __displayDates(object);
}

// ==================== HELPER FUNCTIONS DEFINITION ====================

// Serialize Date collection to file in ASCII mode.
void __writeDatesToTextFile(std::vector<Date>& dates, std::string filePath)
{
    // open file for output
    ofstream outputFile{ filePath, ios::out };

    // exit if unable to open file
    if (!outputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream ss;
    ss << dates.size() << endl;
    for (Date& d : dates)
    {
        ss << d.getDay() << ' ' << d.getMonth() << ' ' << d.getYear() << endl;
    }
    outputFile << ss.rdbuf();
    outputFile.close();
    cout << "==================== Written to text file {" << filePath << "} successfully ====================" << endl;
}

// Deserialize Date collection from file in ASCII mode.
void __readDatesFromTextFile(std::vector<Date>& dates, std::string filePath)
{
    int sizeDates, bufferInt;
    string bufferStr;
    Date date;
    dates.clear();
    // open file for input
    ifstream inputFile{ filePath, ios::in };

    // exit if unable to open file
    if (!inputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    // read file input
    inputFile >> sizeDates;
    for (int i = 0; i < sizeDates; i++)
    {
        date = Date();
        inputFile >> bufferInt;
        date.setDay(bufferInt);
        inputFile >> bufferInt;
        date.setMonth(bufferInt);
        inputFile >> bufferInt;
        date.setYear(bufferInt);
        dates.push_back(date);
    }
    inputFile.close();
    cout << "==================== Read from text file {" << filePath << "} successfully ====================" << endl;
}

// Serialize Date collection to file in binary mode.
void __writeDatesToBinaryFile(std::vector<Date>& dates, std::string filePath)
{
    // open file for output
    ofstream outputFile{ filePath, ios::out | ios::binary };

    // exit if unable to open file
    if (!outputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    int value;
    size_t size = dates.size();
    outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (Date& d : dates)
    {
        value = d.getDay();
        outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
        value = d.getMonth();
        outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
        value = d.getYear();
        outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    outputFile.close();
    cout << "==================== Written to binary file {" << filePath << "} successfully ====================" << endl;
}

// Deserialize Date collection from file in binary mode.
void __readDatesFromBinaryFile(std::vector<Date>& dates, std::string filePath)
{
    int value;
    size_t sizeDates, size;
    Date date;
    dates.clear();
    // open file for input
    ifstream inputFile{ filePath, ios::in | ios::binary };

    // exit if unable to open file
    if (!inputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    // read file input
    inputFile.read(reinterpret_cast<char*>(&sizeDates), sizeof(sizeDates));
    for (int i = 0; i < sizeDates; i++)
    {
        date = Date();
        inputFile.read(reinterpret_cast<char*>(&value), sizeof(value));
        date.setDay(value);
        inputFile.read(reinterpret_cast<char*>(&value), sizeof(value));
        date.setMonth(value);
        inputFile.read(reinterpret_cast<char*>(&value), sizeof(value));
        date.setYear(value);
        dates.push_back(date);
    }
    inputFile.close();
    cout << "==================== Read from binary file {" << filePath << "} successfully ====================" << endl;
}

void __displayDates(std::vector<Date>& dates)
{
    for (Date& d : dates)
    {
        d.showDate();
    }
}
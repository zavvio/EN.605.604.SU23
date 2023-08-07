#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include "Serializable.h"
#include "Date.h"

template <class T>
class SerializableDate : public Serializable<T>
{
public:
    SerializableDate(T& object, std::string filePath) : Serializable<T>(object, filePath) {};
    ~SerializableDate() = default;
    void read(bool isBinary = false) const;
    void write(bool isBinary = false) const;
    void display() const;
};

// Template specialization
template <> void SerializableDate<std::vector<Date>>::read(bool isBinary) const;
template <> void SerializableDate<std::vector<Date>>::write(bool isBinary) const;
template <> void SerializableDate<std::vector<Date>>::display() const;
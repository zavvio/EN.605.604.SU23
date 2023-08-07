#pragma once

#include "DevUtil.h"

template <class T>
class Serializable
{
protected:
    std::string filePath;
    T& object;

public:
    Serializable(T& object, std::string filePath) : object{ object }, filePath{ filePath } {};
    ~Serializable() = default;
    void setFilePath(std::string path) { filePath = path; }
    virtual void read(bool isBinary = false) const {};
    virtual void write(bool isBinary = false) const {};
    virtual void display() const { std::cout << "WHAT!?\n"; };
};
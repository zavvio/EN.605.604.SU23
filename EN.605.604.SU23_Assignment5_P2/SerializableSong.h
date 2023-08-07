#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include "Serializable.h"
#include "Song.h"

template <class T>
class SerializableSong : public Serializable<T>
{
public:
    SerializableSong(T& object, std::string filePath) : Serializable<T>(object, filePath) {};
    ~SerializableSong() = default;
    void read(bool isBinary = false) const;
    void write(bool isBinary = false) const;
    void display() const;
};

// Template specialization
template <> void SerializableSong<std::vector<Song>>::read(bool isBinary) const;
template <> void SerializableSong<std::vector<Song>>::write(bool isBinary) const;
template <> void SerializableSong<std::vector<Song>>::display() const;
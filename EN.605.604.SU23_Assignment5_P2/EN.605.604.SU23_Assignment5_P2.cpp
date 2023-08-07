// EN.605.604.SU23_Assignment5_P2.cpp

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include "Date.h"
#include "Song.h"
#include "Serializable.h"
#include "SerializableDate.h"
#include "SerializableSong.h"

using namespace std;

int main()
{
    cout << "########## Assignment 5 P2 - File I/O (for various classes) via Template + Strategy Pattern ##########" << endl;

    cout << endl << "#################### Serializing collection of Song objects ####################" << endl << endl;

    vector<Song> songs
    { // Provide some predefined songs to save some typing.
        { "I Dreamed a Dream", "Lea Salonga", "Musical", {"Les Miserables", "Glee", "Susan Boyle"}},
        { "Never Gonna Give You Up", "Rick Astley", "Dance Pop", {"Whenever You Need Somebody"}},
        { "Rhapsody in Blue", "George Gershwin", "Orchestral Jazz", {"Gershwin Plays Gershwin", "Leonard Bernstein"}}
    };
    Serializable<vector<Song>>* serializer = new SerializableSong<vector<Song>>(songs, "serialized_text.txt");
    serializer->write(false);
    serializer->setFilePath("serialized_binary.txt");
    serializer->write(true);
    delete serializer;

    // Using a clean vector to read & display data from file.
    vector<Song> songsFromFile;
    serializer = new SerializableSong<vector<Song>>(songsFromFile, "serialized_text.txt");
    serializer->read(false);
    serializer->display();
    delete serializer;
    songsFromFile.clear();
    serializer = new SerializableSong<vector<Song>>(songsFromFile, "serialized_binary.txt");
    serializer->read(true);
    serializer->display();
    delete serializer;

    cout << endl << "#################### Serializing collection of Date objects ####################" << endl << endl;

    vector<Date> dates
    { // Provide some predefined dates
        { 1, 1, 2023 },
        { 4, 7, 2023 },
        { 25, 12, 2023 }
    };
    Serializable<vector<Date>>* serializer_dates = new SerializableDate<vector<Date>>(dates, "serialized_text_dates.txt");
    serializer_dates->write(false);
    serializer_dates->setFilePath("serialized_binary_dates.txt");
    serializer_dates->write(true);
    delete serializer_dates;

    // Using a clean vector to read & display data from file.
    vector<Date> datesFromFile;
    serializer_dates = new SerializableDate<vector<Date>>(datesFromFile, "serialized_text_dates.txt");
    serializer_dates->read(false);
    serializer_dates->display();
    delete serializer_dates;
    datesFromFile.clear();
    serializer_dates = new SerializableDate<vector<Date>>(datesFromFile, "serialized_binary_dates.txt");
    serializer_dates->read(true);
    serializer_dates->display();
    delete serializer_dates;

    return 0;
}

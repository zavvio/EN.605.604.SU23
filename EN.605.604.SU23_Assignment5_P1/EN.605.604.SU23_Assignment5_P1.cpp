// EN.605.604.SU23_Assignment5_P1.cpp

#include <algorithm>
#include <vector>
#include "Song.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	cout << "Assignment 5 P1 - Sort Song Collection (3 songs pre-populated)" << endl;

    vector<Song> songs
    { // Provide some predefined songs to save some typing.
        { "I Dreamed a Dream", "Lea Salonga", "Musical"},
        { "Rhapsody in Blue", "George Gershwin", "Orchestral Jazz" },
        { "Never Gonna Give You Up", "Rick Astley", "Dance Pop"}
    };

    UserInterface anInterface{ songs };
    anInterface.executeSelection();

	return 0;
}

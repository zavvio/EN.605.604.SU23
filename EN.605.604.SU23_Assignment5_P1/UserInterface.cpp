#include "UserInterface.h"

//============================================================
//                      PUBLIC FUNCTIONS                     =
//============================================================

UserInterface::UserInterface(vector<Song>& songs) : _songs{ songs } {};

void UserInterface::executeSelection()
{
    while (menuChoice != 6)
    {
        displayChoices();
        getUserInput();
        switch (menuChoice)
        {
        case 1: // interactive CLI prompt to add song to collection
            inputSong();
            break;
        case 2: // display in as-is order
            displaySongCollection(_songs, 0);
            break;
        case 3: // display in order sorted alphabetically by artist name
            displaySongCollection(_songs, 1);
            break;
        case 4: // display in order sorted alphabetically by title
            displaySongCollection(_songs, 2);
            break;
        case 5: // display in order sorted alphabetically by genre
            displaySongCollection(_songs, 3);
            break;
        case 6:
            cout << "Program Ending." << endl;
            break;
        default:
            cerr << "[ERROR] Unrecognized menu choice." << endl;
        }
    }
}

//============================================================
//                     PRIVATE FUNCTIONS                     =
//============================================================

void UserInterface::displayChoices()
{
    vector<string> choices {
        "1 - input new song",
        "2 - display song collection (as-is)",
        "3 - display song collection (sorted alphabetically by artist name)",
        "4 - display song collection (sorted alphabetically by title)",
        "5 - display song collection (sorted alphabetically by genre)",
        "6 - quit"
    };

    cout << "====================================== Main Menu ======================================" << endl;
    for (int i = 0; i < choices.size(); i++)
        cout << choices[i] << endl;
    cout << "Please enter one of the options [1 - " << choices.size() << "]: ";
}

// Assumption: User will input an expected valid integer as option.
// No advanced parsing is done here for brevity.
void UserInterface::getUserInput()
{
    bool invalid = true;
    menuChoice = -1;
    do
    {
        try
        {
            cin >> menuChoice;
        }
        catch (invalid_argument& e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "Unknown error in " << __FUNCTION__ << endl;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        invalid = menuChoice < 1 || menuChoice > 6;
        if (invalid)
        {
            cout << "Invalid input, please try again: ";
        }
    } while (invalid);
}

// A new Song object (based on user input) will be added to the collection after this function call.
void UserInterface::inputSong()
{
    string title = "";
    string artistName = "";
    string genre = "";
    while (title == "")
    {
        cout << "Enter a new song title: ";
        getline(cin, title);
    }
    while (artistName == "")
    {
        cout << "Enter artist name for the song: ";
        getline(cin, artistName);
    }
    while (genre == "")
    {
        cout << "Enter genre of the song: ";
        getline(cin, genre);
    }
    _songs.push_back(Song(title, artistName, genre));
}

// Utilize functors to customize sort before showing Song collection.
void UserInterface::displaySongCollection(vector<Song> songs, int sortOption)
{
    switch (sortOption)
    {
    case 1:
        sort(songs.begin(), songs.end(), lessByArtistName());
        break;
    case 2:
        sort(songs.begin(), songs.end(), lessByTitle());
        break;
    case 3:
        sort(songs.begin(), songs.end(), lessByGenre());
        break;
    default:
        break;
    }

    cout << "==========================================================================================" << endl;
    for (Song& s : songs)
    {
        cout << "Title: " << left << setw(25) << s.getTitle() << " | Artist: " << left << setw(15) << s.getArtistName() << " | Genre: " << s.getGenre() << endl;
    }
}
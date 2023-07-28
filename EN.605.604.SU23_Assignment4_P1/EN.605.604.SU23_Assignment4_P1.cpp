// EN.605.604.SU23_Assignment4_P1.cpp

#include <list>
#include "Movie.h"

using namespace std;

void input_stage(list<Movie>& movies);
void reorder_stage(list<Movie>& movies);

int main()
{
    cout << "Assignment 4 P1 - Movie Ranking" << endl;
    cout << "[User is expected to provide proper inputs, explicit input check is out of scope.]" << endl;

    list<Movie> movies
    { // Provide some predefined movies to save some typing.
        { "Star Wars Episode IV - A New Hope", 1977 },
        { "The Terminator", 1984 },
        { "Jurassic Park", 1993 },
        { "Titanic", 1997 },
        { "The Matrix", 1999 },
        { "I, Robot", 2004 }
    };

    input_stage(movies);
    reorder_stage(movies);

    return 0;
}

// UI prompt for user to enter all new movie records (name and production year).
void input_stage(list<Movie>& movies)
{
    string input = "";
    int year = 0;
    cout << "There are " << movies.size() << " predefined movies in the database:" << endl;
    for (Movie& movie : movies)
    {
        cout << "\t(" << movie.getYear() << ") " << movie.getName() << endl;
    }

    while (true)
    {
        cout << "Enter new movie name (or \"done\" to move on): ";
        getline(cin, input);
        if (input == "done") break;
        if (input == "") continue;
        cout << "Enter production year: ";
        cin >> year;
        cin.clear();
        cin.ignore(10000, '\n');
        movies.push_back(Movie(input, year));
    }
}

// UI prompt for user to reorder any movie.
// User select a movie based on existing rank, the movie will then be reordered to the new rank.
void reorder_stage(list<Movie>& movies)
{
    list<Movie>::iterator itr;
    Movie temp;
    int choice, newRank, currRank;
    while (true)
    {
        cout << "==================== Movie Rank Chart ====================" << endl;
        for (itr = begin(movies), currRank = 1; itr != end(movies); ++itr, currRank++)
        {
            cout << "Rank " << currRank << ": (" << itr->getYear() << ") " << itr->getName() << endl;
        }

        // Get target movie
        cout << "Current rank of movie to reorder (1 - " << movies.size() << ") (enter 0 to quit): ";
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        else if (choice < 1 || movies.size() < choice)
        {
            cout << "[Error] Invalid rank." << endl;
            continue;
        }

        // Get target rank
        cout << "New target rank (1 - " << movies.size() << "): ";
        cin >> newRank;
        if (newRank < 1 || movies.size() < newRank)
        {
            cout << "[Error] Invalid rank." << endl;
            continue;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        // Reorder movie
        for (itr = begin(movies), currRank = 1; currRank < choice; currRank++, ++itr);
        temp = *itr;
        movies.erase(itr);
        for (itr = begin(movies), currRank = 1; currRank < newRank; currRank++, ++itr);
        movies.insert(itr, temp);
    }
}
// EN.605.604.SU23_Assignment4_P1.cpp : Defines the entry point for the application.

#include <sstream>
#include <vector>
#include "DevUtil.h"
#include "Movie.h"

using namespace std;

void input_stage(vector<Movie>& movies)
{
    string input = "";
    int year = 0;
    cout << "There are " << movies.size() << " predefined movies in the database:" << endl;
    for (Movie& movie : movies)
    {
        cout << "\t(" << movie.getYear() << ") " << movie.getName() << endl;
    }

    do
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
    } while (true);
}

void reorder_stage(vector<Movie>& movies)
{
    Movie temp;
    int choice, newRank;
    do
    {
        cout << "==================== Movie Rank Chart ====================" << endl;
        for (int i = 0; i < movies.size(); i++)
        {
            cout << "Rank " << i + 1 << ": (" << movies[i].getYear() << ") " << movies[i].getName() << endl;
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
        temp = movies[choice - 1];
        movies.erase(movies.begin() + (choice - 1));
        movies.insert(movies.begin() + (newRank - 1), temp);
    } while (true);
}

int main()
{
    cout << "Hello Assignment 4 P1 - Movie Ranking" << endl;
    cout << "[User is expected to provide proper inputs, explicit input check is out of scope.]" << endl;

    vector<Movie> movies
    {
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
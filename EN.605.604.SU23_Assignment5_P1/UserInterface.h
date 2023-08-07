#pragma once

#include <algorithm>
#include <vector>
#include "DevUtil.h"
#include "Song.h"

using namespace std;

class UserInterface
{
public:
    UserInterface(vector<Song>& songs);
    void executeSelection();

private:
    vector<Song>& _songs;
    int menuChoice { 0 };

    void displayChoices();
    void getUserInput();
    void inputSong();
    void displaySongCollection(vector<Song> songs, int sortOption);
};

// Functor to sort alphabetically by title.
class lessByTitle
{
public:
    bool operator()(const Song& lSong, const Song& rSong) const {
        return lSong.getTitle() < rSong.getTitle();
    }
};

// Functor to sort alphabetically by artist name.
class lessByArtistName
{
public:
    bool operator()(const Song& lSong, const Song& rSong) const {
        return lSong.getArtistName() < rSong.getArtistName();
    }
};

// Functor to sort alphabetically by genre.
class lessByGenre
{
public:
    bool operator()(const Song& lSong, const Song& rSong) const {
        return lSong.getGenre() < rSong.getGenre();
    }
};
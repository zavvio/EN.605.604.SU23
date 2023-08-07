#include "Song.h"

Song::Song(std::string title, std::string artistName, std::string genre, std::vector<std::string> albums)
    : title{ title }, artistName{ artistName }, genre{ genre }, albums{ albums }
{}

std::string Song::getTitle() const
{
    return title;
}

void Song::setTitle(std::string title)
{
    this->title = title;
}

std::string Song::getArtistName() const
{
    return artistName;
}

void Song::setArtistName(std::string artistName)
{
    this->artistName = artistName;
}

std::string Song::getGenre() const
{
    return genre;
}

void Song::setGenre(std::string genre)
{
    this->genre = genre;
}

const std::vector<std::string>* Song::getAlbums() const
{
    return &albums;
}

void Song::addAlbum(std::string album)
{
    albums.push_back(album);
}

void Song::showSong() const
{
    using namespace std;
    cout << "Title: " << left << setw(25) << getTitle();
    cout << " | Artist: " << left << setw(15) << getArtistName();
    cout << " | Genre: " << getGenre() << endl;
    cout << "--> Exist in " << getAlbums()->size() << " Albums: ";
    for (const string& a : *(getAlbums()))
    {
        cout << a << ", ";
    }
    cout << endl;
}
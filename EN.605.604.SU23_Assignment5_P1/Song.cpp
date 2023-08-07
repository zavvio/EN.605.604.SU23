#include "Song.h"

Song::Song(std::string title, std::string artistName, std::string genre)
    : title{ title }, artistName{ artistName }, genre{ genre }
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
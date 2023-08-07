#pragma once

#include "DevUtil.h"

class Song
{
public:
    Song(std::string title = "", std::string artistName = "", std::string genre = "");
    std::string getTitle() const;
    void setTitle(std::string title);
    std::string getArtistName() const;
    void setArtistName(std::string artistName);
    std::string getGenre() const;
    void setGenre(std::string genre);

private:
    std::string title;
    std::string artistName;
    std::string genre;
};
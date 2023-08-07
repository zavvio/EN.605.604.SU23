#pragma once

#include <vector>
#include "DevUtil.h"

class Song
{
public:
    Song(std::string title = "", std::string artistName = "", std::string genre = "", std::vector<std::string> albums = {});
    std::string getTitle() const;
    void setTitle(std::string title);
    std::string getArtistName() const;
    void setArtistName(std::string artistName);
    std::string getGenre() const;
    void setGenre(std::string genre);
    const std::vector<std::string>* getAlbums() const;
    void addAlbum(std::string album);
    void showSong() const;

private:
    std::string title;
    std::string artistName;
    std::string genre;
    std::vector<std::string> albums; // dynamically sized member
};
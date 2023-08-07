#include "SerializableSong.h"

using namespace std;

// ==================== HELPER FUNCTIONS ====================

void __writeSongsToTextFile(std::vector<Song>& songs, std::string filePath);
void __readSongsFromTextFile(std::vector<Song>& songs, std::string filePath);
void __writeSongsToBinaryFile(std::vector<Song>& songs, std::string filePath);
void __readSongsFromBinaryFile(std::vector<Song>& songs, std::string filePath);
void __displaySongs(std::vector<Song>& songs);

// Template instantiation
template class SerializableSong<std::vector<Song>>;

// ==================== BASIC TEMPLATE DEFINITION ====================

template <class T> void SerializableSong<T>::read(bool isBinary) const
{}

template <class T> void SerializableSong<T>::write(bool isBinary) const
{}

template <class T> void SerializableSong<T>::display() const
{}

// ==================== TEMPLATE SPECIALIZATION ====================

template <> void SerializableSong<std::vector<Song>>::read(bool isBinary) const
{
    if (isBinary)
    {
        __readSongsFromBinaryFile(object, filePath);
    }
    else
    {
        __readSongsFromTextFile(object, filePath);
    }
}

template <> void SerializableSong<std::vector<Song>>::write(bool isBinary) const
{
    if (isBinary)
    {
        __writeSongsToBinaryFile(object, filePath);
    }
    else
    {
        __writeSongsToTextFile(object, filePath);
    }
}

// Specialized display function for vector<Song> class.
template <> void SerializableSong<std::vector<Song>>::display() const
{
    __displaySongs(object);
}

// ==================== HELPER FUNCTIONS DEFINITION ====================

// Serialize Song collection to file in ASCII mode.
void __writeSongsToTextFile(std::vector<Song>& songs, std::string filePath)
{
    // open file for output
    ofstream outputFile{ filePath, ios::out };

    // exit if unable to open file
    if (!outputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    const vector<string>* albums;
    std::stringstream ss;
    ss << songs.size() << endl;
    for (Song& s : songs)
    {
        ss << quoted(s.getTitle()) << endl;
        ss << quoted(s.getArtistName()) << endl;
        ss << quoted(s.getGenre()) << endl;
        albums = s.getAlbums();
        ss << albums->size() << endl; // must record dynamic memory size
        for (const string& a : *albums)
        {
            ss << quoted(a) << endl;
        }
    }
    outputFile << ss.rdbuf();
    outputFile.close();
    cout << "==================== Written to text file {" << filePath << "} successfully ====================" << endl;
}

// Deserialize Song collection from file in ASCII mode.
void __readSongsFromTextFile(std::vector<Song>& songs, std::string filePath)
{
    int sizeSongs, sizeAlbums;
    string bufferStr;
    Song song;
    songs.clear();
    // open file for input
    ifstream inputFile{ filePath, ios::in };

    // exit if unable to open file
    if (!inputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    // read file input
    inputFile >> sizeSongs;
    for (int i = 0; i < sizeSongs; i++)
    {
        song = Song();
        inputFile >> quoted(bufferStr);
        song.setTitle(bufferStr);
        inputFile >> quoted(bufferStr);
        song.setArtistName(bufferStr);
        inputFile >> quoted(bufferStr);
        song.setGenre(bufferStr);
        inputFile >> sizeAlbums;
        for (int j = 0; j < sizeAlbums; j++)
        {
            inputFile >> quoted(bufferStr);
            song.addAlbum(bufferStr);
        }
        songs.push_back(song);
    }
    inputFile.close();
    cout << "==================== Read from text file {" << filePath << "} successfully ====================" << endl;
}

// Serialize Song collection to file in binary mode.
void __writeSongsToBinaryFile(std::vector<Song>& songs, std::string filePath)
{
    // open file for output
    ofstream outputFile{ filePath, ios::out | ios::binary };

    // exit if unable to open file
    if (!outputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    const vector<string>* albums;
    size_t size = songs.size(); // must record dynamic memory size
    outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (Song& s : songs)
    {
        size = s.getTitle().size(); // string is also dynamically sized memory, must record size.
        outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outputFile.write(reinterpret_cast<const char*>(s.getTitle().c_str()), size);
        size = s.getArtistName().size();
        outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outputFile.write(reinterpret_cast<const char*>(s.getArtistName().c_str()), size);
        size = s.getGenre().size();
        outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outputFile.write(reinterpret_cast<const char*>(s.getGenre().c_str()), size);
        // must record size for dynamic vector memory to facilitate future read
        albums = s.getAlbums();
        size = albums->size();
        outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const string& a : *albums)
        {
            size = a.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            outputFile.write(reinterpret_cast<const char*>(a.c_str()), size);
        }
    }
    outputFile.close();
    cout << "==================== Written to binary file {" << filePath << "} successfully ====================" << endl;
}

// Deserialize Song collection from file in binary mode.
void __readSongsFromBinaryFile(std::vector<Song>& songs, std::string filePath)
{
    size_t sizeSongs, sizeAlbums, size;
    char bufferChar[300];
    string bufferStr;
    Song song;
    songs.clear();
    // open file for input
    ifstream inputFile{ filePath, ios::in | ios::binary };

    // exit if unable to open file
    if (!inputFile)
    {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    // read file input
    inputFile.read(reinterpret_cast<char*>(&sizeSongs), sizeof(sizeSongs));
    for (int i = 0; i < sizeSongs; i++)
    {
        song = Song();
        // use pre-recorded size to determine dynamic string length to read in
        inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (size >= 300)
            throw out_of_range("bufferChar is too small to hold all data.");
        inputFile.read(bufferChar, size);
        bufferChar[size] = '\0';
        song.setTitle({ bufferChar });

        inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (size >= 300)
            throw out_of_range("bufferChar is too small to hold all data.");
        inputFile.read(bufferChar, size);
        bufferChar[size] = '\0';
        song.setArtistName({ bufferChar });

        inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (size >= 300)
            throw out_of_range("bufferChar is too small to hold all data.");
        inputFile.read(bufferChar, size);
        bufferChar[size] = '\0';
        song.setGenre({ bufferChar });

        // read in dynamically sized object based on pre-recorded size
        inputFile.read(reinterpret_cast<char*>(&sizeAlbums), sizeof(sizeAlbums));
        for (int j = 0; j < sizeAlbums; j++)
        {
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            if (size >= 300)
                throw out_of_range("bufferChar is too small to hold all data.");
            inputFile.read(bufferChar, size);
            bufferChar[size] = '\0';
            song.addAlbum({ bufferChar });
        }
        songs.push_back(song);
    }
    inputFile.close();
    cout << "==================== Read from binary file {" << filePath << "} successfully ====================" << endl;
}

void __displaySongs(std::vector<Song>& songs)
{
    for (Song& s : songs)
    {
        s.showSong();
    }
}
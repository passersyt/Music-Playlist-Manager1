#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <string>

class Playlist
{
private:

    Song* head;
    Song* tail;
    Song* current;

    int totalSongs;

public:

    Playlist();

    ~Playlist();

    // Basic Functions
    bool isEmpty();

    // Add Song
    void addSong();

    // Display Playlist
    void displayPlaylist();

    // Play Song
    void playSong();

    // Next Song
    void nextSong();

    // Previous Song
    void previousSong();

    // Search
    void searchSong();

    // Update
    void updateSong();

    // Delete
    void deleteSong();

    // Favourite
    void addFavourite();

    void showFavouriteSongs();

    // Sort
    void sortPlaylist();

    // Shuffle
    void shufflePlaylist();

    // Statistics
    void statistics();

    // File Handling
    void saveToFile();

    void loadFromFile();

private:

    Song* searchByID(int id);

    Song* searchByName(std::string name);

    void swapData(Song* a, Song* b);

};

#endif

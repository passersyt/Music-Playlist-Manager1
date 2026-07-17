#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
public:
    int id;
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    std::string duration;

    bool favourite;

    Song* next;
    Song* prev;

    Song(
        int id,
        std::string title,
        std::string artist,
        std::string album,
        std::string genre,
        std::string duration
    );
};

#endif

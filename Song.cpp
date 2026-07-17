#include "Song.h"

Song::Song(
    int id,
    std::string title,
    std::string artist,
    std::string album,
    std::string genre,
    std::string duration
)
{
    this->id=id;
    this->title=title;
    this->artist=artist;
    this->album=album;
    this->genre=genre;
    this->duration=duration;

    favourite=false;

    next=nullptr;
    prev=nullptr;
}

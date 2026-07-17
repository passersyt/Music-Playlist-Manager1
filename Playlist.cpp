#include "Playlist.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

// Constructor
Playlist::Playlist()
{
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    totalSongs = 0;
}

// Destructor
Playlist::~Playlist()
{
    Song* temp = head;

    while(temp != nullptr)
    {
        Song* next = temp->next;
        delete temp;
        temp = next;
    }
}

// Check Playlist Empty
bool Playlist::isEmpty()
{
    return head == nullptr;
}

// Search by ID
Song* Playlist::searchByID(int id)
{
    Song* temp = head;

    while(temp != nullptr)
    {
        if(temp->id == id)
            return temp;

        temp = temp->next;
    }

    return nullptr;
}

// Search by Name
Song* Playlist::searchByName(string name)
{
    Song* temp = head;

    while(temp != nullptr)
    {
        if(temp->title == name)
            return temp;

        temp = temp->next;
    }

    return nullptr;
}

// Swap Data (Used for Sorting)
void Playlist::swapData(Song* a, Song* b)
{
    swap(a->id,b->id);
    swap(a->title,b->title);
    swap(a->artist,b->artist);
    swap(a->album,b->album);
    swap(a->genre,b->genre);
    swap(a->duration,b->duration);
    swap(a->favourite,b->favourite);
}

// Add Song
void Playlist::addSong()
{
    int id;
    string title;
    string artist;
    string album;
    string genre;
    string duration;

    cout<<"\n========== ADD SONG ==========\n";

    cout<<"Song ID : ";
    cin>>id;
    cin.ignore();

    if(searchByID(id)!=nullptr)
    {
        cout<<"\nSong ID Already Exists.\n";
        return;
    }

    cout<<"Song Name : ";
    getline(cin,title);

    cout<<"Artist : ";
    getline(cin,artist);

    cout<<"Album : ";
    getline(cin,album);

    cout<<"Genre : ";
    getline(cin,genre);

    cout<<"Duration (mm:ss) : ";
    getline(cin,duration);

    Song* newSong = new Song(
        id,
        title,
        artist,
        album,
        genre,
        duration
    );

    if(head==nullptr)
    {
        head = tail = current = newSong;
    }
    else
    {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    totalSongs++;

    cout<<"\nSong Added Successfully.\n";
}
void Playlist::displayPlaylist()
{
    if(isEmpty())
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════════════╗\n";
        cout << "║             Playlist is Empty               ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
        return;
    }

    Song* temp = head;

    cout << "\n";
    cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════\n";
    cout << "                                   🎵 YOUR PLAYLIST 🎵\n";
    cout << "══════════════════════════════════════════════════════════════════════════════════════════════════════\n";

    cout << left
         << setw(6)  << "ID"
         << setw(28) << "TITLE"
         << setw(22) << "ARTIST"
         << setw(18) << "ALBUM"
         << setw(12) << "TIME"
         << setw(8)  << "FAV"
         << "STATUS"
         << endl;

    cout << "------------------------------------------------------------------------------------------------------\n";

    while(temp != nullptr)
    {
        cout << left
             << setw(6)  << temp->id
             << setw(28) << temp->title
             << setw(22) << temp->artist
             << setw(18) << temp->album
             << setw(12) << temp->duration;

        if(temp->favourite)
            cout << setw(8) << "❤️";
        else
            cout << setw(8) << "-";

        if(temp == current)
            cout << "▶ NOW PLAYING";
        else
            cout << "";

        cout << endl;

        temp = temp->next;
    }

    cout << "------------------------------------------------------------------------------------------------------\n";

    cout << "\n🎵 Total Songs : " << totalSongs << endl;
}
void Playlist::playSong()
{
    if(isEmpty())
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════════╗\n";
        cout << "║          Playlist is Empty               ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        return;
    }

    int id;

    cout << "\nEnter Song ID : ";
    cin >> id;

    Song* song = searchByID(id);

    if(song == nullptr)
    {
        cout << "\n❌ Song Not Found.\n";
        return;
    }

    current = song;

    cout << "\n";
    cout << "═══════════════════════════════════════════════════════════════\n";
    cout << "                    🎧 NOW PLAYING\n";
    cout << "═══════════════════════════════════════════════════════════════\n";

    cout << "🎵 Title      : " << current->title << endl;
    cout << "🎤 Artist     : " << current->artist << endl;
    cout << "💿 Album      : " << current->album << endl;
    cout << "🎼 Genre      : " << current->genre << endl;
    cout << "⏱ Duration   : " << current->duration << endl;

    cout << "\n";

    cout << "▶ ";

    for(int i=0;i<=35;i++)
    {
        cout << "█";
        cout.flush();
        Sleep(25);
    }

    cout << " 100%\n";

    cout << "⏮ Previous       ⏸ Pause       ⏭ Next\n";

    cout << "═══════════════════════════════════════════════════════════════\n";
}
void Playlist::nextSong()
{
    if(isEmpty())
    {
        cout << "\nPlaylist is Empty.\n";
        return;
    }

    if(current == nullptr)
    {
        cout << "\nNo song selected.\n";
        return;
    }

    if(current->next == nullptr)
    {
        cout << "\nAlready at the last song.\n";
        return;
    }

    current = current->next;

    cout << "\n▶ Now Playing : " << current->title << endl;
}
void Playlist::previousSong()
{
    if(isEmpty())
    {
        cout << "\nPlaylist is Empty.\n";
        return;
    }

    if(current == nullptr)
    {
        cout << "\nNo song selected.\n";
        return;
    }

    if(current->prev == nullptr)
    {
        cout << "\nAlready at the first song.\n";
        return;
    }

    current = current->prev;

    cout << "\n▶ Now Playing : " << current->title << endl;
}
void Playlist::searchSong()
{
    if(isEmpty())
    {
        cout << "\nPlaylist is Empty.\n";
        return;
    }

    int choice;

    cout << "\nSearch By\n";
    cout << "1. Song ID\n";
    cout << "2. Song Name\n";
    cout << "Enter Choice : ";
    cin >> choice;
    cin.ignore();

    Song* song = nullptr;

    if(choice == 1)
    {
        int id;

        cout << "Enter Song ID : ";
        cin >> id;

        song = searchByID(id);
    }
    else if(choice == 2)
    {
        string title;

        cout << "Enter Song Name : ";
        getline(cin,title);

        song = searchByName(title);
    }
    else
    {
        cout << "\nInvalid Choice.\n";
        return;
    }

    if(song == nullptr)
    {
        cout << "\nSong Not Found.\n";
        return;
    }

    cout << "\n========== SONG DETAILS ==========\n";

    cout << "ID        : " << song->id << endl;
    cout << "Title     : " << song->title << endl;
    cout << "Artist    : " << song->artist << endl;
    cout << "Album     : " << song->album << endl;
    cout << "Genre     : " << song->genre << endl;
    cout << "Duration  : " << song->duration << endl;
    cout << "Favourite : " << (song->favourite ? "Yes" : "No") << endl;
}
void Playlist::updateSong()
{
    if(isEmpty())
    {
        cout << "\nPlaylist is Empty.\n";
        return;
    }

    int id;

    cout << "\nEnter Song ID : ";
    cin >> id;
    cin.ignore();

    Song* song = searchByID(id);

    if(song == nullptr)
    {
        cout << "\nSong Not Found.\n";
        return;
    }

    cout << "\nEnter New Details\n";

    cout << "Song Name : ";
    getline(cin,song->title);

    cout << "Artist : ";
    getline(cin,song->artist);

    cout << "Album : ";
    getline(cin,song->album);

    cout << "Genre : ";
    getline(cin,song->genre);

    cout << "Duration : ";
    getline(cin,song->duration);

    cout << "\nSong Updated Successfully.\n";
}
void Playlist::deleteSong()
{
    if(isEmpty())
    {
        cout << "\nPlaylist is Empty.\n";
        return;
    }

    int id;

    cout << "\nEnter Song ID : ";
    cin >> id;

    Song* song = searchByID(id);

    if(song == nullptr)
    {
        cout << "\nSong Not Found.\n";
        return;
    }

    if(song == head && song == tail)
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
    else if(song == head)
    {
        head = head->next;
        head->prev = nullptr;

        if(current == song)
            current = head;
    }
    else if(song == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;

        if(current == song)
            current = tail;
    }
    else
    {
        song->prev->next = song->next;
        song->next->prev = song->prev;

        if(current == song)
            current = song->next;
    }

    delete song;

    totalSongs--;

    cout << "\nSong Deleted Successfully.\n";
}
void Playlist::addFavourite()
{
    if(isEmpty())
    {
        cout<<"\nPlaylist is Empty.\n";
        return;
    }

    int id;

    cout<<"\nEnter Song ID : ";
    cin>>id;

    Song* song=searchByID(id);

    if(song==nullptr)
    {
        cout<<"\nSong Not Found.\n";
        return;
    }

    song->favourite=true;

    cout<<"\nSong Added to Favourite.\n";
}
void Playlist::showFavouriteSongs()
{
    if(isEmpty())
    {
        cout << "\n";
        cout << "╔════════════════════════════════════════════╗\n";
        cout << "║           Playlist is Empty                ║\n";
        cout << "╚════════════════════════════════════════════╝\n";
        return;
    }

    Song* temp = head;
    bool found = false;

    cout << "\n";
    cout << "══════════════════════════════════════════════════════════════════════════════\n";
    cout << "                          ❤️ FAVORITE SONGS ❤️\n";
    cout << "══════════════════════════════════════════════════════════════════════════════\n";

    cout << left
         << setw(6)  << "ID"
         << setw(28) << "TITLE"
         << setw(22) << "ARTIST"
         << setw(15) << "ALBUM"
         << "STATUS" << endl;

    cout << "-----------------------------------------------------------------------------\n";

    while(temp != nullptr)
    {
        if(temp->favourite)
        {
            found = true;

            cout << left
                 << setw(6)  << temp->id
                 << setw(28) << temp->title
                 << setw(22) << temp->artist
                 << setw(15) << temp->album;

            if(temp == current)
                cout << "▶ PLAYING";
            else
                cout << "❤️ Favourite";

            cout << endl;
        }

        temp = temp->next;
    }

    if(!found)
    {
        cout << "\nNo Favourite Songs Found.\n";
    }

    cout << "══════════════════════════════════════════════════════════════════════════════\n";
}
void Playlist::shufflePlaylist()
{
    if(isEmpty())
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║          Playlist is Empty           ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        return;
    }

    if(totalSongs <= 1)
    {
        cout << "\nNeed at least 2 songs to shuffle.\n";
        return;
    }

    srand((unsigned)time(NULL));

    int randomIndex = rand() % totalSongs;

    Song* temp = head;

    for(int i = 0; i < randomIndex; i++)
        temp = temp->next;

    current = temp;

    cout << "\n";
    cout << "🎵 Shuffling Playlist ";

    for(int i = 0; i < 25; i++)
    {
        cout << "█";
        cout.flush();

#ifdef _WIN32
        Sleep(35);
#else
        usleep(35000);
#endif
    }

    cout << "\n\n";

    cout << "═══════════════════════════════════════════════\n";
    cout << "          🔀 RANDOM SONG SELECTED\n";
    cout << "═══════════════════════════════════════════════\n";

    cout << "🎵 " << current->title << endl;
    cout << "🎤 " << current->artist << endl;
    cout << "💿 " << current->album << endl;
    cout << "⏱ " << current->duration << endl;

    cout << "\n▶ Enjoy Your Music!\n";

    cout << "═══════════════════════════════════════════════\n";
}
void Playlist::sortPlaylist()
{
    if(isEmpty())
    {
        cout<<"\nPlaylist Empty.\n";
        return;
    }

    bool swapped;

    do
    {
        swapped=false;

        Song* temp=head;

        while(temp->next!=nullptr)
        {
            if(temp->title>temp->next->title)
            {
                swapData(temp,temp->next);
                swapped=true;
            }

            temp=temp->next;
        }

    }while(swapped);

    cout<<"\nPlaylist Sorted Successfully.\n";
}
void Playlist::statistics()
{
    int favouriteCount = 0;

    Song* temp = head;

    while(temp != nullptr)
    {
        if(temp->favourite)
            favouriteCount++;

        temp = temp->next;
    }

    cout << "\n";

    cout << " ╔══════════════════════════════════════════════════════╗\n";
    cout << " ║               📊PLAYLIST STATISTICS                  ║\n";
    cout << " ╠══════════════════════════════════════════════════════╣\n";

    cout << " ║ 🎵 Total Songs      : "
         << setw(28) << left << totalSongs << "   ║\n";

    cout << " ║ ❤️ Favourite Songs   : "
         << setw(28) << left << favouriteCount << "   ║\n";

    if(current != nullptr)
    {
        cout << " ║ ▶ Currently Playing : "
             << setw(28) << left << current->title << "   ║\n";
    }
    else
    {
        cout << " ║ ▶ Currently Playing : "
             << setw(28) << left << "None" << "   ║\n";
    }

    cout << " ║ 💿 Playlist Status  : "
         << setw(28) << left
         << (totalSongs > 0 ? "Active" : "Empty")
         << "   ║\n";

    cout << " ╚══════════════════════════════════════════════════════╝\n";
}
void Playlist::saveToFile()
{
    ofstream file("songs.txt");

    Song* temp=head;

    while(temp!=nullptr)
    {
        file<<temp->id<<"|";
        file<<temp->title<<"|";
        file<<temp->artist<<"|";
        file<<temp->album<<"|";
        file<<temp->genre<<"|";
        file<<temp->duration<<"|";
        file<<temp->favourite<<endl;

        temp=temp->next;
    }

    file.close();
}
void Playlist::loadFromFile()
{
    ifstream file("songs.txt");

    if(!file)
        return;

    while(true)
    {
        int id;

        if(!(file>>id))
            break;

        file.ignore();

        string title;
        string artist;
        string album;
        string genre;
        string duration;
        bool favourite;

        getline(file,title,'|');
        getline(file,artist,'|');
        getline(file,album,'|');
        getline(file,genre,'|');
        getline(file,duration,'|');
        file>>favourite;
        file.ignore();

        Song* newSong=new Song(
            id,
            title,
            artist,
            album,
            genre,
            duration
        );

        newSong->favourite=favourite;

        if(head==nullptr)
        {
            head=tail=current=newSong;
        }
        else
        {
            tail->next=newSong;
            newSong->prev=tail;
            tail=newSong;
        }

        totalSongs++;
    }

    file.close();
}

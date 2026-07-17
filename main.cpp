#include <iostream>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include "Playlist.h"

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void logo()
{
    cout << "\n";
    cout << "╔═════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                 ║\n";
    cout << "║      ███████╗██████╗  ██████╗ ████████╗██╗███████╗██╗   ██╗     ║\n";
    cout << "║      ██╔════╝██╔══██╗██╔═══██╗╚══██╔══╝██║██╔════╝╚██╗ ██╔╝     ║\n";
    cout << "║      ███████╗██████╔╝██║   ██║   ██║   ██║█████╗   ╚████╔╝      ║\n";
    cout << "║      ╚════██║██╔═══╝ ██║   ██║   ██║   ██║██╔══╝    ╚██╔╝       ║\n";
    cout << "║      ███████║██║     ╚██████╔╝   ██║   ██║██║        ██║        ║\n";
    cout << "║      ╚══════╝╚═╝      ╚═════╝    ╚═╝   ╚═╝╚═╝        ╚═╝        ║\n";
    cout << "║                                                                 ║\n";
    cout << "║                 🎵 MUSIC PLAYLIST MANAGER 🎵                    ║\n";
    cout << "║                                                                 ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════╝\n";

    cout << "\n";
    cout << "               Doubly Linked List Based Music Player\n";
    cout << "-------------------------------------------------------------------\n";
}

void menu()
{
    cout << "\n";
    cout << " ╔══════════════════════════════════════════════════════════════╗\n";
    cout << " ║                       🎧 MAIN MENU                           ║\n";
    cout << " ╠══════════════════════════════════════════════════════════════╣\n";
    cout << " ║   1.  ➕  Add Song                                           ║\n";
    cout << " ║   2.  📃  Display Playlist                                   ║\n";
    cout << " ║   3.  ▶️  Play Song                                           ║\n";
    cout << " ║   4.  ⏭️  Next Song                                           ║\n";
    cout << " ║   5.  ⏮️  Previous Song                                       ║\n";
    cout << " ║   6.  🔍  Search Song                                        ║\n";
    cout << " ║   7.  ✏️  Update Song                                         ║\n";
    cout << " ║   8.  🗑️  Delete Song                                         ║\n";
    cout << " ║   9.  ❤️  Add to Favourite                                    ║\n";
    cout << " ║   10.  ⭐  Show Favourite Songs                              ║\n";
    cout << " ║   11.  🔀  Shuffle Playlist                                  ║\n";
    cout << " ║   12.  🔤  Sort Playlist                                     ║\n";
    cout << " ║   13.  📊  Playlist Statistics                               ║\n";
    cout << " ║   14.  💾  Save Playlist                                     ║\n";
    cout << " ║   15.  📂  Load Playlist                                     ║\n";
    cout << " ║   16.  🚪  Exit                                              ║\n";
    cout << " ╚══════════════════════════════════════════════════════════════╝\n";

   HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\n";

    SetConsoleTextAttribute(h,14);   // Yellow
    cout << "🎵 Choose an option (1-16): ";

    SetConsoleTextAttribute(h,15);   // White for user input 
}

int main()
{   SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");

    Playlist playlist;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    playlist.loadFromFile();

    int choice;

    do
    {
        clearScreen();

        SetConsoleTextAttribute(hConsole,10);

        logo();

        SetConsoleTextAttribute(hConsole,15);

        menu();

        while(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid Input.\n";
            cout << "Enter Again : ";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
            case 1:
                playlist.addSong();
                break;

            case 2:
                playlist.displayPlaylist();
                break;

            case 3:
                playlist.playSong();
                break;

            case 4:
                playlist.nextSong();
                break;

            case 5:
                playlist.previousSong();
                break;

            case 6:
                playlist.searchSong();
                break;

            case 7:
                playlist.updateSong();
                break;

            case 8:
                playlist.deleteSong();
                break;

            case 9:
                playlist.addFavourite();
                break;

            case 10:
                playlist.showFavouriteSongs();
                break;

            case 11:
                playlist.shufflePlaylist();
                break;

            case 12:
                playlist.sortPlaylist();
                break;

            case 13:
                playlist.statistics();
                break;

            case 14:
                playlist.saveToFile();
                cout << "\nPlaylist Saved Successfully.\n";
                break;

            case 15:
                playlist.loadFromFile();
                cout << "\nPlaylist Loaded Successfully.\n";
                break;

            case 16:
                playlist.saveToFile();
                cout << "\nThank You For Using Music Playlist Manager.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

        if(choice != 16)
            pauseScreen();

    }while(choice != 16);

    return 0;
}

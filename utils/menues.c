#include "utils.h"
#include "music.h"
#include "displayOptions.h"
#include "menues.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void MainMenu() {
    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printTitleScreen();
        printMenuOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 7 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            addNewSong();
            MainMenu();
            break;
        case 2:
            removeSong();
            MainMenu();
            break;
        case 3:
            changeSongInformations();
            MainMenu();
            break;
        case 4:
            displayListedSongs();
            break;
        case 5:
            displayMusicMenu();
            break;
        case 6:
            updateUserDataMenu();
            break;
        case 7:
            exitProgramm(0);
        default:
            break;
    }
}

void printTitleScreen() {
    printf("--------------------------------\n"
           "|                              |\n"
           "|          Song Rater          |\n"
           "|                              |\n"
           "--------------------------------\n");
}

void printListOptionsTitleScreen() {
    printf("-----------------------------------\n"
           "|                                 |\n"
           "|           Song Lister           |\n"
           "|                                 |\n"
           "-----------------------------------\n");
}

void printPlayMusicScreen(TSongInfos songs) {
    printf("  ____________________________________________________\n");
    printf(" /                                                    \\\n");
    printf("|   Song:       %-30s         |\n", songs.name);
    printf("|   Album:      %-30s         |\n", songs.album);
    printf("|   Artist:     %-30s         |\n", songs.artist);
    printf(" \\____________________________________________________/\n\n");
    printf("Controls:\n");
    printf("Space: Pause/Restart Playback\n");
    printf("Esc:   Stop Playback\n");
}

void updateUserDataMenu() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printTitleScreen();
        printChangeUserDataOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            updateSongListFilePathInUserDataFile();
            checkIfAllMusicFileEntriesAreValid();
            updateUserDataMenu();
            break;
        case 2:
            updateMusicFolderPathInUserDataFile();
            checkIfAllMusicFileEntriesAreValid();
            updateUserDataMenu();
            break;
        case 3:
            MainMenu();
            break;
        default:
            break;
    }
}

void printMenuOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  Add a new Song to Song List\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Delete a Song from song List\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Change Song Informations in Song List\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List Songs\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  Music\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  Change UserData\n", (selectedOption == 6) ? ">>" : "  ");
    printf("%s  Exit\n\n", (selectedOption == 7) ? ">>" : "  ");
}

void printListOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List all Songs\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Sorted\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List all Songs with Valid Music File\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 4) ? ">>" : "  ");
}

void printMusicOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  Add Music File for a Song\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Remove Music File for a Song\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Change Music File for a Song\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List all Songs with Valid Music File\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  Play a Song\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 6) ? ">>" : "  ");
}

void printChangeUserDataOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  Change SongList File Path\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Change Music Folder Path\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Name\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Sorted by Album\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List Sorted by Artist\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List every Entries from a given Genre\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List by Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  List by Rating\n", (selectedOption == 6) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 7) ? ">>" : "  ");
}

void printSortedListByNameOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Name (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Infos from a Given Song\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByAlbumOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Album (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entries from a given Album\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByArtistOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Artist (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entries from a given Artist\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByYearOfPublishingOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List (Newest - Oldest)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Oldest - Newest)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List Newer Than The Given Year\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List Older Than The Given Year\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List every Entries from a given Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 6) ? ">>" : "  ");
}

void printSortedListByRatingOptions(const int selectedOption) {
    printf("Chose a Option:\n");
    printf("%s  List (Best - Worse)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Worse - Best)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List every Entries from a given Rating\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 4) ? ">>" : "  ");
}

void displayMusicMenu() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printMusicOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            addMusicFile();
            displayMusicMenu();
            break;
        case 2:
            removeMusicFile();
            displayMusicMenu();
            break;
        case 3:
            changeMusicFile();
            displayMusicMenu();
            break;
        case 4:
            displayListedSongsWithValidMusicFile();
            displayMusicMenu();
        case 5:
            playMusic();
            displayMusicMenu();
            break;
        case 6:
            MainMenu();
            break;
        default:
            break;
    }
}

void displayListedSongs() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printListOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 4 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsStatic();
            displayListedSongs();
            break;
        case 2:
            displayListedSongsSorted();
            break;
        case 3:
            displayListedSongsWithValidMusicFile();
            displayListedSongs();
            break;
        case 4:
            MainMenu();
            break;
        default:
            break;
    }
}

void displayListedSongsSorted() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 7 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsSortedByName();
            break;
        case 2:
            displayListedSongsSortedByAlbum();
            break;
        case 3:
            displayListedSongsSortedByArtist();
            break;
        case 4:
            displayListedSongsByGenre();
            displayListedSongsSorted();
            break;
        case 5:
            displayListedSongsByYearOfPublishing();
            break;
        case 6:
            displayListedSongsByRating();
            break;
        case 7:
            displayListedSongs();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByName() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListByNameOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsSortedByNameA2Z();
            displayListedSongsSortedByName();
            break;
        case 2:
            displayListedSongInfosFromAGivenSong();
            displayListedSongsSortedByName();
            break;
        case 3:
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByAlbum() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListByAlbumOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsSortedByAlbumA2Z();
            displayListedSongsSortedByAlbum();
            break;
        case 2:
            displayListedSongsWithAGivenAlbum();
            displayListedSongsSortedByAlbum();
            break;
        case 3:
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByArtist() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListByArtistOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsSortedByArtistA2Z();
            displayListedSongsSortedByArtist();
            break;
        case 2:
            displayListedSongsWithAGivenArtist();
            displayListedSongsSortedByArtist();
            break;
        case 3:
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsByYearOfPublishing() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListByYearOfPublishingOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsByYearOfPublishingNew2Old();
            displayListedSongsByYearOfPublishing();
            break;
        case 2:
            displayListedSongsByYearOfPublishingOld2New();
            displayListedSongsByYearOfPublishing();
            break;
        case 3:
            displayListedSongsNewerThanTheGivenYear();
            displayListedSongsByYearOfPublishing();
            break;
        case 4:
            displayListedSongsOlderThanTheGivenYear();
            displayListedSongsByYearOfPublishing();
            break;
        case 5:
            displayListedSongsWithAGivenYearOfPublishing();
            displayListedSongsByYearOfPublishing();
            break;
        case 6:
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsByRating() {
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE) {
        system("cls");
        printListOptionsTitleScreen();
        printSortedListByRatingOptions(selectedOption);

        option = getch();
        if (option == 224) {
            // Arrow key detected
            option = getch();
            if (option == 72) {
                selectedOption = (selectedOption == 1) ? 4 : selectedOption - 1;
            } else if (option == 80) {
                selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1;
            }
        } else if (option == 13) {
            break;
        }
    }

    switch (selectedOption) {
        case 1:
            displayListedSongsByRatingBest2Worse();
            displayListedSongsByRating();
            break;
        case 2:
            displayListedSongsByRatingWorse2Best();
            displayListedSongsByRating();
            break;
        case 3:
            displayListedSongsWithAGivenRating();
            displayListedSongsByRating();
            break;
        case 4:
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}


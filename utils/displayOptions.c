#include "utils.h"
#include "displayOptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

void printPartingLine() {
    printf("|%35s|%24s|%24s|%30s|%5s|%7s|%-50s|\n",
           "-------------------------------------", "------------------------------------------",
           "-------------------------",
           "------------------------------", "------", "--------",
           "--------------------------------------------------");
}

void printTableHeader() {
    system("cls");
    printPartingLine();
    printf("| %-35s | %-40s | %-23s | %-28s | %-4s | %-6s | %-48s |\n",
           "Name", "Album", "Artist", "Genre", "Year", "Rating", "Music File");
    printPartingLine();
}

void printTableRow(const TSongInfos song) {
    printf("| %-35s | %-40s | %-23s | %-28s | %-4hd | %-6hd | %-48s |\n",
           song.name, song.album, song.artist, song.genre, song.yearPublished, song.rating,
           song.musicFileName);
}

void displayListedSongsStatic() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[i] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }


    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithValidMusicFile() {
    system("cls");

    FILE *file = NULL;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        free(songName);
        free(songFileName);
        free(musicFilePath);
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);
            free(songName);
            free(songFileName);
            free(musicFilePath);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (!strCmpIgnoreCase(songs[j].musicFileName, "none")) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);
    free(songFileName);
    free(musicFilePath);

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByNameA2Z() {
    FILE *file = NULL;

    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort the songs by name (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByName);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongInfosFromAGivenSong() {
    system("cls");
    FILE *file = NULL;

    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Enter the desired Song Name
    const String searchSong = malloc(MAX_STR_LEN * sizeof(char));
    if (searchSong == NULL) {
        perror("Memory allocation error");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);

        exit(1);
    }

    printf("Enter the Song:");
    fgets(searchSong, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchSong, MAX_STR_LEN);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, searchSong) == 1) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(searchSong);

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByAlbumA2Z() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort songs by album (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByAlbum);

    // Output the sorted songs
    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenAlbum() {
    system("cls");

    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Enter the desired album
    const String searchAlbum = malloc(MAX_STR_LEN * sizeof(char));
    if (searchAlbum == NULL) {
        perror("Memory allocation error");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);

        exit(1);
    }

    printf("Enter the Album:");
    fgets(searchAlbum, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchAlbum, MAX_STR_LEN);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].album, searchAlbum) == 1) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(searchAlbum);

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByArtistA2Z() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort the songs by artist (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByArtist);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenArtist() {
    system("cls");

    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Enter the desired artist
    const String searchArtist = malloc(MAX_STR_LEN * sizeof(char));
    if (searchArtist == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    printf("Enter the Artist:");
    fgets(searchArtist, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchArtist, MAX_STR_LEN);

    // Output the songs with the desired artist
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].artist, searchArtist) == 1) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(searchArtist);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByGenre() {
    system("cls");

    FILE *file = NULL;
    char *searchGenre = malloc(MAX_STR_LEN * sizeof(char));

    if (searchGenre == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        free(searchGenre);

        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);
            free(searchGenre);

            exit(1);
        }
    }

    // User input for desired genre
    printf("Enter the genre: ");

    if (fgets(searchGenre, MAX_STR_LEN, stdin) == NULL) {
        perror("Error reading input");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(searchGenre);

        exit(1);
    }

    // Remove the line break from fgets
    charReplace('\n', '\0', searchGenre, MAX_STR_LEN);


    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered genre substring and output them
    printTableHeader();

    for (int j = 0; j < i; j++) {
        // Check whether the genre substring is included in the genre
        if (strstr(songs[j].genre, searchGenre) != NULL) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(searchGenre);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishingNew2Old() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort songs by release year (new - old)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingNew2Old);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishingOld2New() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort songs by release year (old - new)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingOld2New);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsNewerThanTheGivenYear() {
    system("cls");

    FILE *file = NULL;
    int givenYear;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort the filtered songs in ascending order of publication year
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingOld2New);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (songs[j].yearPublished >= givenYear) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    //free(filteredSongs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsOlderThanTheGivenYear() {
    system("cls");

    FILE *file = NULL;
    int givenYear;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year
    // and output them in ascending order of publication year
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingOld2New);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (songs[j].yearPublished <= givenYear) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenYearOfPublishing() {
    system("cls");

    FILE *file = NULL;
    int givenYear;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year and output them
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (songs[j].yearPublished == givenYear) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRatingBest2Worse() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort the songs (worse - best)
    qsort(songs, i, sizeof(TSongInfos), compareSongsWorse2Best);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRatingWorse2Best() {
    FILE *file = NULL;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Sort the songs (best - worse)
    qsort(songs, i, sizeof(TSongInfos), compareSongsBest2Worse);

    printTableHeader();

    for (int j = 0; j < i; j++) {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenRating() {
    system("cls");

    FILE *file = NULL;
    int givenRating;
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++) {
        for (int j = 0; j < indexCount; j++) {
            songs[j] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL || songs[i].musicFileName == NULL) {
            perror("Memory allocation error");

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++) {
                freeSongInfos(songs[j]);
            }

            free(songs);

            exit(1);
        }
    }

    // User input for the desired rating
    printf("Enter the Rating:");
    scanf("%d", &givenRating);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7) {
        i++;
    }

    fclose(file);

    // Filter the songs according to the rating entered and output them
    printTableHeader();

    for (int j = 0; j < i; j++) {
        if (songs[j].rating == givenRating) {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);

    printf("\n\n");
    system("pause");
}

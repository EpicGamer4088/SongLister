#include "utils.h"
#include "music.h"
#include "menues.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>

TSongInfos inputSongInfos() {
    TSongInfos songInfos = allocateSongInfos();

    printf("Input the needes Informations from the Song\n");

    printf("Name:");
    fflush(stdin);
    fgets(songInfos.name, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.name, MAX_STR_LEN);
    charReplace(';', ',', songInfos.name, MAX_STR_LEN);

    printf("Album:");
    fgets(songInfos.album, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.album, MAX_STR_LEN);
    charReplace(';', ',', songInfos.album, MAX_STR_LEN);

    printf("Artist:");
    fgets(songInfos.artist, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.artist, MAX_STR_LEN);
    charReplace(';', ',', songInfos.artist, MAX_STR_LEN);

    printf("Genre:");
    fgets(songInfos.genre, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.genre, MAX_STR_LEN);
    charReplace(';', ',', songInfos.genre, MAX_STR_LEN);

    printf("Year Published:");
    scanf("%hd", &songInfos.yearPublished);

    do {
        printf("Your Rating (1-5):");
        scanf("%hd", &songInfos.rating);
    } while (!(songInfos.rating >= 1 && songInfos.rating <= 5));

    printf("Do you want to add a Music File for the Song (y|n): ");
    fflush(stdin);
    songInfos.musicFile = getchar() == 'y' ? TRUE : FALSE;
    if (songInfos.musicFile) {
        songInfos.musicFileName = addMusicFileForNewSong(songInfos);
    }

    return songInfos;
}

void addNewSong() {
    system("cls");

    FILE *file = NULL;

    // Open File to Attach
    file = fopen(fullSongListFilePath, "at");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);

    // Check if file already has valid entries
    if (ftell(file) == 0) {
        indexCount = 0;
    } else {
        fseek(file, -1, SEEK_CUR);

        char c;
        while ((c = fgetc(file)) != '\n' && ftell(file) > 1) {
            fseek(file, -2, SEEK_CUR);
        }
    }

    fseek(file, 0, SEEK_END);

    const TSongInfos songInfos = inputSongInfos();

    // Write the data to the end of the file
    if (fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                songInfos.name, songInfos.album, songInfos.artist,
                songInfos.genre, songInfos.yearPublished, songInfos.rating,
                (songInfos.musicFile == TRUE) ? songInfos.musicFileName : "none") < 0) {
        perror("Error writing to file");
        exit(1);
    }

    fclose(file);

    indexCount++;

    // Free Memory
    freeSongInfos(songInfos);

    usleep(500000);
    system("cls");

    printf("Song Added successfully\n\n");
    system("pause");
}

void removeSong() {
    system("cls");

    FILE *file = NULL;
    int songIndex;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        free(songName);
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

    printf("Enter The Song you want to delete: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    // Check if the song exists in the list
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            break;
        }
    }

    if (!songExists) {
        printf("\n\nYour entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);

        system("pause");
        MainMenu();
    }

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but skip the one to be deleted
    for (int j = 0; j < i; j++) {
        if (!strCmpIgnoreCase(songs[j].name, songName)) {

            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);

        } else {
            songIndex = j;
        }
    }

    fclose(file);

    if (fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songs[songIndex].musicFileName))) {
        removeMusicFileFromMusicFolder(
                mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songs[songIndex].musicFileName));
    }
    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);

    indexCount--;

    usleep(500000);
    system("cls");

    printf("Song Removed successfully\n\n");
    system("pause");
}

void changeSongInformations() {
    system("cls");

    FILE *file = NULL;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        free(songName);
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

    printf("Enter The Song you want to change the Informations from: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    // Check if the song exists in the list
    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists) {
        printf("\n\nYour entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);

        system("pause");
        MainMenu();
    }

    printf("\nEnter new Song Informations:");

    TSongInfos songInfos = inputSongInfos();

    system("cls");

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++) {
        if (j != songIndex) {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);
        } else {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songInfos.name, songInfos.album, songInfos.artist,
                    songInfos.genre, songInfos.yearPublished, songInfos.rating,
                    (songInfos.musicFile == TRUE) ? songInfos.musicFileName : "none");
        }
    }

    fclose(file);

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);

    usleep(500000);
    system("cls");

    printf("Song Informations Changed successfully\n\n");
    system("pause");
}

void addMusicFile() {
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

    system("cls");
    printf("Enter the Song Name you want to add a music file to: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    // Check if the song exists in the list
    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists) {
        usleep(500000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    }

    songFileName = generateMusicFileName(songs[songIndex]);

    // Check if song already has a Valid Music File
    if (fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName))) {
        usleep(500000);
        system("cls");

        printf("Your entered Song already has a Valid Music File.\nYou can change it via the Change Option in the Menu\n\n");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    }

    usleep(500000);

    printf("\n\nSelect the SongFile for your entered Song \"%s\"\n", songName);

    usleep(500000);

    musicFilePath = openMusicFileDialog();

    copyAndRenameMusicFile(musicFilePath, fullMusicFolderFilePath, songFileName);

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songFileName);
        } else {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);
        }
    }

    fclose(file);

    usleep(100000);
    system("cls");

    printf("Successfully added Music File for Song \"%s\"\n\n", songName);

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);
    free(songFileName);

    system("pause");
}

String addMusicFileForNewSong(const TSongInfos songInfos) {
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    usleep(500000);

    printf("\n\nSelect the SongFile for your entered Song \"%s\"\n", songInfos.name);

    usleep(500000);

    musicFilePath = openMusicFileDialog();

    songFileName = generateMusicFileName(songInfos);

    copyAndRenameMusicFile(musicFilePath, fullMusicFolderFilePath, songFileName);

    usleep(100000);
    system("cls");

    printf("Successfully added Music File for Song \"%s\"\n\n", songInfos.name);

    system("pause");

    return songFileName;
}

void removeMusicFile() {
    FILE *file = NULL;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL) {
        perror("Memory allocation error");
        free(songName);
        free(songFileName);
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

    system("cls");
    printf("Enter the Song Name you want to remove a music file from: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists) {
        usleep(100000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);

        system("pause");
        displayMusicMenu();
    }

    songFileName = generateMusicFileName(songs[songIndex]);

    if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName))) {
        usleep(100000);
        system("cls");
        printf("Your entered Song does not have a Valid Music File.\nYou can add one via the Add Option in the Menu\n\n");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);

        system("pause");
        displayMusicMenu();
    }

    removeMusicFileFromMusicFolder(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName));

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }
    for (int j = 0; j < i; j++) {
        if (j == songIndex) {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    "none");
        } else {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);
        }
    }
    fclose(file);

    usleep(100000);
    system("cls");

    printf("Successfully removed Music File from Song \"%s\"\n\n", songName);

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);
    free(songFileName);

    system("pause");
}

void changeMusicFile() {
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

    system("cls");
    printf("Enter the Song Name you want to change the music file from: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists) {
        usleep(100000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    }

    songFileName = generateMusicFileName(songs[songIndex]);

    if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName))) {
        usleep(100000);
        system("cls");
        printf("Your entered Song does not have a Valid Music File.\nYou can add one via the Add Option in the Menu\n\n");

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    }

    usleep(500000);

    removeMusicFileFromMusicFolder(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName));

    printf("\n\nSelect the new SongFile for your entered Song \"%s\"\n", songName);

    usleep(500000);

    musicFilePath = openMusicFileDialog();

    copyAndRenameMusicFile(musicFilePath, fullMusicFolderFilePath, songFileName);

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL) {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songFileName);
        } else {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);
        }
    }

    fclose(file);

    usleep(100000);
    system("cls");

    printf("Successfully changed Music File from Song \"%s\"\n\n", songName);

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);
    free(songFileName);

    system("pause");
}

void playMusic() {
    FILE *file = NULL;
    int option;
    Boolean isPlaying = FALSE;
    Boolean endPlayback = FALSE;
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
            songs[i].artist == NULL || songs[i].genre == NULL ||
            songs[i].musicFileName == NULL) {
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

    system("cls");
    printf("Enter the Song Name you want to play the Music File from: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    // Check if the song exists in the list
    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++) {
        if (strCmpIgnoreCase(songs[j].name, songName)) {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists) {
        usleep(500000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    } else if (strCmpIgnoreCase(songs[songIndex].musicFileName, "none")) {
        usleep(500000);
        system("cls");
        printf("Your entered Song \"%s\" does not have a Valid Music File\n\n", songName);

        // Release of allocated memory
        for (int j = 0; j < indexCount; j++) {
            freeSongInfos(songs[j]);
        }

        free(songs);
        free(songName);
        free(songFileName);
        free(musicFilePath);

        system("pause");
        displayMusicMenu();
    }

    usleep(100000);
    system("cls");

    printPlayMusicScreen(songs[songIndex]);

    usleep(500000);

    playWaveFile(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songs[songIndex].musicFileName), &isPlaying);

    while (!endPlayback) {
        option = getch();
        switch (option) {
            case 32: // Space
                pauseResumePlayback(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songs[songIndex].musicFileName),
                                    &isPlaying);
                break;
            case 27: // ESC
                if (isPlaying) {
                    pauseResumePlayback(
                            mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songs[songIndex].musicFileName),
                            &isPlaying);
                }
                endPlayback = TRUE;
                break;
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

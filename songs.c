#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <conio.h>
#include <signal.h>
#include "songs.h"
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>

int indexCount = 0;
String fullSongListFilePath = NULL;
String fullMusicFolderFilePath = NULL;
String fullUserDataFilePath = NULL;
UserData userData = {NULL, NULL, 0};

void Main()
{
    signal(SIGINT, exitHandler); // SIGINT is triggered, for example, by Ctrl+C
    signal(SIGTERM, exitHandler); // SIGTERM is triggered, for example, when exiting by the X in the top right

    fullSongListFilePath = (String)malloc(MAX_STR_LEN * sizeof(String));
    fullMusicFolderFilePath = (String)malloc(MAX_STR_LEN * sizeof(String));
    fullUserDataFilePath = (String)malloc(MAX_STR_LEN * sizeof(String));
    const TSongInfos songInfos = {0, NULL, NULL, NULL, NULL, 0};

    checkAndHandleUserDataFile();
    checkAndHandleMusicFileFolder();

    MainMenu(songInfos);
}

void MainMenu(const TSongInfos songInfos)
{
    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printTitelScreen();
        printMenuOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        addNewSong();
        usleep(500000);
        MainMenu(songInfos);
        break;
    case 2:
        removeSong();
        usleep(1000000);
        MainMenu(songInfos);
        break;
    case 3:
        changeSongInformations();
        usleep(500000);
        MainMenu(songInfos);
        break;
    case 4:
        displayListedSongs();
        usleep(500000);
        MainMenu(songInfos);
        break;
    case 5:

        break;
    case 6:
        freeSongInfos(songInfos);
        exitProgramm(0);
    default:
        break;
    }
}

void printTitelScreen()
{
    printf("--------------------------------\n"
        "|                              |\n"
        "|          Song Rater          |\n"
        "|                              |\n"
        "--------------------------------\n");
}

void printListOptionsTitelScreen()
{
    printf("-----------------------------------\n"
        "|                                 |\n"
        "|           Song Lister           |\n"
        "|                                 |\n"
        "-----------------------------------\n");
}

void printMenuOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  Add a new Song to Song List\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Delete a Song from song List\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Change Song Informations in Song List\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List Songs\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  Change UserData\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  Exit\n\n", (selectedOption == 6) ? ">>" : "  ");
}

void printListOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Sorted\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 3) ? ">>" : "  ");
}

void printChangeUserDataOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  Change SongList File Path\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Change Music Folder Path\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Name\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Sorted by Album\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List Sorted by Artist\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List every Entrie from a given Genre\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List by Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  List by Rating\n", (selectedOption == 6) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 7) ? ">>" : "  ");
}

void printSortedListByNameOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Name (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Entrie from a Given Song\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByAlbumOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Album (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entrie from a given Album\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByArtistOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Artist (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entrie from a given Artist\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByYearOfPublishingOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List (Newest - Oldest)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Oldest - Newest)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List Newer Than The Given Year\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List Older Than The Given Year\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List every Entrie from a given Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 6) ? ">>" : "  ");
}

void printSortedListByRatingOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List (Best - Worse)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Worse - Best)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List every Entrie from a given Rating\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 4) ? ">>" : "  ");
}

String openCSVFileDialog()
{
    static char filePath[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = sizeof(filePath);
    ofn.lpstrFilter = "CSV Files\0*.csv\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return filePath;
    }
    else
    {
        return NULL;
    }
}

String openFolderDialog()
{
    static char folderPath[MAX_PATH];

    BROWSEINFO browseInfo = {0};
    browseInfo.hwndOwner = NULL;
    browseInfo.pidlRoot = NULL;
    browseInfo.pszDisplayName = folderPath;
    browseInfo.lpszTitle = "Select a folder";
    browseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    browseInfo.lpfn = NULL;

    LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);

    if (pidl != NULL)
    {
        SHGetPathFromIDList(pidl, folderPath);
        CoTaskMemFree(pidl);
        return folderPath;
    }
    else
    {
        return NULL;
    }
}

void checkAndHandleUserDataFile()
{
    fullUserDataFilePath = mergeStr(setWorkingDirectoryToExecutablePath(), USERDATA_FILE_NAME);

    FILE* file = fopen(fullUserDataFilePath, "rt");

    if (file == NULL)
    {
        // File does not exist, create the file
        file = fopen(fullUserDataFilePath, "wt");

        if (file != NULL)
        {
            // Write UserData to the file
            setUserData();
            writeUserDataIntoUserDataFile();
            fclose(file);
        }
        else
        {
            printf("Error creating file.\n");
        }
    }
    else
    {
        // File exists, read UserData from the file
        readUserDataFromUserDataFile();
        fclose(file);
    }
}

void checkAndHandleMusicFileFolder()
{
    // Check if the folder already exists
    if (!(PathFileExistsA(fullMusicFolderFilePath)))
    {
        // Create folder because it doesn't exist
        if (CreateDirectoryA(fullMusicFolderFilePath, NULL))
        {
        }
        else
        {
            printf("Error creating folder.\n");
        }
    }
}

void setUserData()
{
    fullSongListFilePath = openCSVFileDialog();
    fullMusicFolderFilePath = openFolderDialog();
    setIndexCount();
}

void writeUserDataIntoUserDataFile()
{
    FILE* file = fopen(fullUserDataFilePath, "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    fprintf(file, "%s;%s;%d", fullSongListFilePath, fullMusicFolderFilePath, indexCount);

    fclose(file);
}

void readUserDataFromUserDataFile()
{
    FILE* file = fopen(fullUserDataFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    fscanf(file, "%[^;];%[^;];%d", fullSongListFilePath, fullMusicFolderFilePath, &indexCount);

    fclose(file);
}

FILE* openFile(const String filePath, const String mode)
{
    return fopen(filePath, mode);
}

FILE* reopenFile(FILE* file, const String filePath, const String mode)
{
    fclose(file);
    return fopen(filePath, mode);
}

FILE* selectSongDataFile(const char* mode, bool* songFileLoaded)
{
    FILE* file = NULL;

    // Check if File alredy exists
    if (access(fullSongListFilePath, F_OK) == -1)
    {
        // File doesn not alredy exist, so create it
        file = fopen(fullSongListFilePath, "w+");
        if (file == NULL)
        {
            perror("Error creating file");
            *songFileLoaded = FALSE;
            exit(1);
        }
        *songFileLoaded = TRUE;
        fclose(file);
        return fopen(fullSongListFilePath, mode);
    }

    *songFileLoaded = TRUE;

    return fopen(fullSongListFilePath, mode);
}

TSongInfos inputSongInfos()
{
    TSongInfos songInfos = allocateSongInfos();

    printf("Input the needes Informations from the Song\n");

    songInfos.index = indexCount;

    printf("Name:");
    clearInputBuffer();
    fgets(songInfos.name, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.name, MAX_STR_LEN);

    printf("Album:");
    fgets(songInfos.album, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.album, MAX_STR_LEN);

    printf("Artist:");
    fgets(songInfos.artist, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.artist, MAX_STR_LEN);

    printf("Genre:");
    fgets(songInfos.genre, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songInfos.genre, MAX_STR_LEN);

    printf("Year Published:");
    scanf("%hd", &songInfos.yearPublished);

    do
    {
        printf("Your Rating (1-5):");
        scanf("%hd", &songInfos.rating);
    }
    while (!(songInfos.rating >= 1 && songInfos.rating <= 5));

    return songInfos;
}

void addNewSong()
{
    FILE* file = NULL;

    // Open File to Attach
    file = fopen(fullSongListFilePath, "at");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);

    // Check if file already has valid entries
    if (ftell(file) == 0)
    {
        indexCount = 0;
    }
    else
    {
        fseek(file, -1, SEEK_CUR);

        char c;
        while ((c = fgetc(file)) != '\n' && ftell(file) > 1)
        {
            fseek(file, -2, SEEK_CUR);
        }
    }

    fseek(file, 0, SEEK_END);

    const TSongInfos songInfos = inputSongInfos();

    // Write the data to the end of the file
    if (fprintf(file, "%hd;%s;%s;%s;%s;%hd;%hd\n", indexCount, songInfos.name, songInfos.album, songInfos.artist,
                songInfos.genre, songInfos.yearPublished, songInfos.rating) < 0)
    {
        perror("Error writing to file");
        exit(1);
    }

    fclose(file);

    indexCount++;

    // Free Memory
    freeSongInfos(songInfos);

    printf("\n\nSong Added successfully ");
    for (int i = 0; i < 3; i++)
    {
        usleep(500000);
        printf(".");
    }
}

void removeSong()
{
    FILE* file = NULL;

    int index;

    printf("Input the Index of the Entry you want to delete.\n"
        "To display your Song List inclusive the Index of every Song, Type \"-1\"\n\n");
    scanf("%d", &index);
    if (index < 0)
    {
        displayListedSongsStatic(file);
        do
        {
            printf("\nIndex of which song you wanna remove from the list:");
            scanf("%d", &index);
        }
        while (index < 0);
    }

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (!feof(file))
    {
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating));
        i++;
    }
    fclose(file);

    // Check if given Index is Valid
    if (index < 0 || index >= i)
    {
        printf("Invalid Index\n");
        return;
    }

    // Open File to Write
    file = fopen("../SongList.csv", "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but skip the one to be deleted
    for (int j = 0; j < i; j++)
    {
        if (j != index)
        {
            if (j < index)
            {
                fprintf(file, "%hd;%s;%s;%s;%s;%hd;%hd\n", songs[j].index,
                        songs[j].name, songs[j].album, songs[j].artist,
                        songs[j].genre, songs[j].yearPublished, songs[j].rating);
            }
            else
            {
                fprintf(file, "%hd;%s;%s;%s;%s;%hd;%hd\n", songs[j].index - 1,
                        songs[j].name, songs[j].album, songs[j].artist,
                        songs[j].genre, songs[j].yearPublished, songs[j].rating);
            }
        }
    }

    fclose(file);

    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    indexCount--;

    printf("\n\nSong Removed successfully ");
    for (int j = 0; j < 3; j++)
    {
        usleep(500000);
        printf(".");
    }
}

void changeSongInformations()
{
    FILE* file = NULL;

    int index;

    printf("Input the Index of the Entrie you wanna edit.\n"
        "To display your Song List inclusive the Index of every Song, Type \"-1\"\n\n");
    scanf("%d", &index);
    if (index < 0)
    {
        displayListedSongsStatic();
        do
        {
            printf("Index of which song you wanna change the Informtion of:");
            scanf("%d", &index);
        }
        while (index < 0);
    }

    printf("\nEnter new Song Informations:");

    TSongInfos songInfos = inputSongInfos();

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (!feof(file))
    {
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating));
        i++;
    }
    fclose(file);

    // Check if given Index is Valid
    if (index < 0 || index >= i)
    {
        printf("Invalid Index\n");
        return;
    }

    // Open File to Write
    file = fopen("../SongList.csv", "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++)
    {
        if (j != index)
        {
            fprintf(file, "%hd;%s;%s;%s;%s;%hd;%hd\n", songs[j].index,
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating);
        }
        else
        {
            fprintf(file, "%hd;%s;%s;%s;%s;%hd;%hd\n", index,
                    songInfos.name, songInfos.album, songInfos.artist,
                    songInfos.genre, songInfos.yearPublished, songInfos.rating);
        }
    }

    fclose(file);

    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\nSong Informations Changed successfully ");
    for (int j = 0; j < 3; j++)
    {
        usleep(500000);
        printf(".");
    }
}

void changeUserData()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printTitelScreen();
        printChangeUserDataOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        fullSongListFilePath = openCSVFileDialog();
        writeUserDataIntoUserDataFile();
        changeUserData();
        break;
    case 2:
        fullMusicFolderFilePath = openFolderDialog();
        writeUserDataIntoUserDataFile();
        changeUserData();
        break;
    case 3:
        break;
    default:
        break;
    }
}

void printPartingLine()
{
    printf("|%5s|%32s|%21s|%21s|%50s|%5s|%7s|\n",
           "-------", "----------------------------------", "---------------------------------------",
           "----------------------",
           "----------------------------------------------------", "------", "--------");
}

void printTableHeader()
{
    system("cls");
    printPartingLine();
    printf("| %-5s | %-32s | %-37s | %-20s | %-50s | %-4s | %-6s |\n",
           "Index", "Name", "Album", "Artist", "Genre", "Year", "Rating");
    printPartingLine();
}

void printTableRow(const TSongInfos song)
{
    printf("| %-5hd | %-32s | %-37s | %-20s | %-50s | %-4hd | %-6hd |\n",
           song.index, song.name, song.album, song.artist, song.genre, song.yearPublished, song.rating);
}

void displayListedSongs()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printListOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        displayListedSongsStatic();
        displayListedSongs();
        break;
    case 2:
        displayListedSongsSorted();
        displayListedSongs();
        break;
    case 3:
        break;
    default:
        break;
    }
}

void displayListedSongsStatic()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount)
    {
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating));
        i++;
    }

    fclose(file);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsSorted()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 7 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        displayListedSongsSortedByName();
        displayListedSongsSorted();
        break;
    case 2:
        displayListedSongsSortedByAlbum();
        displayListedSongsSorted();
        break;
    case 3:
        displayListedSongsSortedByArtist();
        displayListedSongsSorted();
        break;
    case 4:
        displayListedSongsByGenre();
        displayListedSongsSorted();
        break;
    case 5:
        displayListedSongsByYearOfPublishing();
        displayListedSongsSorted();
        break;
    case 6:
        displayListedSongsByRating();
        displayListedSongsSorted();
        break;
    case 7:
        break;
    default:
        break;
    }
}

void displayListedSongsSortedByName()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListByNameOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        displayListedSongsSortedByNameA2Z();
        displayListedSongsSortedByName();
        break;
    case 2:
        displayListedSongInfosFromAGivenSong();
        displayListedSongsSortedByName();
        break;
    case 3:
        break;
    default:
        break;
    }
}

void displayListedSongsSortedByNameA2Z()
{
    FILE* file = NULL;

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }
    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort the songs by name (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByName);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongInfosFromAGivenSong()
{
    system("cls");
    FILE* file = NULL;

    // Read the song data from the file
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
                                    &(songs[i].index), songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
                                    &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired Song Name
    const String searchSong = malloc(MAX_STR_LEN);
    if (searchSong == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }

    printf("Enter the Song:");
    fgets(searchSong, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchSong, MAX_STR_LEN);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, searchSong) == 1)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Free the dynamically allocated memory for searchAlbum
    free(searchSong);

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByAlbum()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListByAlbumOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        displayListedSongsSortedByAlbumA2Z();
        displayListedSongsSortedByAlbum();
        break;
    case 2:
        displayListedSongsWithAGivenAlbum();
        displayListedSongsSortedByAlbum();
        break;
    case 3:
        break;
    default:
        break;
    }
}

void displayListedSongsSortedByAlbumA2Z()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
                                    &(songs[i].index), songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
                                    &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort songs by album (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByAlbum);

    // Output the sorted songs
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenAlbum()
{
    system("cls");

    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
                                    &(songs[i].index), songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
                                    &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired album
    const String searchAlbum = malloc(MAX_STR_LEN);
    if (searchAlbum == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }

    printf("Enter the Album:");
    fgets(searchAlbum, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchAlbum, MAX_STR_LEN);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].album, searchAlbum) == 1)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Free the dynamically allocated memory for searchAlbum
    free(searchAlbum);

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByArtist()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListByArtistOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 3 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
    case 1:
        displayListedSongsSortedByArtistA2Z();
        displayListedSongsSortedByArtist();
        break;
    case 2:
        displayListedSongsWithAGivenArtist();
        displayListedSongsSortedByArtist();
        break;
    case 3:
        break;
    default:
        break;
    }
}

void displayListedSongsSortedByArtistA2Z()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort the songs by artist (A-Z)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByArtist);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenArtist()
{
    system("cls");

    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
                                    &(songs[i].index), songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
                                    &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired artist
    const String searchArtist = malloc(MAX_STR_LEN);
    if (searchArtist == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }

    printf("Enter the Artist:");
    fgets(searchArtist, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', searchArtist, MAX_STR_LEN);

    // Output the songs with the desired artist
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].artist, searchArtist) == 1)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Free the dynamically allocated memory for searchAlbum
    free(searchArtist);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByGenre()
{
    system("cls");

    FILE* file = NULL;
    // Dynamic allocation for the entered genre name
    char* searchGenre = malloc(MAX_STR_LEN);

    if (searchGenre == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }

    // User input for desired genre
    printf("Enter the genre: ");

    if (fgets(searchGenre, MAX_STR_LEN, stdin) == NULL)
    {
        perror("Error reading input");
        free(searchGenre);
        exit(1);
    }

    // Remove the line break from fgets
    charReplace('\n', '\0', searchGenre, MAX_STR_LEN);

    // Dynamic allocation for the song information
    TSongInfos* songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL)
    {
        perror("Memory allocation error");
        free(searchGenre);
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL)
        {
            perror("Memory allocation error");
            free(searchGenre);

            for (int j = 0; j < i; j++)
            {
                free(songs[j].name);
                free(songs[j].album);
                free(songs[j].artist);
                free(songs[j].genre);
            }

            free(songs);

            exit(1);
        }
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered genre substring and output them
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        // Check whether the genre substring is included in the genre
        if (strstr(songs[j].genre, searchGenre) != NULL)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    free(songs);
    free(searchGenre);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishing()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListByYearOfPublishingOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
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
        break;
    default:
        break;
    }
}

void displayListedSongsByYearOfPublishingNew2Old()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort songs by release year (new - old)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingNew2Old);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishingOld2New()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort songs by release year (old - new)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingOld2New);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsNewerThanTheGivenYear()
{
    system("cls");

    FILE* file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    clearInputBuffer(); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year
    TSongInfos* filteredSongs = malloc(i * sizeof(TSongInfos));
    int filteredCount = 0;

    for (int j = 0; j < i; j++)
    {
        if (songs[j].yearPublished >= givenYear)
        {
            filteredSongs[filteredCount++] = songs[j];
        }
    }

    // Sort the filtered songs in ascending order of publication year
    qsort(filteredSongs, filteredCount, sizeof(TSongInfos), compareSongsByYearOfPublishingNew2Old);

    printTableHeader();

    for (int j = 0; j < filteredCount; j++)
    {
        printTableRow(filteredSongs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    free(filteredSongs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsOlderThanTheGivenYear()
{
    system("cls");

    FILE* file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    clearInputBuffer(); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year
    // and output them in ascending order of publication year
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishingOld2New);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (songs[j].yearPublished <= givenYear)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenYearOfPublishing()
{
    system("cls");

    FILE* file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    clearInputBuffer(); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year and output them
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (songs[j].yearPublished == givenYear)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRating()
{
    clearInputBuffer();

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printSortedListByRatingOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 4 : selectedOption - 1;
            }
            else if (option == 80)
            {
                selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1;
            }
        }
        else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
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
        break;
    default:
        break;
    }
}

void displayListedSongsByRatingBest2Worse()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort the songs (worse - best)
    qsort(songs, i, sizeof(TSongInfos), compareSongsWorse2Best);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRatingWorse2Best()
{
    FILE* file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort the songs (best - worse)
    qsort(songs, i, sizeof(TSongInfos), compareSongsBest2Worse);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenRating()
{
    system("cls");

    FILE* file = NULL;
    int givenRating;

    // User input for the desired rating
    printf("Enter the Rating:");
    scanf("%d", &givenRating);
    clearInputBuffer(); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i].name = malloc(MAX_STR_LEN);
        songs[i].album = malloc(MAX_STR_LEN);
        songs[i].artist = malloc(MAX_STR_LEN);
        songs[i].genre = malloc(MAX_STR_LEN);
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount &&
        fscanf(file, "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd\n",
               &(songs[i].index), songs[i].name, songs[i].album,
               songs[i].artist, songs[i].genre, &(songs[i].yearPublished),
               &(songs[i].rating)) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the rating entered and output them
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (songs[j].rating == givenRating)
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        free(songs[j].name);
        free(songs[j].album);
        free(songs[j].artist);
        free(songs[j].genre);
    }

    printf("\n\n");
    system("pause");
}

void exitProgramm(const int returnValue)
{
    system("cls");
    printf("The Program will Close. Goodbye!\n\n");
    usleep(1000000);
    system("PAUSE");
    exit(returnValue);
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void charReplace(const char old, const char new, char* haystack, const int maxLength)
{
    for (int i = 0; i < maxLength && haystack[i] != '\0'; i++)
    {
        if (haystack[i] == old)
        {
            haystack[i] = new;
        }
    }
}

char* mergeStr(const char* str1, const char* str2)
{
    int len1 = 0;
    int len2 = 0;

    while (str1[len1] != '\0')
    {
        len1++;
    }

    while (str2[len2] != '\0')
    {
        len2++;
    }

    const String mergedStr = (String)malloc(len1 + len2 + 1);

    if (mergedStr == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < len1; i++)
    {
        mergedStr[i] = str1[i];
    }

    for (int i = 0; i < len2; i++)
    {
        mergedStr[len1 + i] = str2[i];
    }

    mergedStr[len1 + len2] = '\0';

    return mergedStr;
}

bool strCmp(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return FALSE;
        }
        str1++;
        str2++;
    }
    return TRUE;
}

bool strCmpIgnoreCase(const char* str1, const char* str2)
{
    while (*str1 && *str2)
    {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2))
            return 0;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

TSongInfos allocateSongInfos()
{
    const TSongInfos songInfos = {
        0,
        (String)malloc(MAX_STR_LEN * sizeof(String)),
        (String)malloc(MAX_STR_LEN * sizeof(String)),
        (String)malloc(MAX_STR_LEN * sizeof(String)),
        (String)malloc(MAX_STR_LEN * sizeof(String)),
        0
    };

    return songInfos;
}

void setIndexCount()
{
    FILE* file = fopen(fullSongListFilePath, "r");

    indexCount = 0;

    // Store the current position in the file
    const long int currentPosition = ftell(file);

    rewind(file);

    while (1)
    {
        char line[MAX_STR_LEN];
        if (fgets(line, sizeof(line), file) != NULL)
        {
            // Check if line is valid (not empy or blankspaces)
            int validLine = 0;
            for (int i = 0; i < strlen(line); i++)
            {
                if (!isspace(line[i]))
                {
                    validLine = 1;
                    break;
                }
            }

            if (validLine && sscanf(line, "%*hd;%*[^;];%*[^;];%*[^;];%*[^;];%*hd;%*hd") == 0)
            {
                // Valid Line found, increment indexCount
                indexCount++;
            }
        }

        if (feof(file))
        {
            break;
        }
    }

    fclose(file);
}

String setWorkingDirectoryToExecutablePath() {
    // Reserve dynamic memory for the buffer
    char* buffer = (char*)malloc(MAX_PATH);
    if (buffer == NULL) {
        // Memory allocation error
        return NULL;
    }

    GetModuleFileName(NULL, buffer, MAX_PATH);

    // Removing the filename to keep just the directory
    char* lastBackslash = strrchr(buffer, '\\');
    if (lastBackslash != NULL) {
        *lastBackslash = '\0';
    }

    // Return dynamic reserved path
    return buffer;
}

int compareSongsByName(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    return strcmp(songA->name, songB->name);
}

int compareSongsByAlbum(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    // Compare the albums and sort in ascending order
    return strcmp(songA->album, songB->album);
}

int compareSongsByArtist(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    return strcmp(songA->artist, songB->artist);
}

int compareSongsByYearOfPublishingNew2Old(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    // Sort by publication year in descending order
    return songB->yearPublished - songA->yearPublished;
}

int compareSongsByYearOfPublishingOld2New(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    // Sort by publication year in ascending order
    return songA->yearPublished - songB->yearPublished;
}

int compareSongsWorse2Best(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    // First sort by rating in descending order
    if (songB->rating != songA->rating)
    {
        return songB->rating - songA->rating;
    }

    // If the rating is the same, sort by index in ascending order
    return songA->index - songB->index;
}

int compareSongsBest2Worse(const void* a, const void* b)
{
    const TSongInfos* songA = (const TSongInfos*)a;
    const TSongInfos* songB = (const TSongInfos*)b;

    // First sort by rating in ascending order
    if (songA->rating != songB->rating)
    {
        return songA->rating - songB->rating;
    }

    // If the rating is the same, sort by index in ascending order
    return songA->index - songB->index;
}

void freeSongInfos(const TSongInfos songInfos)
{
    free(songInfos.name);
    free(songInfos.album);
    free(songInfos.artist);
    free(songInfos.genre);
}

/*
int max(const int a, const int b)
{
    return (a > b) ? a : b;
}
 */

void exitHandler()
{
    free(fullSongListFilePath);
    free(fullMusicFolderFilePath);
    free(fullUserDataFilePath);
}

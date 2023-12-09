#include "songs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <conio.h>
#include <signal.h>
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <vlc/vlc.h>

int indexCount = 0;
String fullSongListFilePath = NULL;
String fullMusicFolderFilePath = NULL;
String fullUserDataFilePath = NULL;

void Main()
{
    signal(SIGINT, exitHandler); // SIGINT is triggered, for example, by Ctrl+C
    signal(SIGTERM, exitHandler); // SIGTERM is triggered, for example, when exiting by the X in the top right
    //atexit(exitHandler); // atexit is triggered, when the Program closes, for example, by exit(1)

    fullSongListFilePath = (String) malloc(MAX_PATH * sizeof(char));
    fullMusicFolderFilePath = (String) malloc(MAX_PATH * sizeof(char));
    fullUserDataFilePath = (String) malloc(MAX_PATH * sizeof(char));

    checkAndHandleUserDataFile();
    checkAndHandleMusicFileFolder();

    setIndexCount();

    checkIfAllMusicFileEntriesAreValid();

    MainMenu();
}

void MainMenu()
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
                selectedOption = (selectedOption == 1) ? 7 : selectedOption - 1;
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
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
            updateUserData();
            break;
        case 7:
            exitProgramm(0);
        default:
            break;
    }
}

void checkIfAllMusicFileEntriesAreValid()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 8)
    {
        i++;
    }

    fclose(file);

    for (int j = 0; j < i; j++)
    {
        songFileName = mergeStr(mergeStr(songs[j].artist, "__"), songs[j].name);

        convertSpacesAndSpecialCharsToUnderscores(songFileName);
        convertToLowerCase(songFileName);

        songFileName = mergeStr(songFileName, ".mp3");

        if (fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)) &&
            strCmpIgnoreCase(songs[j].musicFileName, "none"))
        {
            // Open File to Write
            file = fopen(fullSongListFilePath, "wt");
            if (file == NULL)
            {
                perror("Error when opening the file");
                exit(1);
            }
            for (int k = 0; k < i; k++)
            {
                if (k == j)
                {
                    songs[k].musicFileName = songFileName;

                }
                fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                        songs[k].name, songs[k].album, songs[k].artist,
                        songs[k].genre, songs[k].yearPublished, songs[k].rating,
                        songs[k].musicFileName);

            }
            fclose(file);

        } else if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)) &&
                   !strCmpIgnoreCase(songs[j].musicFileName, "none"))
        {
            // Open File to Write
            file = fopen(fullSongListFilePath, "wt");
            if (file == NULL)
            {
                perror("Error when opening the file");
                exit(1);
            }
            for (int k = 0; k < i; k++)
            {
                if (k == j)
                {
                    fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                            songs[k].name, songs[k].album, songs[k].artist,
                            songs[k].genre, songs[k].yearPublished, songs[k].rating,
                            "none");
                } else
                {
                    fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                            songs[k].name, songs[k].album, songs[k].artist,
                            songs[k].genre, songs[k].yearPublished, songs[k].rating,
                            songs[k].musicFileName);
                }
            }
            fclose(file);
        }
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
    printf("%s  Music\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  Change UserData\n", (selectedOption == 6) ? ">>" : "  ");
    printf("%s  Exit\n\n", (selectedOption == 7) ? ">>" : "  ");
}

void printListOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List all Songs\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Sorted\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List all Songs with Valid Music File\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 4) ? ">>" : "  ");
}

void printMusicOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  Add Music File for a Song\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  Remove Music File for a Song\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  Change Music File for a Song\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List all Songs with Valid Music File\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  Play a Song\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  Back To Main Menu\n", (selectedOption == 6) ? ">>" : "  ");
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
    printf("%s  List every Entries from a given Genre\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List by Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  List by Rating\n", (selectedOption == 6) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 7) ? ">>" : "  ");
}

void printSortedListByNameOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Name (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List Infos from a Given Song\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByAlbumOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Album (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entries from a given Album\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByArtistOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List Sorted by Artist (A-Z)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List every Entries from a given Artist\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 3) ? ">>" : "  ");
}

void printSortedListByYearOfPublishingOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List (Newest - Oldest)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Oldest - Newest)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List Newer Than The Given Year\n", (selectedOption == 3) ? ">>" : "  ");
    printf("%s  List Older Than The Given Year\n", (selectedOption == 4) ? ">>" : "  ");
    printf("%s  List every Entries from a given Year of Publishing\n", (selectedOption == 5) ? ">>" : "  ");
    printf("%s  One Step Back...\n", (selectedOption == 6) ? ">>" : "  ");
}

void printSortedListByRatingOptions(const int selectedOption)
{
    printf("Chose a Option:\n");
    printf("%s  List (Best - Worse)\n", (selectedOption == 1) ? ">>" : "  ");
    printf("%s  List (Worse - Best)\n", (selectedOption == 2) ? ">>" : "  ");
    printf("%s  List every Entries from a given Rating\n", (selectedOption == 3) ? ">>" : "  ");
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
    } else
    {
        return NULL;
    }
}

String openMusicFileDialog()
{
    static char filePath[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Media Files\0*.mp3;*.mp4\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return filePath;
    } else
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
    } else
    {
        return NULL;
    }
}

void copyAndRenameMusicFile(const String srcPath, const String destFolder, const String newFileName)
{
    String destPath = (String) malloc(MAX_PATH * sizeof(char));
    snprintf(destPath, MAX_PATH, "%s\\%s", destFolder, newFileName);

    if (CopyFile(srcPath, destPath, FALSE) == 0)
    {
        printf("\n\nError copying file. Error code: %lu\n", GetLastError());
    }

    free(destPath);  // Don't forget to free the allocated memory
}

void removeMusicFileFromMusicFolder(const String filePath)
{
    if (remove(filePath) != 0)
    {
        printf("\n\nError deleting file. Error code: %lu\n", GetLastError());
    }
}

void checkAndHandleUserDataFile()
{
    fullUserDataFilePath = mergeStr(getExecutablePath(), USERDATA_FILE_NAME);

    FILE *file = fopen(fullUserDataFilePath, "rb");

    if (file == NULL)
    {
        // File does not exist, create the file
        file = fopen(fullUserDataFilePath, "wb");

        if (file != NULL)
        {
            // Write UserData to the file
            setUserData();
            writeUserDataIntoUserDataFile();
            fclose(file);
        } else
        {
            printf("Error creating file.\n");
        }
    } else
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
        } else
        {
            printf("Error creating folder.\n");
        }
    }
}

void setUserData()
{
    fullSongListFilePath = openCSVFileDialog();
    fullMusicFolderFilePath = openFolderDialog();
}

void writeUserDataIntoUserDataFile()
{
    FILE *file = fopen(fullUserDataFilePath, "wb");
    if (file == NULL)
    {
        perror("Error opening file for writing in binary mode");
        exit(1);
    }

    // Writing "fullSongListFilePath" and "fullMusicFolderFilePath" into userdata.bin file in Binary mode
    fwrite(fullSongListFilePath, sizeof(char), strlen(fullSongListFilePath) + 1, file); // Include null terminator
    fwrite(fullMusicFolderFilePath, sizeof(char), strlen(fullMusicFolderFilePath) + 1, file); // Include null terminator

    fclose(file);
}

void readUserDataFromUserDataFile()
{
    FILE *file = fopen(fullUserDataFilePath, "rb");
    if (file == NULL)
    {
        perror("Error opening file for reading in binary mode");
        exit(1);
    }

    // Determines the size of the userdata.bin file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read in "fullSongListFilePath"
    fread(fullSongListFilePath, sizeof(char), fileSize, file);

    // Look for the null terminator at the end of "fullSongListFilePath"
    size_t fullSongListFilePathLen = strnlen(fullSongListFilePath, fileSize);
    if (fullSongListFilePathLen >= fileSize - 1)
    {
        // "fullSongListFilePath" is too long
        perror("Error reading fullSongListFilePath from userdata.bin file");
        fclose(file);
        exit(1);
    }

    // Read in "fullMusicFolderFilePath"
    fseek(file, fullSongListFilePathLen + 1, SEEK_SET);
    fread(fullMusicFolderFilePath, sizeof(char), fileSize - (fullSongListFilePathLen + 1), file);

    fclose(file);
}

void updateUserData()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
        case 1:
            updateSongListFilePathInUserDataFile();
            updateUserData();
            break;
        case 2:
            updateMusicFolderPathInUserDataFile();
            updateUserData();
            break;
        case 3:
            MainMenu();
            break;
        default:
            break;
    }
}

void updateSongListFilePathInUserDataFile()
{
    fullSongListFilePath = openCSVFileDialog();
    writeUserDataIntoUserDataFile();
    system("cls");
    printf("Succesfully Updated SongList File Path\n\n");
    system("pause");
}


void updateMusicFolderPathInUserDataFile()
{
    fullMusicFolderFilePath = openFolderDialog();
    writeUserDataIntoUserDataFile();
    system("cls");
    printf("Succesfully Updated Music Folder Path\n\n");
    system("pause");
}

TSongInfos inputSongInfos()
{
    TSongInfos songInfos = allocateSongInfos();


    printf("Input the needes Informations from the Song\n");

    printf("Name:");
    fflush(stdin);
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
    } while (!(songInfos.rating >= 1 && songInfos.rating <= 5));

    printf("Do you want to add a Music File for the Song (y|n): ");
    fflush(stdin);
    songInfos.musicFile = getchar() == 'y' ? TRUE : FALSE;
    if (songInfos.musicFile)
    {
        songInfos.musicFileName = addMusicFileForNewSong(songInfos);
    }

    return songInfos;
}

void addNewSong()
{
    system("cls");

    FILE *file = NULL;

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
    } else
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
    if (fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                songInfos.name, songInfos.album, songInfos.artist,
                songInfos.genre, songInfos.yearPublished, songInfos.rating,
                (songInfos.musicFile == TRUE) ? songInfos.musicFileName : "none") < 0)
    {
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

void removeSong()
{
    system("cls");

    FILE *file = NULL;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }
    fclose(file);

    printf("Enter The Song you want to delete: ");
    fflush(stdin);
    fgets(songName, MAX_STR_LEN, stdin);
    charReplace('\n', '\0', songName, MAX_STR_LEN);

    // Check if the song exists in the list
    int songIndex;
    Boolean songExists = FALSE;
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists)
    {
        printf("\n\nYour entered Song \"%s\" does not exist in your current Song List\n\n", songName);
        free(songName);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        MainMenu();
    }

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but skip the one to be deleted
    for (int j = 0; j < i; j++)
    {
        if (!strCmpIgnoreCase(songs[j].name, songName))
        {
            if (j < songIndex)
            {
                fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                        songs[j].name, songs[j].album, songs[j].artist,
                        songs[j].genre, songs[j].yearPublished, songs[j].rating,
                        songs[j].musicFileName);
            } else
            {
                fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                        songs[j].name, songs[j].album, songs[j].artist,
                        songs[j].genre, songs[j].yearPublished, songs[j].rating,
                        songs[j].musicFileName);
            }
        }
    }

    fclose(file);

    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    indexCount--;

    usleep(500000);
    system("cls");

    printf("Song Removed successfully\n\n");
    system("pause");
}

void changeSongInformations()
{
    system("cls");

    FILE *file = NULL;
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
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
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists)
    {
        printf("\n\nYour entered Song \"%s\" does not exist in your current Song List\n\n", songName);
        free(songName);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        MainMenu();
    }

    printf("\nEnter new Song Informations:");

    TSongInfos songInfos = inputSongInfos();

    system("cls");

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++)
    {
        if (j != songIndex)
        {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songs[j].musicFileName);
        } else
        {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songInfos.name, songInfos.album, songInfos.artist,
                    songInfos.genre, songInfos.yearPublished, songInfos.rating,
                    (songInfos.musicFile == TRUE) ? songInfos.musicFileName : "none");
        }
    }

    fclose(file);

    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    usleep(500000);
    system("cls");

    printf("Song Informations Changed successfully\n\n");
    system("pause");
}

void addMusicFile()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 8)
    {
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
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists)
    {
        usleep(500000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        displayMusicMenu();
    }

    songFileName = mergeStr(mergeStr(songs[songIndex].artist, "__"), songName);

    convertSpacesAndSpecialCharsToUnderscores(songFileName);
    convertToLowerCase(songFileName);

    songFileName = mergeStr(songFileName, ".mp3");

    // Check if song already has a Valid Music File
    if (fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)))
    {
        usleep(500000);
        system("cls");

        printf("Your entered Song already has a Valid Music File.\nYou can change it via the Change Option in the Menu\n\n");

        // Release of allocated memory
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
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
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songFileName);
        } else
        {
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
    free(songName);
    free(songFileName);
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    system("pause");
}

String addMusicFileForNewSong(const TSongInfos songInfos)
{
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    usleep(500000);

    printf("\n\nSelect the SongFile for your entered Song \"%s\"\n", songInfos.name);

    usleep(500000);

    musicFilePath = openMusicFileDialog();

    songFileName = mergeStr(songInfos.artist, "__");

    songFileName = mergeStr(songFileName, songInfos.name);

    convertSpacesAndSpecialCharsToUnderscores(songFileName);
    convertToLowerCase(songFileName);

    songFileName = mergeStr(songFileName, ".mp3");

    copyAndRenameMusicFile(musicFilePath, fullMusicFolderFilePath, songFileName);

    usleep(100000);
    system("cls");

    printf("Successfully added Music File for Song \"%s\"\n\n", songInfos.name);

    system("pause");

    return songFileName;
}

void removeMusicFile()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
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
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists)
    {
        usleep(100000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        displayMusicMenu();
    }

    songFileName = mergeStr(mergeStr(songs[songIndex].artist, "__"), songName);

    convertSpacesAndSpecialCharsToUnderscores(songFileName);
    convertToLowerCase(songFileName);

    songFileName = mergeStr(songFileName, ".mp3");

    if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)))
    {
        usleep(100000);
        system("cls");
        printf("Your entered Song does not have a Valid Music File.\nYou can add one via the Add Option in the Menu\n\n");
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        displayMusicMenu();
    }

    removeMusicFileFromMusicFolder(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName));

    // Open File to Write
    file = fopen(fullSongListFilePath, "wt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }
    for (int j = 0; j < i; j++)
    {
        if (j == songIndex)
        {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    "none");
        } else
        {
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
    free(songName);
    free(songFileName);
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    system("pause");
}

void changeMusicFile()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
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
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            songExists = TRUE;
            songIndex = j;
            break;
        }
    }

    if (!songExists)
    {
        usleep(100000);
        system("cls");
        printf("Your entered Song \"%s\" does not exist in your current Song List\n\n", songName);
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
        system("pause");
        displayMusicMenu();
    }

    songFileName = mergeStr(mergeStr(songs[songIndex].artist, "__"), songName);

    convertSpacesAndSpecialCharsToUnderscores(songFileName);
    convertToLowerCase(songFileName);

    songFileName = mergeStr(songFileName, ".mp3");

    if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)))
    {
        usleep(100000);
        system("cls");
        printf("Your entered Song does not have a Valid Music File.\nYou can add one via the Add Option in the Menu\n\n");
        free(songName);
        free(songFileName);
        free(musicFilePath);
        for (int j = 0; j < indexCount; j++)
        {
            freeSongInfos(songs[j]);
        }
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
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    // Write Song List back to File but write the new Song Informations for the given entrie Index
    for (int j = 0; j < i; j++)
    {
        if (strCmpIgnoreCase(songs[j].name, songName))
        {
            fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                    songs[j].name, songs[j].album, songs[j].artist,
                    songs[j].genre, songs[j].yearPublished, songs[j].rating,
                    songFileName);
        } else
        {
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
    free(songName);
    free(songFileName);
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    system("pause");
}


void playMusic()
{


    system("pause");
}

void displayMusicMenu()
{
    fflush(stdin);

    int option;
    int selectedOption = 1;

    while (TRUE)
    {
        system("cls");
        printListOptionsTitelScreen();
        printMusicOptions(selectedOption);

        option = getch();
        if (option == 224)
        {
            // Arrow key detected
            option = getch();
            if (option == 72)
            {
                selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
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

void printPartingLine()
{
    printf("|%32s|%21s|%21s|%30s|%5s|%7s|%-50s|\n",
           "----------------------------------", "---------------------------------------",
           "----------------------",
           "------------------------------", "------", "--------",
           "--------------------------------------------------");
}

void printTableHeader()
{
    system("cls");
    printPartingLine();
    printf("| %-32s | %-37s | %-20s | %-28s | %-4s | %-6s | %-48s |\n",
           "Name", "Album", "Artist", "Genre", "Year", "Rating", "Music File");
    printPartingLine();
}

void printTableRow(const TSongInfos song)
{
    printf("| %-32s | %-37s | %-20s | %-28s | %-4hd | %-6hd | %-48s |\n",
           song.name, song.album, song.artist, song.genre, song.yearPublished, song.rating,
           song.musicFileName);
}

void displayListedSongs()
{
    fflush(stdin);

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
                selectedOption = (selectedOption == 1) ? 4 : selectedOption - 1;
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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

void displayListedSongsStatic()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }


    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithValidMusicFile()
{
    system("cls");

    FILE *file = NULL;
    TSongInfos songs[indexCount];
    String songName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));
    String musicFilePath = (String) malloc(MAX_STR_LEN * sizeof(char));

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Output the songs with the desired album
    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        if (!strCmpIgnoreCase(songs[j].musicFileName, "none"))
        {
            printTableRow(songs[j]);
            printPartingLine();
        }
    }

    // Release of allocated memory
    free(songName);
    free(songFileName);
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsSorted()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
        {
            break;
        }
    }

    switch (selectedOption)
    {
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

void displayListedSongsSortedByName()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByNameA2Z()
{
    FILE *file = NULL;

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongInfosFromAGivenSong()
{
    system("cls");
    FILE *file = NULL;

    // Read the song data from the file
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired Song Name
    const String searchSong = malloc(MAX_STR_LEN * sizeof(char));
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByAlbum()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByAlbumA2Z()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenAlbum()
{
    system("cls");

    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired album
    const String searchAlbum = malloc(MAX_STR_LEN * sizeof(char));
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsSortedByArtist()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 3) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsSortedByArtistA2Z()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenArtist()
{
    system("cls");

    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Enter the desired artist
    const String searchArtist = malloc(MAX_STR_LEN * sizeof(char));
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByGenre()
{
    system("cls");

    FILE *file = NULL;
    // Dynamic allocation for the entered genre name
    char *searchGenre = malloc(MAX_STR_LEN * sizeof(char));

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
    TSongInfos *songs = malloc(indexCount * sizeof(TSongInfos));

    if (songs == NULL)
    {
        perror("Memory allocation error");
        free(searchGenre);
        exit(1);
    }

    // Dynamic allocation for each song element
    for (int i = 0; i < indexCount; i++)
    {
        for (int j = 0; i < indexCount; i++)
        {
            songs[i] = allocateSongInfos();
        }

        if (songs[i].name == NULL || songs[i].album == NULL ||
            songs[i].artist == NULL || songs[i].genre == NULL)
        {
            perror("Memory allocation error");
            free(searchGenre);

            // Release of allocated memory
            for (int j = 0; j < indexCount; j++)
            {
                freeSongInfos(songs[j]);
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
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(searchGenre);

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishing()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsByYearOfPublishingNew2Old()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }
    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort songs by release year (new - old)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishing);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByYearOfPublishingOld2New()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Sort songs by release year (old - new)
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishing);

    printTableHeader();

    for (int j = 0; j < i; j++)
    {
        printTableRow(songs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsNewerThanTheGivenYear()
{
    system("cls");

    FILE *file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year
    TSongInfos *filteredSongs = malloc(i * sizeof(TSongInfos));
    int filteredCount = 0;

    for (int j = 0; j < i; j++)
    {
        if (songs[j].yearPublished >= givenYear)
        {
            filteredSongs[filteredCount++] = songs[j];
        }
    }

    // Sort the filtered songs in ascending order of publication year
    qsort(filteredSongs, filteredCount, sizeof(TSongInfos), compareSongsByYearOfPublishing);

    printTableHeader();

    for (int j = 0; j < filteredCount; j++)
    {
        printTableRow(filteredSongs[j]);
        printPartingLine();
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    free(filteredSongs);

    printf("\n\n");
    system("pause");
}

void displayListedSongsOlderThanTheGivenYear()
{
    system("cls");

    FILE *file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
    {
        i++;
    }

    fclose(file);

    // Filter the songs according to the entered release year
    // and output them in ascending order of publication year
    qsort(songs, i, sizeof(TSongInfos), compareSongsByYearOfPublishing);

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
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenYearOfPublishing()
{
    system("cls");

    FILE *file = NULL;
    int givenYear;

    // User input for the desired publication year
    printf("Enter the Year:");
    scanf("%d", &givenYear);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRating()
{
    fflush(stdin);

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
            } else if (option == 80)
            {
                selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1;
            }
        } else if (option == 13)
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
            displayListedSongsSorted();
            break;
        default:
            break;
    }
}

void displayListedSongsByRatingBest2Worse()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsByRatingWorse2Best()
{
    FILE *file = NULL;
    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++)
    {
        freeSongInfos(songs[j]);
    }

    printf("\n\n");
    system("pause");
}

void displayListedSongsWithAGivenRating()
{
    system("cls");

    FILE *file = NULL;
    int givenRating;

    // User input for the desired rating
    printf("Enter the Rating:");
    scanf("%d", &givenRating);
    fflush(stdin); // Empty buffer to avoid unwanted characters in the buffer

    TSongInfos songs[indexCount];

    for (int i = 0; i < indexCount; i++)
    {
        songs[i] = allocateSongInfos();
    }

    // Open File to Read
    file = fopen(fullSongListFilePath, "rt");
    if (file == NULL)
    {
        perror("Error when opening the file");
        exit(1);
    }

    int i = 0;
    while (i < indexCount && fscanf(file, "%[^;];%[^;];%[^;];%[^;];%hd;%hd;%[^\n]\n",
                                    songs[i].name, songs[i].album,
                                    songs[i].artist, songs[i].genre, &songs[i].yearPublished,
                                    &songs[i].rating, songs[i].musicFileName) == 7)
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
        freeSongInfos(songs[j]);
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

void charReplace(const char old, const char new, char *haystack, const int maxLength)
{
    for (int i = 0; i < maxLength && haystack[i] != '\0'; i++)
    {
        if (haystack[i] == old)
        {
            haystack[i] = new;
        }
    }
}

char *mergeStr(const char *str1, const char *str2)
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

    const String mergedStr = (String) malloc(len1 + len2 + 1);

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

Boolean strCmpIgnoreCase(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (tolower((unsigned char) *str1) != tolower((unsigned char) *str2))
            return 0;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

TSongInfos allocateSongInfos()
{
    const TSongInfos songInfos = {
            (String) malloc(MAX_STR_LEN * sizeof(char)),
            (String) malloc(MAX_STR_LEN * sizeof(char)),
            (String) malloc(MAX_STR_LEN * sizeof(char)),
            (String) malloc(MAX_STR_LEN * sizeof(char)),
            0,
            0,
            (String) malloc(MAX_STR_LEN * sizeof(char)),
            FALSE
    };

    return songInfos;
}

void setIndexCount()
{
    FILE *file = fopen(fullSongListFilePath, "rt");

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

String getExecutablePath()
{
    // Reserve dynamic memory for the buffer
    String buffer = (String) malloc(MAX_PATH * sizeof(char));
    if (buffer == NULL)
    {
        // Memory allocation error
        return NULL;
    }

    GetModuleFileName(NULL, buffer, MAX_PATH);

    // Removing the filename to keep just the directory
    char *lastBackslash = strrchr(buffer, '\\');
    if (lastBackslash != NULL)
    {
        *lastBackslash = '\0';
    }

    // Return dynamic reserved path
    return buffer;
}

Boolean fileExists(const String fullFilePath)
{
    FILE *file = fopen(fullFilePath, "rb");
    if (file)
    {
        fclose(file);
        return TRUE;  // Datei existiert
    } else
    {
        return FALSE;  // Datei existiert nicht
    }
}

void convertSpacesAndSpecialCharsToUnderscores(char *str)
{
    if (str == NULL)
    {
        return;  // Handle NULL input
    }

    while (*str)
    {
        if (*str == ' ' || *str == '/' || *str == '\\' || *str == '|')
        {
            *str = '_';
        }
        str++;
    }
}

void convertToLowerCase(char *str)
{
    if (str == NULL)
    {
        return;  // Handle NULL input
    }

    while (*str)
    {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

int compareSongsByName(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    return strcmp(songA->name, songB->name);
}

int compareSongsByAlbum(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Compare the albums and sort in ascending order
    return strcmp(songA->album, songB->album);
}

int compareSongsByArtist(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    return strcmp(songA->artist, songB->artist);
}

int compareSongsByYearOfPublishing(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by publication year in ascending order
    return songA->yearPublished - songB->yearPublished;
}

int compareSongsWorse2Best(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by Rating in descending order
    return songB->rating - songA->rating;
}

int compareSongsBest2Worse(const void *a, const void *b)
{
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by Rating in ascending order
    return songA->rating - songB->rating;
}

void freeSongInfos(const TSongInfos songInfos)
{
    free(songInfos.name);
    free(songInfos.album);
    free(songInfos.artist);
    free(songInfos.genre);
    free(songInfos.musicFileName);
}

void exitHandler()
{
    free(fullSongListFilePath);
    free(fullMusicFolderFilePath);
    free(fullUserDataFilePath);
}

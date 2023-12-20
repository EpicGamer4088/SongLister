#include "utils.h"
#include "menues.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <conio.h>
#include <signal.h>
#include <windows.h>
#include <mmsystem.h>
#include <shlobj.h>
#include <shlwapi.h>

#pragma comment(lib, "winmm.lib")

int indexCount = 0;
String fullSongListFilePath = NULL;
String fullMusicFolderFilePath = NULL;
String fullUserDataFilePath = NULL;

void Main() {
    signal(SIGINT, exitHandler); // SIGINT is triggered, for example, by Ctrl+C
    signal(SIGTERM, exitHandler); // SIGTERM is triggered, for example, when exiting by the X in the top right

    fullSongListFilePath = (String) malloc(MAX_PATH * sizeof(char));
    fullMusicFolderFilePath = (String) malloc(MAX_PATH * sizeof(char));
    fullUserDataFilePath = (String) malloc(MAX_PATH * sizeof(char));

    checkAndHandleUserDataFile();
    checkAndHandleSongListFile();
    checkAndHandleMusicFolder();

    setIndexCount();

    checkIfAllMusicFileEntriesAreValid();

    MainMenu();
}

void setIndexCount() {
    FILE *file = fopen(fullSongListFilePath, "rt");

    indexCount = 0;

    while (1) {
        char line[MAX_STR_LEN];
        if (fgets(line, sizeof(line), file) != NULL) {
            // Check if line is valid (not empy or blankspaces)
            int validLine = 0;
            for (int i = 0; i < strlen(line); i++) {
                if (!isspace(line[i])) {
                    validLine = 1;
                    break;
                }
            }

            if (validLine && sscanf(line, "%*hd;%*[^;];%*[^;];%*[^;];%*[^;];%*hd;%*hd") == 0) {
                // Valid Line found, increment indexCount
                indexCount++;
            }
        }

        if (feof(file)) {
            break;
        }
    }

    fclose(file);
}

String getExecutablePath() {
    // Reserve dynamic memory for the buffer
    String buffer = (String) malloc(MAX_PATH * sizeof(char));
    if (buffer == NULL) {
        // Memory allocation error
        return NULL;
    }

    GetModuleFileName(NULL, buffer, MAX_PATH);

    // Removing the filename to keep just the directory
    char *lastBackslash = strrchr(buffer, '\\');
    if (lastBackslash != NULL) {
        *lastBackslash = '\0';
    }

    // Return dynamic reserved path
    return buffer;
}

Boolean fileExists(const String fullFilePath) {
    FILE *file = fopen(fullFilePath, "rb");
    if (file) {
        fclose(file);
        return TRUE;  // Datei existiert
    } else {
        return FALSE;  // Datei existiert nicht
    }
}

String openCSVFileDialog() {
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

    if (GetOpenFileName(&ofn) == TRUE) {
        return filePath;
    } else {
        return NULL;
    }
}

String openMusicFileDialog() {
    static char filePath[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    //ofn.lpstrFilter = "Media Files\0*.wav;*.mp3;*.mp4\0All Files\0*.*\0";
    ofn.lpstrFilter = ".wav\0*.wav\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        return filePath;
    } else {
        return NULL;
    }
}

String openFolderDialog() {
    static char folderPath[MAX_PATH];

    BROWSEINFO browseInfo = {0};
    browseInfo.hwndOwner = NULL;
    browseInfo.pidlRoot = NULL;
    browseInfo.pszDisplayName = folderPath;
    browseInfo.lpszTitle = "Select a folder";
    browseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
    browseInfo.lpfn = NULL;

    LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);

    if (pidl != NULL) {
        SHGetPathFromIDList(pidl, folderPath);
        CoTaskMemFree(pidl);
        return folderPath;
    } else {
        return NULL;
    }
}

void checkIfAllMusicFileEntriesAreValid() {
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
            free(songName);
            free(songFileName);

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

    for (int j = 0; j < i; j++) {
        songFileName = generateMusicFileName(songs[j]);

        if (fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)) &&
            strCmpIgnoreCase(songs[j].musicFileName, "none")) {
            // Open File to Write
            file = fopen(fullSongListFilePath, "wt");
            if (file == NULL) {
                perror("Error when opening the file");
                exit(1);
            }
            for (int k = 0; k < i; k++) {
                if (k == j) {
                    songs[k].musicFileName = songFileName;

                }
                fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                        songs[k].name, songs[k].album, songs[k].artist,
                        songs[k].genre, songs[k].yearPublished, songs[k].rating,
                        songs[k].musicFileName);

            }
            fclose(file);

        } else if (!fileExists(mergeStr(mergeStr(fullMusicFolderFilePath, "\\"), songFileName)) &&
                   !strCmpIgnoreCase(songs[j].musicFileName, "none")) {
            // Open File to Write
            file = fopen(fullSongListFilePath, "wt");
            if (file == NULL) {
                perror("Error when opening the file");
                exit(1);
            }
            for (int k = 0; k < i; k++) {
                if (!strCmpIgnoreCase(songs[j].musicFileName, "none")) {
                    fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                            songs[k].name, songs[k].album, songs[k].artist,
                            songs[k].genre, songs[k].yearPublished, songs[k].rating,
                            "none");
                } else {
                    fprintf(file, "%s;%s;%s;%s;%hd;%hd;%s\n",
                            songs[k].name, songs[k].album, songs[k].artist,
                            songs[k].genre, songs[k].yearPublished, songs[k].rating,
                            songs[k].musicFileName);
                }
            }
            fclose(file);
        }
    }

    // Release of allocated memory
    for (int j = 0; j < indexCount; j++) {
        freeSongInfos(songs[j]);
    }

    free(songs);
    free(songName);
}

void checkAndHandleUserDataFile() {
    fullUserDataFilePath = mergeStr(getExecutablePath(), USERDATA_FILE_NAME);

    FILE *file = fopen(fullUserDataFilePath, "rb");

    if (file == NULL) {
        // File does not exist, create the file
        file = fopen(fullUserDataFilePath, "wb");

        if (file != NULL) {
            // Write UserData to the file
            setUserData();
            writeUserDataIntoUserDataFile();
            fclose(file);
        } else {
            printf("Error creating file.\n");
        }
    } else {
        // File exists, read UserData from the file
        readUserDataFromUserDataFile();
        fclose(file);
    }
}

void checkAndHandleSongListFile() {
    FILE *file = fopen(fullSongListFilePath, "rt");

    if (file == NULL) {
        openCSVFileDialog();
    } else {
        fclose(file);
    }

    free(fullUserDataFilePath);
}

void checkAndHandleMusicFolder() {
    // Check if the folder already exists
    if (!(PathFileExistsA(fullMusicFolderFilePath))) {
        // Folder doesn't exist, open folder dialog
        openFolderDialog();
    }
}

void copyAndRenameMusicFile(const String srcPath, const String destFolder, const String newFileName) {
    String destPath = (String) malloc(MAX_PATH * sizeof(char));
    snprintf(destPath, MAX_PATH, "%s\\%s", destFolder, newFileName);

    if (CopyFile(srcPath, destPath, FALSE) == 0) {
        printf("\n\nError copying file. Error code: %lu\n", GetLastError());
    }

    free(destPath);
}

void removeMusicFileFromMusicFolder(const String filePath) {
    if (remove(filePath) != 0) {
        printf("\n\nError deleting file. Error code: %lu\n", GetLastError());
    }
}

void setUserData() {
    fullSongListFilePath = openCSVFileDialog();
    fullMusicFolderFilePath = openFolderDialog();
}

void writeUserDataIntoUserDataFile() {
    FILE *file = fopen(fullUserDataFilePath, "wb");
    if (file == NULL) {
        perror("Error opening file for writing in binary mode");
        exit(1);
    }

    // Writing "fullSongListFilePath" and "fullMusicFolderFilePath" into userdata.bin file in Binary mode
    fwrite(fullSongListFilePath, sizeof(char), strlen(fullSongListFilePath) + 1, file); // Include null terminator
    fwrite(fullMusicFolderFilePath, sizeof(char), strlen(fullMusicFolderFilePath) + 1, file); // Include null terminator

    fclose(file);
}

void readUserDataFromUserDataFile() {
    FILE *file = fopen(fullUserDataFilePath, "rb");
    if (file == NULL) {
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
    if (fullSongListFilePathLen >= fileSize - 1) {
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


void updateSongListFilePathInUserDataFile() {
    fullSongListFilePath = openCSVFileDialog();
    writeUserDataIntoUserDataFile();
    system("cls");
    printf("Succesfully Updated SongList File Path\n\n");
    system("pause");
}

void updateMusicFolderPathInUserDataFile() {
    fullMusicFolderFilePath = openFolderDialog();
    writeUserDataIntoUserDataFile();
    system("cls");
    printf("Succesfully Updated Music Folder Path\n\n");
    system("pause");
}

void playWaveFile(const String fullMusicFilePath, Boolean *isPlaying) {
    *isPlaying = TRUE; // Setze den Wiedergabestatus
    PlaySound(fullMusicFilePath, NULL, SND_ASYNC | SND_FILENAME);
}

void pauseResumePlayback(const String fullMusicFilePath, Boolean *isPlaying) {
    if (*isPlaying) {
        *isPlaying = FALSE; // Setze den Wiedergabestatus
        PlaySound(NULL, NULL, SND_PURGE);
    } else {
        *isPlaying = TRUE; // Setze den Wiedergabestatus
        playWaveFile(fullMusicFilePath, isPlaying);
    }
}

String generateMusicFileName(const TSongInfos songInfos) {
    String songFileName = (String) malloc(MAX_STR_LEN * sizeof(char));

    if (songFileName != NULL) {
        songFileName = mergeStr(songInfos.artist, "__");
        songFileName = mergeStr(songFileName, songInfos.name);

        convertSpacesAndSpecialCharsToUnderscores(songFileName);
        convertToLowerCase(songFileName);

        songFileName = mergeStr(songFileName, ".wav");
    }

    return songFileName;
}


void convertSpacesAndSpecialCharsToUnderscores(char *str) {
    if (str == NULL) {
        return;  // Handle NULL input
    }

    while (*str) {
        if (*str == ' ' || *str == '/' || *str == '\\' || *str == '|') {
            *str = '_';
        }
        str++;
    }
}

void convertToLowerCase(char *str) {
    if (str == NULL) {
        return;
    }

    // Iterate through each character in the string
    while (*str) {
        // Convert the character to lowercase without using tolower from the string library
        if (*str >= 'A' && *str <= 'Z') {
            *str += ('a' - 'A');  // Convert uppercase to lowercase
        }
        str++;
    }
}

int compareSongsByName(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    return strcmp(songA->name, songB->name);
}

int compareSongsByAlbum(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Compare the albums and sort in ascending order
    return strcmp(songA->album, songB->album);
}

int compareSongsByArtist(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    return strcmp(songA->artist, songB->artist);
}

int compareSongsByYearOfPublishingNew2Old(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by publication year in ascending order
    return songB->yearPublished - songA->yearPublished;
}

int compareSongsByYearOfPublishingOld2New(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by publication year in ascending order
    return songA->yearPublished - songB->yearPublished;
}

int compareSongsWorse2Best(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by Rating in descending order
    return songB->rating - songA->rating;
}

int compareSongsBest2Worse(const void *a, const void *b) {
    const TSongInfos *songA = (const TSongInfos *) a;
    const TSongInfos *songB = (const TSongInfos *) b;

    // Sort by Rating in ascending order
    return songA->rating - songB->rating;
}

void charReplace(const char old, const char new, char *haystack, const int maxLength) {
    for (int i = 0; i < maxLength && haystack[i] != '\0'; i++) {
        if (haystack[i] == old) {
            haystack[i] = new;
        }
    }
}

String mergeStr(const char *str1, const char *str2) {
    int len1 = 0;
    int len2 = 0;

    while (str1[len1] != '\0') {
        len1++;
    }

    while (str2[len2] != '\0') {
        len2++;
    }

    const String mergedStr = (String) malloc(len1 + len2 + 1);

    if (mergedStr == NULL) {
        exit(1);
    }

    for (int i = 0; i < len1; i++) {
        mergedStr[i] = str1[i];
    }

    for (int i = 0; i < len2; i++) {
        mergedStr[len1 + i] = str2[i];
    }

    mergedStr[len1 + len2] = '\0';

    return mergedStr;
}

Boolean strCmpIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char) *str1) != tolower((unsigned char) *str2))
            return 0;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

TSongInfos allocateSongInfos() {
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

    if (songInfos.name == NULL || songInfos.album == NULL | songInfos.artist == NULL ||
        songInfos.genre == NULL || songInfos.musicFileName == NULL) {
    }

    return songInfos;
}

void freeSongInfos(const TSongInfos songInfos) {
    free(songInfos.name);
    free(songInfos.album);
    free(songInfos.artist);
    free(songInfos.genre);
    free(songInfos.musicFileName);
}

void exitProgramm(const int returnValue) {
    system("cls");
    printf("The Program will Close. Goodbye!\n\n");
    usleep(1000000);
    system("PAUSE");
    exit(returnValue);
}

void exitHandler() {
    free(fullSongListFilePath);
    free(fullMusicFolderFilePath);
    free(fullUserDataFilePath);
}



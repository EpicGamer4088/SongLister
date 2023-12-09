#ifndef SONGS_H
#define SONGS_H

#include <stdio.h>

#define MAX_STR_LEN 255                         // Maximum String Length
#define USERDATA_FILE_NAME "/userdata.bin"      // File Name for Userdata

/**
 * @brief Defines the type `String` as a pointer to a null-terminated char array.
 *
 * The `String` type is used to represent strings in C. It is a pointer to a char array
 * terminated with a null character ('\0').
 */
typedef char *String;

/**
 * @brief External declaration for the variable `indexCount`.
 *
 * The `indexCount` variable is declared as external. It is used to keep track of
 * the current index count in the program and for assigning unique identifiers to songs.
 * It is going to be initialized in the Main function.
 */
extern int indexCount;

/**
 * @brief External declaration for the variable `fullSongListFilePath`.
 *
 * The `fullSongListFilePath` variable is declared as external. It is used to store the full
 * path to the SongList CSV file. It is going to be initialized in the Main function.
 */
extern String fullSongListFilePath;

/**
 * @brief External declaration for the variable `fullMusicFolderFilePath`.
 *
 * The `fullMusicFolderFilePath` variable is declared as external. It represents the full path
 * to the folder where music files are stored. It's value points to the directory where music files
 * are stored. It is going to be initialized in the Main function.
 */
extern String fullMusicFolderFilePath;

/**
 * @brief External declaration for the variable `fullUserDataFilePath`.
 *
 * The `fullUserDataFilePath` variable is declared as external. It serves as the full path
 * to the UserData file, storing important program configuration data.
 * The value points to the location of the userdata.bin file.
 * It is going to be initialized in the Main function.
 */
extern String fullUserDataFilePath;

/**
 * @brief Defines an enumeration type `Boolean` representing Boolean values.
 *
 * The `Boolean` type is an enumeration with two possible values: `FALSE` and `TRUE`.
 * It is used to represent Boolean logic in, providing a more readable
 * alternative to using integer values directly.
 */
typedef enum Boolean
{
    FALSE, /**< Represents the Boolean value `false`. */
    TRUE   /**< Represents the Boolean value `true`. */
}
Boolean;

/**
 * @brief Defines a structure `SongInfos` to represent information about a song.
 *
 * The `SongInfos` structure includes various fields such as index, name, album, artist,
 * genre, yearPublished, rating, musicFileName, and musicFile, providing a way to store
 * information related to a song. This structure is aliased as `TSongInfos` for convenience.
 *
 * - `name`: Name of the song.
 * - `album`: Album containing the song.
 * - `artist`: Artist who performed the song.
 * - `genre`: Genre of the song.
 * - `yearPublished`: Year the song was published.
 * - `rating`: Rating assigned to the song.
 * - `musicFileName`: File name of the song's associated music file.
 * - `musicFile`: Boolean indicating whether a valid music file is associated with the song.
 */
typedef struct SongInfos
{
    String name;            /**< Name of the song. */
    String album;           /**< Album containing the song. */
    String artist;          /**< Artist who performed the song. */
    String genre;           /**< Genre of the song. */
    short yearPublished;    /**< Year the song was published. */
    short rating;           /**< Rating assigned to the song. */
    String musicFileName;   /**< File name of the song's associated music file. */
    Boolean musicFile;      /**< Boolean indicating whether a valid music file is associated with the song. */
}
TSongInfos;


void Main();


void MainMenu();


void checkIfAllMusicFileEntriesAreValid() ;


void printTitelScreen();


void printListOptionsTitelScreen();


void printMenuOptions(const int selectedOption);


void printListOptions(const int selectedOption);


void printMusicOptions(const int selectedOption);


void printChangeUserDataOptions(const int selectedOption);


void printSortedListOptions(const int selectedOption);


void printSortedListByNameOptions(const int selectedOption);


void printSortedListByAlbumOptions(const int selectedOption);


void printSortedListByArtistOptions(const int selectedOption);


void printSortedListByYearOfPublishingOptions(const int selectedOption);


void printSortedListByRatingOptions(const int selectedOption);


String openCSVFileDialog();


String openMusicFileDialog();


String openFolderDialog();


void copyAndRenameMusicFile(const String srcPath, const String destFolder, const String newFileName);


void removeMusicFileFromMusicFolder(const String filePath);


void checkAndHandleUserDataFile();


void checkAndHandleMusicFileFolder();


void setUserData();


void writeUserDataIntoUserDataFile();


void readUserDataFromUserDataFile();


void updateUserData();


void updateSongListFilePathInUserDataFile();


void updateMusicFolderPathInUserDataFile();


TSongInfos inputSongInfos();


void addNewSong();


void removeSong();


void changeSongInformations();


void addMusicFile();


String addMusicFileForNewSong(const TSongInfos songInfos);


void removeMusicFile();


void changeMusicFile();


void playMusic();


void displayMusicMenu();


void printPartingLine();


void printTableHeader();


void printTableRow(const TSongInfos song);


void displayListedSongs();


void displayListedSongsStatic();


void displayListedSongsWithValidMusicFile();


void displayListedSongsSorted();


void displayListedSongsSortedByName();


void displayListedSongsSortedByNameA2Z();


void displayListedSongInfosFromAGivenSong();


void displayListedSongsSortedByAlbum();


void displayListedSongsSortedByAlbumA2Z();


void displayListedSongsWithAGivenAlbum();


void displayListedSongsSortedByArtist();


void displayListedSongsSortedByArtistA2Z();


void displayListedSongsWithAGivenArtist();


void displayListedSongsByGenre();


void displayListedSongsByYearOfPublishing();


void displayListedSongsByYearOfPublishingNew2Old();


void displayListedSongsByYearOfPublishingOld2New();


void displayListedSongsNewerThanTheGivenYear();


void displayListedSongsOlderThanTheGivenYear();


void displayListedSongsWithAGivenYearOfPublishing();


void displayListedSongsByRating();


void displayListedSongsByRatingBest2Worse();


void displayListedSongsByRatingWorse2Best();


void displayListedSongsWithAGivenRating();


void exitProgramm(const int returnValue);


void charReplace(const char old, const char new, char *haystack, const int maxLength);


char *mergeStr(const char *str1, const char *str2);


Boolean strCmpIgnoreCase(const char *str1, const char *str2);


TSongInfos allocateSongInfos();


void setIndexCount();


String getExecutablePath();


Boolean fileExists(const String fullFilePath);


void convertSpacesAndSpecialCharsToUnderscores(char* str);


void convertToLowerCase(char* str);


int compareSongsByName(const void *a, const void *b);


int compareSongsByAlbum(const void *a, const void *b);


int compareSongsByArtist(const void *a, const void *b);


int compareSongsByYearOfPublishing(const void *a, const void *b);


int compareSongsWorse2Best(const void *a, const void *b);


int compareSongsBest2Worse(const void *a, const void *b);


void freeSongInfos(const TSongInfos songInfos);


void exitHandler();

#endif //SONGS_H

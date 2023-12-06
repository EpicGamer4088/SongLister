#ifndef SONGS_H
#define SONGS_H

#include <stdio.h>

#define MAX_STR_LEN 255

#define DEFAULT_FILE_NAME "SongList"
#define DEFAULT_FILE_PATH "../"
#define USERDATA_FILE_NAME "/userdata.bin"

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
 * path to the SongList CSV file and is going to be initialized in the Main function.
 */
extern String fullSongListFilePath;


extern String fullMusicFolderFilePath;


extern String fullUserDataFilePath;

/**
 * @brief Defines a structure `UserData` to represent user-specific data.
 *
 * The `UserData` structure includes fields such as `fullListFilePath`, `fullMusicFolderFilePath`,
 * and `indexCount`, providing a way to store the Data read in from the the UserData File
 * This structure is aliased as `UserData` for convenience.
 */
typedef struct UserData
{
    String fullSongListFilePath;          /**< Full file path for storing song data list. */
    String fullMusicFolderFilePath;   /**< Full file path for the music folder. */
    int indexCount;                   /**< Count of song entries in the data list. */
}
UserData;

extern UserData userData;

/**
 * @brief Defines an enumeration type `bool` representing bool values.
 *
 * The `bool` type is an enumeration with two possible values: `FALSE` and `TRUE`.
 * It is used to represent bool logic in, providing a more readable
 * alternative to using integer values directly.
 */
typedef enum bool
{
    FALSE, /**< Represents the bool value `false`. */
    TRUE   /**< Represents the bool value `true`. */
}
bool;

/**
 * @brief Defines a structure `SongInfos` to represent information about a song.
 *
 * The `SongInfos` structure includes various fields such as index, name, album, artist,
 * genre, yearPublished, and rating, providing a way to store information related to a song.
 * This structure is aliased as `TSongInfos` for convenience.
 */
typedef struct SongInfos
{
    short index;            /**< Index of the song. */
    String name;            /**< Name of the song. */
    String album;           /**< Album containing the song. */
    String artist;          /**< Artist who performed the song. */
    String genre;           /**< Genre of the song. */
    short yearPublished;    /**< Year the song was published. */
    short rating;           /**< Rating assigned to the song. */
}
TSongInfos;

/**
 * @brief Entry point for the main function.
 *
 * The `Main` function serves as the entry point for the program. It sets up signal
 * handlers for SIGINT (Ctrl+C) and SIGTERM (exit by the X in the top right), allocates
 * memory for `fullSongListFilePath`, initializes a file pointer (`file`), and declares a bool
 * variable `songFileLoaded` initialized to FALSE. It also initializes a constant
 * `TSongInfos` structure named `songInfos` with default values. Finally, the `MainMenu`
 * function is called, passing the file pointer, song file loading status, and song
 * information structure as arguments to start the main program logic.
 */
void Main();

/**
 * @brief Main menu function for handling user interaction for Start Menu.
 *
 * The `MainMenu` function takes parameters including a file pointer `file` for
 * song data, a bool `songFileLoaded` indicating whether the song file is loaded,
 * and a constant `TSongInfos` structure `songInfos` representing song information.
 * It presents a menu to the user, allowing them to perform various actions related
 * to song data. The function continuously runs until the user chooses to exit.
 *
 * @param file The file pointer for song data.
 * @param songFileLoaded A bool indicating whether the song file is loaded.
 * @param songInfos A constant structure representing song information.
 */
void MainMenu(const TSongInfos songInfos);

/**
 * @brief Prints the title screen for the Song Rater program.
 *
 * The `printTitelScreen` function displays a simple title screen for the Song Rater
 * program, providing a visual representation to the user when the program is executed.
 */
void printTitelScreen();

/**
 * @brief Prints the title screen for the Song Lister program.
 *
 * The `printListOptionsTitelScreen` function displays a simple title screen for the
 * Song Lister program, providing a visual representation to the user when listing options.
 */
void printListOptionsTitelScreen();

/**
 * @brief Prints the menu options for the Song Rater program.
 *
 * The `printMenuOptions` function displays the menu options for the Song Rater program,
 * indicating the user's selected option with a ">>" marker. The options include adding
 * a new song, deleting a song, changing song information, listing songs, and exiting the program.
 *
 * @param selectedOption The user's selected option (1 to 5).
 */
void printMenuOptions(const int selectedOption);

/**
 * @brief Prints the list options for the Song Lister program.
 *
 * The `printListOptions` function displays the list options for the Song Lister program,
 * indicating the user's selected option with a ">>" marker. The options include listing
 * songs, listing songs sorted, and returning to the main menu.
 *
 * @param selectedOption The user's selected option (1 to 3).
 */
void printListOptions(const int selectedOption);


void printChangeUserDataOptions(const int selectedOption);

/**
 * @brief Prints the sorted list options for the Song Lister program.
 *
 * The `printSortedListOptions` function displays the sorted list options for the Song
 * Lister program, indicating the user's selected option with a ">>" marker. The options
 * include listing songs sorted by name, album, artist, entries from a given genre,
 * year of publishing, and rating. Additionally, there is an option to go one step back.
 *
 * @param selectedOption The user's selected option (1 to 7).
 */
void printSortedListOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by name in the Song Lister program.
 *
 * The `printSortedListByNameOptions` function displays the options for sorting the list
 * by name in the Song Lister program, indicating the user's selected option with a ">>" marker.
 * The options include listing songs sorted by name (A-Z), listing an entry from a given song,
 * and going one step back.
 *
 * @param selectedOption The user's selected option (1 to 3).
 */
void printSortedListByNameOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by album in the Song Lister program.
 *
 * The `printSortedListByAlbumOptions` function displays the options for sorting the list
 * by album in the Song Lister program, indicating the user's selected option with a ">>" marker.
 * The options include listing songs sorted by album (A-Z), listing entries from a given album,
 * and going one step back.
 *
 * @param selectedOption The user's selected option (1 to 3).
 */
void printSortedListByAlbumOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by artist in the Song Lister program.
 *
 * The `printSortedListByArtistOptions` function displays the options for sorting the list
 * by artist in the Song Lister program, indicating the user's selected option with a ">>" marker.
 * The options include listing songs sorted by artist (A-Z), listing entries from a given artist,
 * and going one step back.
 *
 * @param selectedOption The user's selected option (1 to 3).
 */
void printSortedListByArtistOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by year of publishing in the Song Lister program.
 *
 * The `printSortedListByYearOfPublishingOptions` function displays the options for sorting
 * the list by year of publishing in the Song Lister program, indicating the user's selected
 * option with a ">>" marker. The options include listing songs from newest to oldest,
 * oldest to newest, newer than a given year, older than a given year, entries from a given
 * year of publishing, and going one step back.
 *
 * @param selectedOption The user's selected option (1 to 6).
 */
void printSortedListByYearOfPublishingOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by rating in the Song Lister program.
 *
 * The `printSortedListByRatingOptions` function displays the options for sorting
 * the list by rating in the Song Lister program, indicating the user's selected
 * option with a ">>" marker. The options include listing songs from best to worst,
 * worst to best, entries from a given rating, and going one step back.
 *
 * @param selectedOption The user's selected option (1 to 4).
 */
void printSortedListByRatingOptions(const int selectedOption);

/**
 * @brief Opens a file dialog for selecting a CSV file.
 *
 * The `openCSVFileDialog` function displays a file dialog that allows the user to select
 * a CSV file. If the user selects a file, the function returns the full path of the selected file.
 * If no file is selected or an error occurs, the function returns NULL.
 *
 * @return A string containing the full path of the selected CSV file, or NULL if no file is selected.
 */
String openCSVFileDialog();

/**
 * @brief Opens a folder dialog for selecting a folder.
 *
 * The `openFolderDialog` function displays a folder dialog that allows the user to select a folder.
 * If the user selects a folder, the function returns the full path of the selected folder.
 * If no folder is selected or an error occurs, the function returns NULL.
 *
 * @return A string containing the full path of the selected folder, or NULL if no folder is selected.
 */
String openFolderDialog();


void checkAndHandleUserDataFile();


void checkAndHandleMusicFileFolder();


void setUserData();


void writeUserDataIntoUserDataFile();


void readUserDataFromUserDataFile();


FILE *openFile(const String filePath, const String mode);

/**
 * @brief Reopens a file with the specified mode.
 *
 * The `reopenFile` function closes the provided file using `fclose` and then reopens
 * it with the specified mode using `fopen`. The full file path is retrieved from the
 * global variable `fullSongListFilePath`. The reopened file pointer is returned.
 *
 * @param file The file pointer to be reopened.
 * @param mode The mode to be used for reopening the file (e.g., "r", "w", "a", etc.).
 * @return The reopened file pointer.
 */
FILE *reopenFile(FILE *file,const String filePath, const String mode);

/**
 * @brief Selects the song data file for reading and writing.
 *
 * The `selectSongDataFile` function checks if the song data file specified by
 * the global variable `fullSongListFilePath` already exists. If the file does not exist,
 * it creates the file and returns the file pointer with the specified mode.
 * If the file already exists, it simply returns the file pointer with the specified mode.
 * The function updates the `songFileLoaded` bool accordingly.
 *
 * @param mode The mode to be used for opening the file (e.g., "r", "w", "a", etc.).
 * @param songFileLoaded A pointer to a bool indicating whether the song file is loaded.
 * @return The file pointer for the selected song data file.
 */
FILE *selectSongDataFile(const char *mode, bool *songFileLoaded);

/**
 * @brief Takes user input for song information and returns a TSongInfos structure.
 *
 * The `inputSongInfos` function prompts the user to input various information about a song,
 * including the name, album, artist, genre, year published, and rating. The function allocates
 * memory for the `TSongInfos` structure using `allocateSongInfos` and assigns the input values
 * to the corresponding fields. The resulting `TSongInfos` structure is returned.
 *
 * @return A `TSongInfos` structure containing the user-inputted song information.
 */
TSongInfos inputSongInfos();

/**
 * @brief Adds a new song entry to the song data file.
 *
 * The `addNewSong` function adds a new song entry to the specified file. It first checks
 * if the file already has valid entries and adjusts the `indexCount` accordingly. The function
 * then prompts the user to input song information using `inputSongInfos`. The inputted data is
 * written to the end of the file in CSV format. The function increments the `indexCount` and
 * frees the allocated memory for song information. A success message is displayed.
 *
 * @param file The file pointer to the song data file.
 */
void addNewSong();

/**
 * @brief Adds a new song entry to the song data file.
 *
 * The `addNewSong` function adds a new song entry to the specified file. It first checks
 * if the file already has valid entries and adjusts the `indexCount` accordingly. The function
 * then prompts the user to input song information using `inputSongInfos`. The inputted data is
 * written to the end of the file in CSV format. The function increments the `indexCount` and
 * frees the allocated memory for song information. A success message is displayed.
 *
 * @param file The file pointer to the song data file.
 */
void removeSong();

/**
 * @brief Changes the information of a song entry in the song data file.
 *
 * The `changeSongInformations` function allows the user to change the information of a song entry
 * in the specified file. The user is prompted to input the index of the entry to be edited. If the
 * user enters "-1," the function displays the list of songs with their indexes. After selecting an
 * index, the user is prompted to enter the new song information using `inputSongInfos`. The function
 * then reads the existing song entries from the file, updates the information for the selected index,
 * and writes the modified entries back to the file.
 *
 * @param file The file pointer to the song data file.
 */
void changeSongInformations();


void changeUserData();

/**
 * @brief Prints a formatted parting line for better visual separation.
 *
 * The `printPartingLine` function prints a formatted parting line with specified column headers
 * to visually separate sections in the console output.
 */
void printPartingLine();

/**
 * @brief Prints the header for the song data table.
 *
 * The `printTableHeader` function clears the console screen, prints a parting line, and then
 * prints a formatted table header with column names, including Index, Name, Album, Artist, Genre,
 * Year, and Rating. Another parting line is printed for visual separation.
 */
void printTableHeader();

/**
 * @brief Prints a table row with song information.
 *
 * The `printTableRow` function prints a formatted table row with the provided song information,
 * including the Index, Name, Album, Artist, Genre, Year, and Rating of the song.
 *
 * @param song The `TSongInfos` structure containing song information.
 */
void printTableRow(const TSongInfos song);

/**
 * @brief Displays the list of songs with various options.
 *
 * The `displayListedSongs` function displays the list of songs with options for sorting and
 * navigating through the list. The user can choose to display the list as it is, sorted, or
 * return to the main menu. The function uses the `printListOptionsTitelScreen` function to
 * print the title screen for the list options and the `printListOptions` function to display
 * the available options.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongs();

/**
 * @brief Displays the list of songs without any sorting.
 *
 * The `displayListedSongsStatic` function reads the song entries from the file and
 * displays them in a table format without any sorting. It allocates memory for song
 * information, reads the data from the file, prints the table header, and then prints
 * each song's information in a formatted table row. After displaying the list, it rewinds
 * the file and waits for user input to continue.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsStatic();

/**
 * @brief Displays the list of songs with sorting options.
 *
 * The `displayListedSongsSorted` function provides sorting options for the user to choose from.
 * The user can select different criteria for sorting the songs, such as by name, album, artist, genre,
 * year of publishing, rating, or return to the previous menu. The function uses the `printListOptionsTitelScreen`
 * function to print the title screen for the sorting options and the `printSortedListOptions` function to
 * display the available sorting options.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSorted();

/**
 * @brief Displays the list of songs sorted by name with sorting options.
 *
 * The `displayListedSongsSortedByName` function provides sorting options for songs by name.
 * The user can choose to list songs in alphabetical order or display information about a specific song.
 * The function uses the `printListOptionsTitelScreen` function to print the title screen for sorting options
 * and the `printSortedListByNameOptions` function to display the available sorting options.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByName();

/**
 * @brief Displays the list of songs sorted by name in ascending order (A-Z).
 *
 * The `displayListedSongsSortedByNameA2Z` function reads the song information from the file,
 * sorts the songs by name in ascending order, and displays the sorted list. It uses the `printTableHeader`,
 * `printTableRow`, and `printPartingLine` functions to print the table header, rows, and a separating line, respectively.
 * The allocated memory for song information is released after displaying the list.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByNameA2Z();

/**
 * @brief Displays song information for a given song name.
 *
 * The `displayListedSongInfosFromAGivenSong` function reads the song information from the file,
 * prompts the user to enter a song name, and displays the information for the songs with the specified name.
 * It uses the `printTableHeader`, `printTableRow`, and `printPartingLine` functions to print the table header, rows,
 * and a separating line, respectively. The dynamically allocated memory for song information is released after displaying the list.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongInfosFromAGivenSong();

/**
 * @brief Displays the list of songs sorted by album name in ascending order.
 *
 * The `displayListedSongsSortedByAlbum` function clears the input buffer, prompts the user to select
 * sorting options for the album, and displays the list of songs sorted accordingly. It uses functions such as
 * `reopenFile`, `printListOptionsTitelScreen`, `printSortedListByAlbumOptions`, `displayListedSongsSortedByAlbumA2Z`,
 * `displayListedSongsWithAGivenAlbum`, and other related utility functions. The dynamically allocated memory for song information
 * is released after displaying the list.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByAlbum();

/**
 * @brief Displays the list of songs sorted by album name in ascending order (A-Z).
 *
 * The `displayListedSongsSortedByAlbumA2Z` function reads the song data from the file, allocates memory
 * for the songs, sorts them by album name in ascending order, and then displays the sorted list. It uses
 * functions such as `printTableHeader`, `printTableRow`, `printPartingLine`, and `system`. The dynamically
 * allocated memory for song information is released after displaying the list.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByAlbumA2Z();

/**
 * @brief Displays the list of songs with a given album name.
 *
 * The `displayListedSongsWithAGivenAlbum` function reads the song data from the file, allocates memory
 * for the songs, prompts the user to enter a desired album, and then displays the songs with the entered
 * album name. It uses functions such as `printTableHeader`, `printTableRow`, `printPartingLine`, `fgets`,
 * `charReplace`, `strCmpIgnoreCase`, `rewind`, `free`, `system`, and `printf`. The dynamically allocated
 * memory for song information and the entered album name is released after displaying the list.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsWithAGivenAlbum();

/**
 * @brief Displays the list of songs sorted by artist name.
 *
 * The `displayListedSongsSortedByArtist` function provides an interactive menu for the user to choose
 * different options related to sorting songs by artist. It uses functions such as `clearInputBuffer`,
 * `reopenFile`, `system`, `printListOptionsTitelScreen`, `printSortedListByArtistOptions`, `getch`,
 * `displayListedSongsSortedByArtistA2Z`, `displayListedSongsWithAGivenArtist`, and a switch statement
 * for handling user choices.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByArtist();

/**
 * @brief Displays the list of songs sorted by artist name in ascending order (A-Z).
 *
 * The `displayListedSongsSortedByArtistA2Z` function reads song data from the file, allocates memory,
 * sorts the songs by artist in ascending order, prints the sorted list using `printTableHeader` and
 * `printTableRow`, releases allocated memory, and then waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsSortedByArtistA2Z();

/**
 * @brief Displays the list of songs with a given artist.
 *
 * The `displayListedSongsWithAGivenArtist` function reads song data from the file, allocates memory,
 * prompts the user to enter the desired artist, prints the songs with the specified artist using
 * `printTableHeader` and `printTableRow`, releases allocated memory, and then waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsWithAGivenArtist();

/**
 * @brief Displays the list of songs filtered by genre.
 *
 * The `displayListedSongsByGenre` function prompts the user to input a genre, reads the song data from the file,
 * filters songs based on the entered genre substring, and displays the results using `printTableHeader` and `printTableRow`.
 * Memory is dynamically allocated for the entered genre, song information, and each song element.
 * The allocated memory is released before waiting for user input.
 *
 * @param file Pointer to the file containing song information.
 */
void displayListedSongsByGenre();

/**
 * @brief Displays the list of songs sorted by year of publishing.
 *
 * The `displayListedSongsByYearOfPublishing` function presents a menu allowing the user to choose different sorting
 * and filtering options based on the year of publishing. It reads the user's selection, calls corresponding functions
 * for sorting and filtering, and then repeats the process until the user chooses to exit. The sorting and filtering
 * options include sorting from new to old, old to new, displaying songs newer or older than a given year, and displaying
 * songs with a specific year of publishing.
 *
 * @param file Pointer to the file containing song information.
 */
void displayListedSongsByYearOfPublishing();

/**
 * @brief Displays the list of songs sorted by year of publishing in descending order (new to old).
 *
 * The `displayListedSongsByYearOfPublishingNew2Old` function reads song data from the file, allocates memory,
 * and sorts the songs by their year of publishing in descending order using `compareSongsByYearOfPublishingNew2Old`.
 * It then prints the sorted songs using `printTableHeader` and `printTableRow`, releases allocated memory, and
 * waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsByYearOfPublishingNew2Old();

/**
 * @brief Displays the list of songs sorted by year of publishing in ascending order (old to new).
 *
 * The `displayListedSongsByYearOfPublishingOld2New` function reads song data from the file, allocates memory,
 * and sorts the songs by their year of publishing in ascending order using `compareSongsByYearOfPublishingOld2New`.
 * It then prints the sorted songs using `printTableHeader` and `printTableRow`, releases allocated memory, and
 * waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsByYearOfPublishingOld2New();

/**
 * @brief Displays the list of songs published in or after a given year.
 *
 * The `displayListedSongsNewerThanTheGivenYear` function prompts the user to input a desired publication year,
 * reads song data from the file, allocates memory, filters and counts songs with a publication year greater than or
 * equal to the entered year, sorts the filtered songs by year of publishing in ascending order using
 * `compareSongsByYearOfPublishingNew2Old`, prints the sorted songs using `printTableHeader` and `printTableRow`,
 * releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsNewerThanTheGivenYear();

/**
 * @brief Displays the list of songs published in or before a given year.
 *
 * The `displayListedSongsOlderThanTheGivenYear` function prompts the user to input a desired publication year,
 * reads song data from the file, allocates memory, sorts the songs by year of publishing in ascending order using
 * `compareSongsByYearOfPublishingOld2New`, prints the songs with a publication year less than or equal to
 * the entered year using `printTableHeader` and `printTableRow`, releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsOlderThanTheGivenYear();

/**
 * @brief Displays the list of songs with a given year of publishing.
 *
 * The `displayListedSongsWithAGivenYearOfPublishing` function prompts the user to input a desired publication year,
 * reads song data from the file, allocates memory, prints the songs with a publication year equal to
 * the entered year using `printTableHeader` and `printTableRow`, releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsWithAGivenYearOfPublishing();

/**
 * @brief Displays the list of songs sorted by rating.
 *
 * The `displayListedSongsByRating` function allows the user to choose from various sorting options,
 * such as sorting from best to worst rating, worst to best rating, or displaying songs with a specific rating.
 * It reads song data from the file, allocates memory, prints the sorted or filtered songs using `printTableHeader`
 * and `printTableRow`, releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsByRating();

/**
 * @brief Displays the list of songs sorted from best to worst rating.
 *
 * The `displayListedSongsByRatingBest2Worse` function reads song data from the file, allocates memory,
 * sorts the songs from best to worst rating using `qsort`, prints the sorted songs using `printTableHeader`
 * and `printTableRow`, releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsByRatingBest2Worse();

/**
 * @brief Displays the list of songs sorted from worst to best rating.
 *
 * The `displayListedSongsByRatingWorse2Best` function reads song data from the file, allocates memory,
 * sorts the songs from worst to best rating using `qsort`, prints the sorted songs using `printTableHeader`
 * and `printTableRow`, releases allocated memory, and waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsByRatingWorse2Best();

/**
 * @brief Displays the list of songs with a given rating.
 *
 * The `displayListedSongsWithAGivenRating` function reads song data from the file, allocates memory,
 * prompts the user to enter the desired rating, prints the songs with the specified rating using
 * `printTableHeader` and `printTableRow`, releases allocated memory, and then waits for user input.
 *
 * @param file The file pointer to the song data file.
 */
void displayListedSongsWithAGivenRating();

/**
 * @brief Clears the input buffer by consuming any remaining characters.
 *
 * The `clearInputBuffer` function reads characters from the standard input until a newline
 * or the end of the file is encountered, effectively clearing the input buffer.
 */
void exitProgramm(const int returnValue);

/**
 * @brief Clears the input buffer by consuming any remaining characters.
 *
 * The `clearInputBuffer` function reads characters from the standard input until a newline
 * or the end of the file is encountered, effectively clearing the input buffer.
 */
void clearInputBuffer();

/**
 * @brief Replaces occurrences of a character in a string.
 *
 * The `charReplace` function replaces all occurrences of the specified 'old' character
 * with the 'new' character in the given string 'haystack' up to the specified 'maxLength'.
 *
 * @param old The character to be replaced.
 * @param new The character to replace 'old' with.
 * @param haystack The string in which replacements will be made.
 * @param maxLength The maximum length of the string to consider for replacements.
 */
void charReplace(const char old, const char new, char *haystack, const int maxLength);

/**
 * @brief Merges two strings into a new dynamically allocated string.
 *
 * The `mergeStr` function concatenates two input strings `str1` and `str2` into a new
 * dynamically allocated string, and returns the result. The caller is responsible for
 * freeing the memory allocated for the returned string.
 *
 * @param str1 The first string to be merged.
 * @param str2 The second string to be merged.
 * @return A dynamically allocated string containing the concatenated result of `str1` and `str2`.
 *         The caller is responsible for freeing the allocated memory.
 */
char *mergeStr(const char *str1, const char *str2);

/**
 * @brief Compares two strings for equality.
 *
 * The `strCmp` function compares two input strings `str1` and `str2` character by character
 * and returns TRUE if they are equal, and FALSE otherwise.
 *
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return TRUE if the strings are equal, FALSE otherwise.
 */
bool strCmp(const char *str1, const char *str2);

/**
 * @brief Compares two strings for equality, ignoring case.
 *
 * The `strCmpIgnoreCase` function compares two input strings `str1` and `str2` character by character,
 * ignoring case, and returns TRUE if they are equal, and FALSE otherwise.
 *
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return TRUE if the strings are equal, ignoring case; FALSE otherwise.
 */
bool strCmpIgnoreCase(const char *str1, const char *str2);

/**
 * @brief Allocates memory for a TSongInfos structure.
 *
 * The `allocateSongInfos` function allocates memory for a TSongInfos structure, initializes its fields,
 * and returns the resulting structure.
 *
 * @return The allocated TSongInfos structure.
 */
TSongInfos allocateSongInfos();

/**
 * @brief Sets the global variable `indexCount` based on the number of valid entries in the file.
 *
 * The `setIndexCount` function initializes `indexCount` to zero and then counts the number of valid
 * entries in the provided file, considering lines that are not empty or composed of only whitespaces.
 * It updates the global variable `indexCount` accordingly.
 *
 * @param file The file pointer to the song data file.
 */
void setIndexCount();


String setWorkingDirectoryToExecutablePath();

/**
 * @brief Compares two songs based on their names.
 *
 * The `compareSongsByName` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the alphabetical order of their names.
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return An integer less than, equal to, or greater than zero if the name of the first song is found,
 *         respectively, to be less than, equal to, or greater than the name of the second song.
 */
int compareSongsByName(const void *a, const void *b);

/**
 * @brief Compares two songs based on their albums.
 *
 * The `compareSongsByAlbum` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the alphabetical order of their albums.
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return An integer less than, equal to, or greater than zero if the album of the first song is found,
 *         respectively, to be less than, equal to, or greater than the album of the second song.
 */
int compareSongsByAlbum(const void *a, const void *b);

/**
 * @brief Compares two songs based on their artists.
 *
 * The `compareSongsByArtist` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the alphabetical order of their artists.
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return An integer less than, equal to, or greater than zero if the artist of the first song is found,
 *         respectively, to be less than, equal to, or greater than the artist of the second song.
 */
int compareSongsByArtist(const void *a, const void *b);

/**
 * @brief Compares two songs based on their year of publishing in descending order.
 *
 * The `compareSongsByYearOfPublishingNew2Old` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the publication year of the songs in descending order (new to old).
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return A positive integer if the publication year of the first song is less than that of the second song,
 *         0 if they are equal, and a negative integer if the publication year of the first song is greater than that of the second song.
 */
int compareSongsByYearOfPublishingNew2Old(const void *a, const void *b);

/**
 * @brief Compares two songs based on their year of publishing in ascending order.
 *
 * The `compareSongsByYearOfPublishingOld2New` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the publication year of the songs in ascending order (old to new).
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return A negative integer if the publication year of the first song is less than that of the second song,
 *         0 if they are equal, and a positive integer if the publication year of the first song is greater than that of the second song.
 */
int compareSongsByYearOfPublishingOld2New(const void *a, const void *b);

/**
 * @brief Compares two songs based on their rating in descending order.
 *
 * The `compareSongsWorse2Best` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the rating of the songs in descending order (worse to best).
 * If the ratings are the same, it sorts by the index in ascending order.
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return A positive integer if the rating of the first song is less than that of the second song,
 *         0 if they have the same rating (sorts by index in ascending order in this case),
 *         and a negative integer if the rating of the first song is greater than that of the second song.
 */
int compareSongsWorse2Best(const void *a, const void *b);

/**
 * @brief Compares two songs based on their rating in ascending order.
 *
 * The `compareSongsBest2Worse` function is a comparator function intended for use with the `qsort` function
 * to sort an array of `TSongInfos` structures based on the rating of the songs in ascending order (best to worse).
 * If the ratings are the same, it sorts by the index in ascending order.
 *
 * @param a Pointer to the first song (`TSongInfos` structure).
 * @param b Pointer to the second song (`TSongInfos` structure).
 * @return A positive integer if the rating of the first song is greater than that of the second song,
 *         0 if they have the same rating (sorts by index in ascending order in this case),
 *         and a negative integer if the rating of the first song is less than that of the second song.
 */
int compareSongsBest2Worse(const void *a, const void *b);

/**
 * @brief Frees the dynamically allocated memory of a `TSongInfos` structure.
 *
 * The `freeSongInfos` function deallocates the memory occupied by the dynamic strings
 * (name, album, artist, and genre) within a `TSongInfos` structure.
 *
 * @param songInfos The `TSongInfos` structure to be freed.
 */
void freeSongInfos(const TSongInfos songInfos);


/**
 * @brief Returns the maximum of two integers.
 *
 * The `max` function compares two integers and returns the greater of the two.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of the two integers.
 */
 /*
int max(const int a, const int b);
*/

/**
 * @brief Frees allocated memory and performs cleanup before program exit.
 *
 * The `exitHandler` function is responsible for freeing the dynamically allocated
 * memory used for the full file path. It is intended to be used as an exit handler
 * in the program to ensure proper cleanup before program termination.
 */
void exitHandler();

#endif //SONGS_H

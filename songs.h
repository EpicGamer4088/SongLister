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
    String musicFileName;
    Boolean musicFile;
}
TSongInfos;

/**
 * @brief Entry point for the main function.
 *
 * The `Main` function serves as the entry point for the program. It sets up signal
 * handlers for SIGINT (Ctrl+C) and SIGTERM (exit by the X in the top right), allocates
 * memory for `fullSongListFilePath`, initializes a file pointer (`file`), and declares a Boolean
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
 * song data, a Boolean `songFileLoaded` indicating whether the song file is loaded,
 * and a constant `TSongInfos` structure `songInfos` representing song information.
 * It presents a menu to the user, allowing them to perform various actions related
 * to song data. The function continuously runs until the user chooses to exit.
 *
 * @param file The file pointer for song data.
 * @param songFileLoaded A Boolean indicating whether the song file is loaded.
 * @param songInfos A constant structure representing song information.
 */
void MainMenu();

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

/**
 * @brief Prints the menu options for music-related actions.
 *
 * The `printMusicOptions` function displays a menu with options for managing music files.
 * It highlights the option specified by the `selectedOption` parameter using ">>". The menu
 * includes options to add, remove, and change music files for a song, play a song, and go back
 * to the main menu.
 *
 * @param selectedOption The user's selected option (1 to 5).
 */
void printMusicOptions(const int selectedOption);

/**
 * @brief Prints the menu options for changing user data paths.
 *
 * The `printChangeUserDataOptions` function displays a menu with options for changing paths
 * related to user data. It highlights the option specified by the `selectedOption` parameter
 * using ">>". The menu includes options to change the path of the SongList file, change the
 * path of the music folder, and go back to the main menu.
 *
 * @param selectedOption The user's selected option (1 to 3).
 */
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
 * @brief Opens a file dialog for selecting media files (MP3 or MP4).
 *
 * The `openMusicFileDialog` function displays a file dialog that allows the user to select a media file,
 * specifically supporting MP3 and MP4 formats. If the user selects a file, the function returns the full path
 * of the selected file. If no file is selected or an error occurs, the function returns NULL.
 *
 * @return A string containing the full path of the selected media file, or NULL if no file is selected.
 */
String openMusicFileDialog();

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

/**
 * @brief Copies and renames a music file.
 *
 * The `copyAndRenameMusicFile` function copies a music file from the source path to the specified destination
 * folder with a new file name. It dynamically allocates memory for the destination path and uses the Windows API
 * function `CopyFile` to perform the file copy. If an error occurs during the copy operation, an error message is
 * printed along with the error code. The allocated memory for the destination path is freed after the copy operation.
 *
 * @param srcPath      A string containing the full path of the source music file.
 * @param destFolder   A string containing the full path of the destination folder.
 * @param newFileName  A string containing the new file name for the copied music file.
 */
void copyAndRenameMusicFile(const char* srcPath, const char* destFolder, const char* newFileName);

/**
 * @brief Checks and handles the user data file.
 *
 * The `checkAndHandleUserDataFile` function checks if the user data file exists. If the file does not exist,
 * it creates the file, sets user data using `setUserData`, writes user data into the file, and then closes the file.
 * If the file already exists, it reads user data from the file using `readUserDataFromUserDataFile` and then closes
 * the file. The full path of the user data file is determined by merging the executable path with the user data file name.
 */
void checkAndHandleUserDataFile();

/**
 * @brief Checks and handles the music file folder.
 *
 * The `checkAndHandleMusicFileFolder` function checks if the music file folder already exists. If the folder does not
 * exist, it creates the folder using `CreateDirectoryA`. The full path of the music file folder is determined by the
 * `fullMusicFolderFilePath`. If the folder creation is unsuccessful, an error message is printed.
 */
void checkAndHandleMusicFileFolder();

/**
 * @brief Sets user data related to song list and music folder paths.
 *
 * The `setUserData` function prompts the user to select a CSV file for the song list using `openCSVFileDialog`.
 * It also prompts the user to select a folder for the music files using `openFolderDialog`. The selected paths
 * are stored in the global variables `fullSongListFilePath` and `fullMusicFolderFilePath`.
 */
void setUserData();

/**
 * @brief Writes user data into the user data file.
 *
 * The `writeUserDataIntoUserDataFile` function opens the user data file and writes the full paths
 * of the song list and music folder into the file. If an error occurs when opening the file, an error
 * message is printed, and the program exits with an error code.
 */
void writeUserDataIntoUserDataFile();

/**
 * @brief Reads user data from the user data file.
 *
 * The `readUserDataFromUserDataFile` function reads the user data file and extracts the full paths
 * of the song list and music folder. The extracted paths are stored in the global variables
 * `fullSongListFilePath` and `fullMusicFolderFilePath`.
 */
void readUserDataFromUserDataFile();

/**
 * @brief Updates user data through an interactive menu.
 *
 * The `updateUserData` function presents an interactive menu allowing the user to choose between updating
 * the song list file path, updating the music folder path, or returning to the main menu. The user's selection
 * is continuously monitored using arrow keys, and the chosen option is executed when the Enter key is pressed.
 * This function is part of an iterative process, and it calls itself recursively based on the user's selections.
 */
void updateUserData();

/**
 * @brief Updates the song list file path in the user data file.
 *
 * The `updateSongListFilePathInUserDataFile` function prompts the user to select a new CSV file for the song list
 * using `openCSVFileDialog`. The selected path is then stored in the global variable `fullSongListFilePath`, and the
 * updated user data is written into the user data file using `writeUserDataIntoUserDataFile`. A success message is
 * displayed, and the program pauses before returning.
 */
void updateSongListFilePathInUserDataFile();

/**
 * @brief Updates the music folder path in the user data file.
 *
 * The `updateMusicFolderPathInUserDataFile` function prompts the user to select a new folder for the music files
 * using `openFolderDialog`. The selected path is then stored in the global variable `fullMusicFolderFilePath`, and the
 * updated user data is written into the user data file using `writeUserDataIntoUserDataFile`. A success message is
 * displayed, and the program pauses before returning.
 */
void updateMusicFolderPathInUserDataFile();

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

/**
 * @brief Adds a music file for a specific song entry.
 *
 * The `addMusicFile` function allows the user to associate a music file with an existing song entry.
 * It prompts the user to enter the name of the song and checks if it exists in the song list. If the
 * song exists, it constructs a unique file name for the music file based on the artist and song name.
 * If the song already has a valid music file, the user is informed, and the function returns to the
 * music menu. If the song doesn't have a valid music file, the user is prompted to select a music file,
 * which is then copied to the music folder and associated with the song in the song list. The function
 * updates the song list file with the new information and displays a success message before returning
 * to the music menu.
 */
void addMusicFile();

/**
 * @brief Adds a music file for a new song entry.
 *
 * The `addMusicFileForNewSong` function facilitates the process of adding a music file for a new song
 * entry. It prompts the user to select a music file, then constructs a unique file name for the music file
 * based on the artist and song name provided in the `songInfos` parameter. The function copies and renames
 * the selected music file to the music folder, updates the song file name, and displays a success message.
 * The final file name is returned, allowing further use if needed.
 *
 * @param songInfos The song information structure containing details about the new song.
 * @return A string containing the final file name of the added music file.
 */
String addMusicFileForNewSong(const TSongInfos songInfos);


void removeMusicFile();


void changeMusicFile();


void playMusic();

/**
 * @brief Displays the music menu and handles user interaction.
 *
 * The `displayMusicMenu` function presents the user with a menu of music-related options, such as adding,
 * removing, changing, or playing music files. It continuously listens for user input and responds accordingly.
 * The selected option triggers the corresponding function, and the menu is displayed until the user exits
 * or selects the appropriate action.
 */
void displayMusicMenu();

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
 * @brief Compares two strings for equality, ignoring case.
 *
 * The `strCmpIgnoreCase` function compares two input strings `str1` and `str2` character by character,
 * ignoring case, and returns TRUE if they are equal, and FALSE otherwise.
 *
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return TRUE if the strings are equal, ignoring case; FALSE otherwise.
 */
Boolean strCmpIgnoreCase(const char *str1, const char *str2);

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

/**
 * @brief Retrieves the full path of the executable's directory.
 *
 * The `getExecutablePath` function dynamically allocates memory to store the full path of the directory
 * where the executable is located. It uses the `GetModuleFileName` function to obtain the full path
 * and then removes the filename to keep only the directory. The allocated buffer containing the path
 * is returned, and the caller is responsible for freeing the memory.
 *
 * @return A dynamically allocated string containing the full path of the executable's directory,
 *         or NULL in case of memory allocation failure or if the path retrieval fails.
 */
String getExecutablePath();

/**
 * @brief Checks if a file exists at the specified full path.
 *
 * The `fileExists` function attempts to open the file at the given `fullFilePath` in binary mode.
 * If the file can be opened, it is assumed to exist, and the function returns TRUE. Otherwise, it
 * returns FALSE. The caller is responsible for providing a valid full file path.
 *
 * @param fullFilePath A string containing the full path of the file to check for existence.
 * @return TRUE if the file exists, FALSE otherwise.
 */
Boolean fileExists(const String fullFilePath);

/**
 * @brief Converts spaces and specified special characters in a string to underscores.
 *
 * The `convertSpacesAndSpecialCharsToUnderscores` function iterates through each character in the
 * provided string (`str`) and replaces spaces, forward slashes, backslashes, and pipe characters with underscores.
 * The function modifies the input string in place.
 *
 * @param str A pointer to the null-terminated string to be modified.
 */
void convertSpacesAndSpecialCharsToUnderscores(char* str);

/**
 * @brief Converts all characters in a string to lowercase.
 *
 * The `convertToLowerCase` function iterates through each character in the provided string (`str`)
 * and converts it to lowercase using the `tolower` function. The function modifies the input string in place.
 *
 * @param str A pointer to the null-terminated string to be converted to lowercase.
 */
void convertToLowerCase(char* str);

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
 * @brief Frees allocated memory and performs cleanup before program exit.
 *
 * The `exitHandler` function is responsible for freeing the dynamically allocated
 * memory used for the full file path. It is intended to be used as an exit handler
 * in the program to ensure proper cleanup before program termination.
 */
void exitHandler();

#endif //SONGS_H

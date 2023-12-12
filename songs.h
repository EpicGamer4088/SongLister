#ifndef SONGS_H
#define SONGS_H

#include <stdio.h>

/**
 * @brief Maximum length for strings in the program.
 *
 * This line defines the constant MAX_STR_LEN with a value of 255, representing the
 * maximum length for strings in the program. It is commonly used to define the size
 * of character arrays to avoid hardcoding values and enhance code maintainability.
 *
 * @note Assumes that this constant is used consistently in the program for defining
 * string lengths.
 */
#define MAX_STR_LEN 255

/**
 * @brief File name for the user data file.
 *
 * This line defines the constant USERDATA_FILE_NAME with the value "/userdata.bin",
 * representing the file name for the user data file. It is commonly used to reference
 * file names in the program and provides a centralized location for file-related names.
 *
 * @note Assumes that this constant is used as the user data file name in the program.
 */
#define USERDATA_FILE_NAME "/userdata.bin"

/**
 * @brief Definition of the String type as a character pointer.
 *
 * This line defines the String type as a synonym for a character pointer (char *).
 * It is commonly used to improve code readability and provide a more descriptive
 * name for character arrays or strings in C.
 *
 * @note Assumes that the char type is available in the program.
 *
 * @see char
 */
typedef char *String;

/**
 * @brief External declaration of the index count variable.
 *
 * This line declares an external integer variable named indexCount, which
 * is defined elsewhere in the program. It is commonly used when a variable is
 * defined in a different source file, and its declaration is needed in the current
 * source file to inform the compiler about its existence and type.
 *
 * @note Assumes that the int type is declared and defined elsewhere in the program,
 * and this declaration allows the use of indexCount in the current source file.
 *
 * @see int
 */
extern int indexCount;

/**
 * @brief External declaration of the full song list file path.
 *
 * This line declares an external String variable named fullSongListFilePath, which
 * is defined elsewhere in the program. It is commonly used when a variable is defined
 * in a different source file, and its declaration is needed in the current source file
 * to inform the compiler about its existence and type.
 *
 * @note Assumes that the String type is declared and defined elsewhere in the program,
 * and this declaration allows the use of fullSongListFilePath in the current source file.
 *
 * @see String
 */
extern String fullSongListFilePath;

/**
 * @brief External declaration of the full music folder file path.
 *
 * This line declares an external String variable named fullMusicFolderFilePath, which
 * is defined elsewhere in the program. It is commonly used when a variable is defined
 * in a different source file, and its declaration is needed in the current source file
 * to inform the compiler about its existence and type.
 *
 * @note Assumes that the String type is declared and defined elsewhere in the program,
 * and this declaration allows the use of fullMusicFolderFilePath in the current source file.
 *
 * @see String
 */
extern String fullMusicFolderFilePath;

/**
 * @brief External declaration of the full user data file path.
 *
 * This line declares an external String variable named fullUserDataFilePath, which
 * is defined elsewhere in the program. It is commonly used when a variable is defined
 * in a different source file, and its declaration is needed in the current source file
 * to inform the compiler about its existence and type.
 *
 * @note Assumes that the String type is declared and defined elsewhere in the program,
 * and this declaration allows the use of fullUserDataFilePath in the current source file.
 *
 * @see String
 */
extern String fullUserDataFilePath;

/**
 * @brief Enumeration representing boolean values.
 *
 * This enumeration, named Boolean, defines two constant values: FALSE and TRUE,
 * representing boolean values in C. It is commonly used to improve code readability
 * by providing more expressive names for true and false values.
 *
 * @note Assumes that the enumeration is used in contexts where Boolean values are
 * needed, and TRUE is considered equivalent to a non-zero value, while FALSE is zero.
 *
 * @see None
 */
typedef enum Boolean
{
    FALSE, ///< Represents the boolean value false.
    TRUE   ///< Represents the boolean value true.
}
        Boolean;


/**
 * @brief Structure representing information about a song.
 *
 * This structure, named TSongInfos, encapsulates details about a song, including its name,
 * album, artist, genre, year of publishing, rating, music file name, and a flag indicating
 * whether a music file is associated with the song. The String type is assumed to be a
 * character array, and Boolean is used for representing true/false values. The structure is
 * designed to hold dynamic strings for various fields, and it is typically used to manage
 * information about songs in a music-related application.
 *
 * @note Assumes the availability of the String type, Boolean type, and standard short
 * integer type. The structure is expected to be used in conjunction with functions and
 * operations related to managing and manipulating song information.
 *
 * @see String, Boolean
 */
typedef struct SongInfos
{
    String name;          ///< Name of the song.
    String album;         ///< Album of the song.
    String artist;        ///< Artist of the song.
    String genre;         ///< Genre of the song.
    short yearPublished;  ///< Year the song was published.
    short rating;         ///< Rating assigned to the song.
    String musicFileName; ///< File name of the associated music file.
    Boolean musicFile;    ///< Flag indicating whether a music file is associated with the song.
}
        TSongInfos;

/**
 * @brief Main function for the program.
 *
 * This function serves as the entry point for the program. It initializes signal handlers for
 * SIGINT (Ctrl+C) and SIGTERM (termination signal). Memory is allocated for file path strings
 * (fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath). It checks and handles
 * the existence and content of the user data file and the music file folder. The index count
 * is set based on the number of entries in the user data file. It further checks the validity
 * of all music file entries. Finally, the program enters the main menu to start the user interface.
 *
 * @warning Ensure proper memory deallocation after program execution.
 */
void Main();

/**
 * @brief Displays and manages the main menu of the program.
 *
 * This function presents a menu interface to the user, allowing them to navigate through different
 * options. The options are displayed on the console, and the user can navigate using arrow keys (up and
 * down) or by pressing the Enter key to select an option. The menu is continuously displayed until the
 * user selects the 'Exit' option.
 *
 * The function uses the system("cls") command to clear the console screen, providing a clean interface.
 * Arrow key input is detected to navigate through menu options. Upon pressing Enter, the selected option
 * is executed. The function then enters a loop that repeats until the user selects the 'Exit' option.
 *
 * The switch statement handles the selected option, calling the corresponding functions such as addNewSong(),
 * removeSong(), changeSongInformations(), displayListedSongs(), displayMusicMenu(), and updateUserData().
 * After executing the selected option, the MainMenu() function is called recursively to display the menu again.
 *
 * @note The use of system("cls") is platform-dependent and may need adjustment for different operating systems.
 * @note The function operates with a loop that continues until the user selects the 'Exit' option (case 7).
 * @note Recursive calls to MainMenu() are used to keep presenting the menu after executing an option.
 *
 * @see addNewSong, removeSong, changeSongInformations, displayListedSongs, displayMusicMenu, updateUserData, exitProgramm
 */
void MainMenu();

/**
 * @brief Checks the validity of all music file entries in the user data file.
 *
 * This function performs a series of checks on the music file entries stored in the user data file.
 * It allocates memory for temporary storage, reads the entries, and verifies their integrity.
 * The checks include validating file paths, handling memory allocation errors, and updating the user
 * data file accordingly. The function also ensures that the music file entries' filenames match the
 * expected format and are present in the music folder.
 *
 * @note Memory allocation for song information is performed for each song entry in a nested loop.
 * @note The function updates the user data file to maintain consistency with the music folder.
 * @note Checks for the existence of music files and ensures filenames match the expected format.
 * @note Assumes the existence of helper functions such as allocateSongInfos, freeSongInfos, mergeStr,
 *       convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase, fileExists, and strCmpIgnoreCase.
 * @note Exits the program with an error message if memory allocation or file operations encounter issues.
 *
 * @see allocateSongInfos, freeSongInfos, mergeStr, convertSpacesAndSpecialCharsToUnderscores,
 *      convertToLowerCase, fileExists, strCmpIgnoreCase
 */
void checkIfAllMusicFileEntriesAreValid();

/**
 * @brief Prints the title screen of the program to the console.
 *
 * This function displays a simple ASCII art title screen for the Song Rater program.
 * The title is enclosed in a box for aesthetic presentation. It uses the printf function
 * to output the formatted title screen to the console.
 *
 * @note This function assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printTitleScreen();

/**
 * @brief Prints the title screen for the Song Lister program.
 *
 * This function displays a simple ASCII art title screen for the Song Lister program.
 * The title is enclosed in a box for aesthetic presentation. It uses the printf function
 * to output the formatted title screen to the console.
 *
 * @note This function assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printListOptionsTitleScreen();

/**
 * @brief Prints the screen for playing music, displaying song information and controls.
 *
 * This function formats and prints a screen for playing music, showing details such as
 * the song name, album, and artist. Additionally, it provides information about the controls
 * for playback, including options to pause/restart and stop playback. The layout is presented
 * in a simple ASCII art box for aesthetic presentation.
 *
 * @param songs The structure containing information about the currently playing song.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printPlayMusicScreen(TSongInfos songs);

/**
 * @brief Prints the menu options with highlighting for the selected option.
 *
 * This function displays the menu options with a visual indicator (">>") to highlight
 * the currently selected option. The menu includes choices for adding a new song, deleting
 * a song, changing song information, listing songs, accessing the music menu, changing user data,
 * and exiting the program. The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printMenuOptions(const int selectedOption);

/**
 * @brief Prints the list options menu with highlighting for the selected option.
 *
 * This function displays the list options menu with a visual indicator (">>") to highlight
 * the currently selected option. The menu includes choices for listing all songs, listing sorted songs,
 * listing songs with valid music files, and returning to the main menu. The selected option is emphasized
 * using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printListOptions(const int selectedOption);

/**
 * @brief Prints the music options menu with highlighting for the selected option.
 *
 * This function displays the music options menu with a visual indicator (">>") to highlight
 * the currently selected option. The menu includes choices for adding a music file for a song,
 * removing a music file for a song, changing the music file for a song, listing all songs with
 * valid music files, playing a song, and returning to the main menu. The selected option is
 * emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printMusicOptions(const int selectedOption);

/**
 * @brief Prints the change user data options menu with highlighting for the selected option.
 *
 * This function displays the change user data options menu with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for changing the SongList
 * file path, changing the music folder path, and returning to the main menu. The selected option
 * is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printChangeUserDataOptions(const int selectedOption);

/**
 * @brief Prints the sorted list options menu with highlighting for the selected option.
 *
 * This function displays the sorted list options menu with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs
 * sorted by name, album, artist, genre, year of publishing, rating, and returning one step back.
 * The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by name with highlighting for the selected option.
 *
 * This function displays the options for sorting the list by name with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs by name
 * in ascending order, listing information from a given song, and returning one step back.
 * The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByNameOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by album with highlighting for the selected option.
 *
 * This function displays the options for sorting the list by album with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs by album
 * in ascending order, listing every entry from a given album, and returning one step back.
 * The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByAlbumOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by artist with highlighting for the selected option.
 *
 * This function displays the options for sorting the list by artist with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs by artist
 * in ascending order, listing every entry from a given artist, and returning one step back.
 * The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByArtistOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by year of publishing with highlighting for the selected option.
 *
 * This function displays the options for sorting the list by year of publishing with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs from newest to oldest,
 * from oldest to newest, newer than a given year, older than a given year, every entry from a given year of
 * publishing, and returning one step back. The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByYearOfPublishingOptions(const int selectedOption);

/**
 * @brief Prints the options for sorting the list by rating with highlighting for the selected option.
 *
 * This function displays the options for sorting the list by rating with a visual indicator (">>")
 * to highlight the currently selected option. The menu includes choices for listing songs from best
 * to worst, from worst to best, every entry from a given rating, and returning one step back.
 * The selected option is emphasized using the visual indicator.
 *
 * @param selectedOption The index of the currently selected menu option.
 *
 * @note Assumes the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByRatingOptions(const int selectedOption);

/**
 * @brief Opens a file dialog to select a CSV file and returns the selected file path.
 *
 * This function opens a file dialog allowing the user to select a CSV file. The selected file path
 * is stored in a static character array and returned as a String. If the user cancels the operation
 * or encounters an error, the function returns NULL.
 *
 * @return A String containing the selected CSV file path, or NULL if the operation is canceled or encounters an error.
 *
 * @note Assumes the availability of the Windows API and the GetOpenFileName function.
 *
 * @see OPENFILENAME, GetOpenFileName
 */
String openCSVFileDialog();

/**
 * @brief Opens a file dialog to select a music file and returns the selected file path.
 *
 * This function opens a file dialog allowing the user to select a music file, specifically in the WAV format.
 * The selected file path is stored in a static character array and returned as a String. If the user cancels
 * the operation or encounters an error, the function returns NULL.
 *
 * @return A String containing the selected music file path, or NULL if the operation is canceled or encounters an error.
 *
 * @note Assumes the availability of the Windows API and the GetOpenFileName function.
 *
 * @see OPENFILENAME, GetOpenFileName
 */
String openMusicFileDialog();

/**
 * @brief Opens a folder dialog to select a folder and returns the selected folder path.
 *
 * This function opens a folder dialog allowing the user to select a folder. The selected folder path
 * is stored in a static character array and returned as a String. If the user cancels the operation or
 * encounters an error, the function returns NULL.
 *
 * @return A String containing the selected folder path, or NULL if the operation is canceled or encounters an error.
 *
 * @note Assumes the availability of the Windows API and the SHBrowseForFolder and SHGetPathFromIDList functions.
 *
 * @see BROWSEINFO, SHBrowseForFolder, SHGetPathFromIDList
 */
String openFolderDialog();

/**
 * @brief Copies and renames a music file from the source path to the destination folder with a new file name.
 *
 * This function takes the source path of a music file, a destination folder, and a new file name. It combines
 * the destination folder and the new file name to create the full destination path, then copies the file from
 * the source path to the destination path. If the copy operation encounters an error, an error message with the
 * error code is printed to the console.
 *
 * @param srcPath The source path of the music file to be copied.
 * @param destFolder The destination folder where the file will be copied.
 * @param newFileName The new file name for the copied file.
 *
 * @note Assumes the availability of the Windows API and the CopyFile and GetLastError functions.
 *
 * @see snprintf, CopyFile, GetLastError
 */
void copyAndRenameMusicFile(const String srcPath, const String destFolder, const String newFileName);

/**
 * @brief Removes a music file from the music folder.
 *
 * This function attempts to remove a music file specified by its file path. If the removal operation
 * encounters an error, an error message with the error code is printed to the console.
 *
 * @param filePath The file path of the music file to be removed.
 *
 * @note Assumes the availability of the Windows API and the remove and GetLastError functions.
 *
 * @see remove, GetLastError
 */
void removeMusicFileFromMusicFolder(const String filePath);

/**
 * @brief Checks and handles the existence of the user data file.
 *
 * This function checks if the user data file exists. If the file does not exist, it creates the file and
 * writes default user data into it. If the file already exists, it reads user data from the file.
 *
 * @note Assumes the availability of the file-related functions (fopen, fclose) and the user data handling functions.
 *
 * @see getExecutablePath, mergeStr, fopen, setUserData, writeUserDataIntoUserDataFile, readUserDataFromUserDataFile
 */
void checkAndHandleUserDataFile();

/**
 * @brief Checks and handles the existence of the music file folder.
 *
 * This function checks if the music file folder exists. If the folder does not exist, it creates the folder.
 *
 * @note Assumes the availability of the Windows API, specifically the PathFileExistsA and CreateDirectoryA functions.
 *
 * @see PathFileExistsA, CreateDirectoryA
 */
void checkAndHandleMusicFileFolder();

/**
 * @brief Sets user data by prompting the user to select a song list file and a music folder.
 *
 * This function sets the user data by using file dialogs to prompt the user to select a song list file
 * and a music folder. The selected file paths are stored in global variables for later use.
 *
 * @note Assumes the availability of the file dialog functions (openCSVFileDialog, openFolderDialog).
 *
 * @see openCSVFileDialog, openFolderDialog
 */
void setUserData();

/**
 * @brief Writes user data into the user data file in binary mode.
 *
 * This function opens the user data file in binary mode and writes the full song list file path and
 * the full music folder path into the file. The data is written using the fwrite function. If an error
 * occurs during the file opening or writing process, an error message is printed to the console.
 *
 * @note Assumes the availability of the file-related functions (fopen, fclose, fwrite) and global variables
 * (fullSongListFilePath, fullMusicFolderFilePath).
 *
 * @see fopen, fclose, fwrite
 */
void writeUserDataIntoUserDataFile();

/**
 * @brief Reads user data from the user data file in binary mode.
 *
 * This function opens the user data file in binary mode and reads the full song list file path and
 * the full music folder path from the file. The data is read using the fread function. If an error
 * occurs during the file opening or reading process, an error message is printed to the console.
 *
 * @note Assumes the availability of the file-related functions (fopen, fclose, fread) and global variables
 * (fullSongListFilePath, fullMusicFolderFilePath).
 *
 * @see fopen, fclose, fread
 */
void readUserDataFromUserDataFile();

/**
 * @brief Updates user data by providing options to change the song list file path or music folder path.
 *
 * This function displays a menu allowing the user to choose between updating the song list file path,
 * updating the music folder path, or returning to the main menu. The user's selection determines the
 * action to be taken.
 *
 * @note Assumes the availability of the console-related functions (system, getch), UI-related functions
 * (printTitleScreen, printChangeUserDataOptions), and other functions for updating specific user data.
 *
 * @see system, getch, printTitleScreen, printChangeUserDataOptions, updateSongListFilePathInUserDataFile,
 * updateMusicFolderPathInUserDataFile, MainMenu
 */
void updateUserData();

/**
 * @brief Updates the song list file path in the user data file.
 *
 * This function prompts the user to select a new song list file path using a file dialog.
 * The selected path is then updated in the user data file, and a success message is displayed.
 *
 * @note Assumes the availability of the console-related functions (system), UI-related functions,
 * file dialog function (openCSVFileDialog), and user data writing function (writeUserDataIntoUserDataFile).
 *
 * @see system, openCSVFileDialog, writeUserDataIntoUserDataFile
 */
void updateSongListFilePathInUserDataFile();

/**
 * @brief Updates the music folder path in the user data file.
 *
 * This function prompts the user to select a new music folder path using a folder dialog.
 * The selected path is then updated in the user data file, and a success message is displayed.
 *
 * @note Assumes the availability of the console-related functions (system), UI-related functions,
 * folder dialog function (openFolderDialog), and user data writing function (writeUserDataIntoUserDataFile).
 *
 * @see system, openFolderDialog, writeUserDataIntoUserDataFile
 */
void updateMusicFolderPathInUserDataFile();

/**
 * @brief Inputs information for a new song.
 *
 * This function allocates memory for a new song, prompts the user to input various information such as
 * name, album, artist, genre, year published, and rating. It also provides an option to add a music file
 * for the song. The input is validated, and the song information is returned.
 *
 * @note Assumes the availability of the console-related functions (printf, fgets, scanf, getchar, fflush),
 * memory allocation functions (allocateSongInfos), string manipulation functions (charReplace),
 * and other utility functions (addMusicFileForNewSong).
 *
 * @return TSongInfos The structure containing the input song information.
 *
 * @see printf, fgets, scanf, getchar, fflush, allocateSongInfos, charReplace, addMusicFileForNewSong
 */
TSongInfos inputSongInfos();

/**
 * @brief Adds a new song to the song list.
 *
 * This function opens the song list file in append mode, gets the input for a new song using the
 * inputSongInfos function, and appends the song information to the end of the file. The function
 * updates the index count accordingly and displays a success message.
 *
 * @note Assumes the availability of the console-related functions (system, printf, usleep),
 * file-related functions (fopen, fseek, ftell, fgetc, fprintf, fclose), memory-related functions (malloc),
 * input function (inputSongInfos), utility functions (freeSongInfos), and other system-related functions (exit).
 *
 * @see system, printf, usleep, fopen, fseek, ftell, fgetc, fprintf, fclose, malloc, inputSongInfos, freeSongInfos, exit
 */
void addNewSong();

/**
 * @brief Removes a song from the song list.
 *
 * This function opens the song list file in read mode, reads the existing songs, prompts the user to
 * enter the name of the song to be removed, checks if the entered song exists, opens the song list file
 * in write mode, skips the entry to be deleted, and writes the updated song list back to the file.
 * The function also removes the associated music file from the music folder. The memory allocated for
 * songs is released after use, and the indexCount is updated accordingly.
 *
 * @note Assumes the availability of the console-related functions (system, printf, usleep), file-related
 * functions (fopen, fscanf, fclose), memory-related functions (malloc), string-related functions (fgets,
 * charReplace, strCmpIgnoreCase, mergeStr), input function (removeMusicFileFromMusicFolder), utility functions
 * (freeSongInfos), and other system-related functions (exit, MainMenu).
 *
 * @see system, printf, usleep, fopen, fscanf, fclose, malloc, fgets, charReplace, strCmpIgnoreCase, mergeStr,
 * removeMusicFileFromMusicFolder, freeSongInfos, exit, MainMenu
 */
void removeSong();

/**
 * @brief Changes the information of a song in the song list.
 *
 * This function opens the song list file in read mode, reads the existing songs, prompts the user to
 * enter the name of the song to be changed, checks if the entered song exists, opens the song list file
 * in write mode, skips the entry to be changed, writes the updated information for the given entry, and
 * writes the rest of the song list back to the file. The function also allocates and deallocates memory
 * dynamically, and it uses the inputSongInfos and other utility functions.
 *
 * @note Assumes the availability of the console-related functions (system, printf, usleep), file-related
 * functions (fopen, fscanf, fclose), memory-related functions (malloc), string-related functions (fgets,
 * charReplace, strCmpIgnoreCase, mergeStr), input function (inputSongInfos), utility functions (freeSongInfos),
 * and other system-related functions (exit, MainMenu).
 *
 * @see system, printf, usleep, fopen, fscanf, fclose, malloc, fgets, charReplace, strCmpIgnoreCase, mergeStr,
 * inputSongInfos, freeSongInfos, exit, MainMenu
 */
void changeSongInformations();

/**
 * @brief Adds a music file to an existing song in the song list.
 *
 * This function allows the user to add a music file to an existing song in the song list. It dynamically
 * allocates memory for various variables, including the song name, song file name, music file path, and
 * an array of song information structures. The function reads the existing song information from the song
 * list file, prompts the user to enter the name of the song they want to add a music file to, checks if
 * the song exists, generates a unique music file name, checks if the song already has a valid music file,
 * prompts the user to select a music file, copies and renames the selected music file to the music folder,
 * and updates the song list file with the new music file information. The function also handles errors,
 * such as memory allocation failures, file opening errors, and displays appropriate messages to the console.
 *
 * @note Assumes the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf,
 * fgets, fflush, charReplace, strCmpIgnoreCase, displayMusicMenu, generateMusicFileName, fileExists,
 * openMusicFileDialog, copyAndRenameMusicFile, freeSongInfos, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf, fgets, fflush, charReplace,
 * strCmpIgnoreCase, displayMusicMenu, generateMusicFileName, fileExists, openMusicFileDialog,
 * copyAndRenameMusicFile, freeSongInfos
 */
void addMusicFile();

/**
 * @brief Adds a music file for a new song.
 *
 * This function adds a music file for a new song by prompting the user to select a music file,
 * generating a unique music file name based on the provided song information, copying and renaming
 * the selected music file to the music folder, and returning the generated music file name. The
 * function dynamically allocates memory for the song file name and music file path. After the
 * successful addition of the music file, it displays a success message on the console and pauses
 * the system for user acknowledgment.
 *
 * @param songInfos The information of the new song for which a music file is to be added.
 *
 * @return The generated music file name for the new song.
 *
 * @note Assumes the availability of system, printf, usleep, malloc, free, fopen, fclose, perror,
 * exit, openMusicFileDialog, generateMusicFileName, copyAndRenameMusicFile, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, fopen, fclose, perror, exit, openMusicFileDialog,
 * generateMusicFileName, copyAndRenameMusicFile
 */
String addMusicFileForNewSong(const TSongInfos songInfos);

/**
 * @brief Removes the music file associated with a song from the song list.
 *
 * This function facilitates the removal of the music file associated with a song by first reading the
 * existing song information from the song list file, prompting the user to enter the name of the song
 * they want to remove the music file from, checking if the song exists, generating the corresponding
 * music file name, verifying if the song has a valid music file, removing the music file from the music
 * folder, updating the song list file with a placeholder value for the removed music file, and displaying
 * a success message on the console. The function dynamically allocates memory for various variables,
 * including the song name, song file name, music file path, and an array of song information structures.
 * Error handling is incorporated to manage memory allocation failures, file opening errors, and cases
 * where the specified song does not exist or does not have a valid music file.
 *
 * @note Assumes the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose,
 * fscanf, fgets, fflush, charReplace, strCmpIgnoreCase, displayMusicMenu, generateMusicFileName,
 * fileExists, removeMusicFileFromMusicFolder, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf, fgets, fflush, charReplace,
 * strCmpIgnoreCase, displayMusicMenu, generateMusicFileName, fileExists, removeMusicFileFromMusicFolder
 */
void removeMusicFile();

/**
 * @brief Changes the music file associated with a song in the song list.
 *
 * This function allows the user to change the music file associated with a song by first reading the
 * existing song information from the song list file, prompting the user to enter the name of the song
 * they want to change the music file for, checking if the song exists, generating a new unique music
 * file name based on the provided song information, verifying if the song has a valid existing music
 * file, removing the existing music file from the music folder, prompting the user to select a new
 * music file, copying and renaming the selected music file to the music folder, and updating the song
 * list file with the new music file information. The function dynamically allocates memory for various
 * variables, including the song name, song file name, music file path, and an array of song information
 * structures. Error handling is incorporated to manage memory allocation failures, file opening errors,
 * cases where the specified song does not exist, or does not have a valid music file.
 *
 * @note Assumes the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose,
 * fscanf, fgets, fflush, charReplace, strCmpIgnoreCase, displayMusicMenu, generateMusicFileName,
 * fileExists, removeMusicFileFromMusicFolder, convertSpacesAndSpecialCharsToUnderscores,
 * convertToLowerCase, openMusicFileDialog, copyAndRenameMusicFile, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf, fgets, fflush, charReplace,
 * strCmpIgnoreCase, displayMusicMenu, generateMusicFileName, fileExists, removeMusicFileFromMusicFolder,
 * convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase, openMusicFileDialog, copyAndRenameMusicFile
 */
void changeMusicFile();

/**
 * @brief Plays the music associated with a song.
 *
 * This function allows the user to play the music associated with a song by first reading the
 * existing song information from the song list file, prompting the user to enter the name of the song
 * they want to play the music for, checking if the song exists, checking if the song has a valid music file,
 * displaying the play music screen, and allowing the user to control the playback (pause, resume, or exit).
 * The function dynamically allocates memory for various variables, including the song name, song file name,
 * music file path, and an array of song information structures. Error handling is incorporated to manage
 * memory allocation failures, file opening errors, cases where the specified song does not exist, or does
 * not have a valid music file.
 *
 * @note Assumes the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf,
 * fgets, fflush, charReplace, strCmpIgnoreCase, displayMusicMenu, printPlayMusicScreen, playWaveFile,
 * pauseResumePlayback, getch, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf, fgets, fflush, charReplace,
 * strCmpIgnoreCase, displayMusicMenu, printPlayMusicScreen, playWaveFile, pauseResumePlayback, getch
 */
void playMusic();

/**
 * @brief Plays a wave file asynchronously.
 *
 * This function sets the playback status to playing and uses the Windows API PlaySound function
 * to play the specified wave file asynchronously.
 *
 * @param fullMusicFilePath Full path to the wave file to be played.
 * @param isPlaying Pointer to a Boolean flag indicating the playback status.
 *
 * @note Assumes the availability of PlaySound and SND_ASYNC.
 *
 * @see PlaySound, SND_ASYNC
 */
void playWaveFile(const char *fullMusicFilePath, Boolean *isPlaying);

/**
 * @brief Toggles between pausing and resuming the playback of a wave file.
 *
 * This function checks the current playback status indicated by the isPlaying flag.
 * If the playback is in progress, it pauses the playback by setting isPlaying to FALSE
 * and purging the sound. If the playback is paused or stopped, it resumes playback
 * by setting isPlaying to TRUE and calling the playWaveFile function.
 *
 * @param fullMusicFilePath Full path to the wave file being played.
 * @param isPlaying Pointer to a Boolean flag indicating the playback status.
 *
 * @note Assumes the availability of PlaySound, SND_PURGE, and playWaveFile function.
 *
 * @see PlaySound, SND_PURGE, playWaveFile
 */
void pauseResumePlayback(const char *fullMusicFilePath, Boolean *isPlaying);

/**
 * @brief Displays the music-related menu and handles user interactions.
 *
 * This function continuously displays the music menu, reads user input, and responds based on the selected option.
 * The menu includes options for adding, removing, changing, listing songs with valid music files, playing music,
 * and returning to the main menu. It uses arrow keys for navigation and the Enter key to select an option.
 * The selected option is then processed, and the corresponding action is performed. The menu is redisplayed until
 * the user chooses to return to the main menu.
 *
 * @note Assumes the availability of system, getch, printListOptionsTitleScreen, printMusicOptions, addMusicFile,
 * removeMusicFile, changeMusicFile, displayListedSongsWithValidMusicFile, playMusic, and MainMenu functions.
 *
 * @see system, getch, printListOptionsTitleScreen, printMusicOptions, addMusicFile, removeMusicFile, changeMusicFile,
 * displayListedSongsWithValidMusicFile, playMusic, MainMenu
 */
void displayMusicMenu();

/**
 * @brief Prints a formatted line for visual separation or boundary in a table-like display.
 *
 * This function prints a line with fixed-length segments, creating a visual separation or boundary.
 * It is commonly used in table-like displays to enhance readability and structure.
 */
void printPartingLine();

/**
 * @brief Prints the table header with column labels for a music information display.
 *
 * This function clears the console screen, prints a visual separation line, and then prints the column labels
 * for a table displaying music information, including Name, Album, Artist, Genre, Year, Rating, and Music File.
 * Another visual separation line is printed below the header for a structured appearance.
 *
 * @note Assumes the availability of system and printPartingLine functions.
 *
 * @see system, printPartingLine
 */
void printTableHeader();

/**
 * @brief Prints a formatted table row with music information.
 *
 * This function takes a TSongInfos structure representing a song and prints its attributes in a formatted
 * table row. The printed row includes columns for Name, Album, Artist, Genre, Year, Rating, and Music File.
 *
 * @param song The TSongInfos structure containing information about the song to be printed.
 */
void printTableRow(const TSongInfos song);

/**
 * @brief Displays options for listing songs and performs the selected action.
 *
 * This function prompts the user with options to list songs statically, list songs sorted, display songs
 * with valid music files, or return to the main menu. It interacts with the user to select different display
 * options and performs the corresponding actions based on the user's choice.
 *
 * @note Assumes the availability of system, getch, printListOptionsTitleScreen, printListOptions,
 * displayListedSongsStatic, displayListedSongsSorted, displayListedSongsWithValidMusicFile, and MainMenu functions.
 *
 * @see system, getch, printListOptionsTitleScreen, printListOptions,
 * displayListedSongsStatic, displayListedSongsSorted, displayListedSongsWithValidMusicFile, MainMenu
 */
void displayListedSongs();

/**
 * @brief Displays a static list of songs, including details like name, album, artist, genre, year, rating, and music file.
 *
 * This function allocates memory for song information, reads song details from a file, and prints a formatted table
 * displaying each song's information. It prints a header with column names and separates each song entry with a line.
 * After displaying the list, it releases allocated memory and pauses the program.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, and indexCount.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, indexCount
 */
void displayListedSongsStatic();

/**
 * @brief Displays a list of songs with valid music files, including details like name, album, artist, genre, year, rating, and music file.
 *
 * This function allocates memory for song information, reads song details from a file, and prints a formatted table
 * displaying each song's information. It filters songs that have a valid music file, excluding those with "none" as the music file.
 * It prints a header with column names and separates each song entry with a line. After displaying the list, it releases
 * allocated memory and pauses the program.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, and indexCount.
 * @note Assumes the availability of strCmpIgnoreCase.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, strCmpIgnoreCase, indexCount
 */
void displayListedSongsWithValidMusicFile();

/**
 * @brief Displays a sorted list of songs based on user-selected criteria, allowing sorting by name, album, artist, genre, year, or rating.
 *
 * This function presents a menu to the user for selecting the sorting criteria, and then displays the list of songs
 * accordingly. It continuously prompts the user until they choose to exit. The available sorting options include sorting
 * by name, album, artist, genre, year of publishing, and rating. After displaying the sorted list, it redirects to the main
 * menu or other relevant functions based on user choice.
 *
 * @note Assumes the availability of system, printListOptionsTitleScreen, printSortedListOptions, getch,
 *       displayListedSongsSortedByName, displayListedSongsSortedByAlbum, displayListedSongsSortedByArtist,
 *       displayListedSongsByGenre, displayListedSongsByYearOfPublishing, displayListedSongsByRating, displayListedSongs.
 *
 * @see system, printListOptionsTitleScreen, printSortedListOptions, getch,
 *      displayListedSongsSortedByName, displayListedSongsSortedByAlbum, displayListedSongsSortedByArtist,
 *      displayListedSongsByGenre, displayListedSongsByYearOfPublishing, displayListedSongsByRating, displayListedSongs
 */
void displayListedSongsSorted();

/**
 * @brief Displays a menu for sorting songs by name, allowing options for alphabetical order or searching for a specific song.
 *
 * This function prompts the user to choose between sorting songs alphabetically or searching for a specific song by name.
 * It continuously prompts the user until they choose to exit. If sorting alphabetically, it redirects to the relevant sorting
 * function. If searching, it allows the user to input the song name and displays information for the matching song.
 * After completion, it redirects back to the main sorted list menu or other relevant functions based on user choice.
 *
 * @note Assumes the availability of system, printListOptionsTitleScreen, printSortedListByNameOptions, getch,
 *       displayListedSongsSortedByNameA2Z, displayListedSongInfosFromAGivenSong, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByNameOptions, getch,
 *      displayListedSongsSortedByNameA2Z, displayListedSongInfosFromAGivenSong, displayListedSongsSorted
 */
void displayListedSongsSortedByName();

/**
 * @brief Displays a sorted list of songs by name in alphabetical order (A-Z).
 *
 * This function reads the song information from the file, allocates memory for each song element, and then sorts the songs
 * alphabetically by name. It prints the sorted list to the console, including song details such as name, album, artist, genre,
 * year of publishing, rating, and music file. After displaying the sorted list, it releases the allocated memory and prompts
 * the user to continue by pressing any key.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
 *       freeSongInfos, compareSongsByName.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
 *      freeSongInfos, compareSongsByName
 */
void displayListedSongsSortedByNameA2Z();

/**
 * @brief Displays song information for a given song name entered by the user.
 *
 * This function prompts the user to enter the name of a song and then searches for the entered song name in the song list.
 * It displays the song information, including details such as name, album, artist, genre, year of publishing, rating, and music file,
 * for the matching song(s). The displayed information is presented in a table format. After completion, it releases the allocated
 * memory and prompts the user to continue by pressing any key.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *       charReplace, strCmpIgnoreCase, freeSongInfos.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *      charReplace, strCmpIgnoreCase, freeSongInfos
 */
void displayListedSongInfosFromAGivenSong();

/**
 * @brief Displays a menu for sorting songs by album, allowing options for alphabetical order or searching for songs with a specific album.
 *
 * This function prompts the user to choose between sorting songs by album in alphabetical order or searching for songs
 * with a specific album. It continuously prompts the user until they choose to exit. If sorting alphabetically, it redirects
 * to the relevant sorting function. If searching, it allows the user to input the album name and displays information for the
 * matching songs. After completion, it redirects back to the main sorted list menu or other relevant functions based on user choice.
 *
 * @note Assumes the availability of system, printListOptionsTitleScreen, printSortedListByAlbumOptions, getch,
 *       displayListedSongsSortedByAlbumA2Z, displayListedSongsWithAGivenAlbum, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByAlbumOptions, getch,
 *      displayListedSongsSortedByAlbumA2Z, displayListedSongsWithAGivenAlbum, displayListedSongsSorted
 */
void displayListedSongsSortedByAlbum();

/**
 * @brief Displays a sorted list of songs by album in alphabetical order (A-Z).
 *
 * This function reads the song information from the file, allocates memory for each song element, and then sorts the songs
 * alphabetically by album. It prints the sorted list to the console, including song details such as name, album, artist, genre,
 * year of publishing, rating, and music file. After displaying the sorted list, it releases the allocated memory and prompts
 * the user to continue by pressing any key.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
 *       freeSongInfos, compareSongsByAlbum.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
 *      freeSongInfos, compareSongsByAlbum
 */
void displayListedSongsSortedByAlbumA2Z();

/**
 * @brief Displays songs with a given album entered by the user.
 *
 * This function prompts the user to enter the name of an album and then searches for songs with the entered album name in the song list.
 * It displays the song information, including details such as name, album, artist, genre, year of publishing, rating, and music file,
 * for the matching songs. The displayed information is presented in a table format. After completion, it releases the allocated
 * memory and prompts the user to continue by pressing any key.
 *
 * @note Assumes the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *       charReplace, strCmpIgnoreCase, freeSongInfos.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *      charReplace, strCmpIgnoreCase, freeSongInfos
 */
void displayListedSongsWithAGivenAlbum();

/**
 * @brief Displays a menu for sorting songs by artist, allowing options for alphabetical order or searching for songs with a specific artist.
 *
 * This function prompts the user to choose between sorting songs by artist in alphabetical order or searching for songs
 * with a specific artist. It continuously prompts the user until they choose to exit. If sorting alphabetically, it redirects
 * to the relevant sorting function. If searching, it allows the user to input the artist name and displays information for the
 * matching songs. After completion, it redirects back to the main sorted list menu or other relevant functions based on user choice.
 *
 * @note Assumes the availability of system, printListOptionsTitleScreen, printSortedListByArtistOptions, getch,
 *       displayListedSongsSortedByArtistA2Z, displayListedSongsWithAGivenArtist, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByArtistOptions, getch,
 *      displayListedSongsSortedByArtistA2Z, displayListedSongsWithAGivenArtist, displayListedSongsSorted
 */
void displayListedSongsSortedByArtist();

/**
 * @brief Displays the list of songs sorted by artist name in ascending order (A to Z).
 *
 * This function allocates memory for an array of song information structures, reads the song information from the
 * song list file, dynamically allocates memory for each song element, sorts the songs alphabetically by artist name
 * using the qsort function, and then prints the sorted list in a tabular format. The function also ensures proper
 * memory allocation, error handling, and resource release. It relies on utility functions for file handling,
 * memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsByArtist, printTableHeader, printTableRow, printPartingLine), and
 * other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsByArtist, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsSortedByArtistA2Z();

/**
 * @brief Displays the list of songs with a given artist.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * prompts the user to enter the desired artist, and then prints the songs with the specified artist in a
 * tabular format. The function ensures proper memory allocation, error handling, and resource release. It
 * relies on utility functions for file handling, memory management, string manipulation, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), string-related functions (fgets, charReplace,
 * strCmpIgnoreCase), utility functions (allocateSongInfos, freeSongInfos, printTableHeader, printTableRow,
 * printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, fgets, charReplace, strCmpIgnoreCase,
 * allocateSongInfos, freeSongInfos, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsWithAGivenArtist();

/**
 * @brief Displays the list of songs based on a specified genre substring.
 *
 * This function clears the console screen, allocates memory for the genre input, allocates memory for an array of
 * song information structures, reads the song information from the song list file, dynamically allocates memory for
 * each song element, prompts the user to enter the desired genre substring, and then prints the songs with the
 * specified genre substring in a tabular format. The function ensures proper memory allocation, error handling, and
 * resource release. It relies on utility functions for file handling, memory management, string manipulation, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), string-related functions (fgets, charReplace,
 * strstr), utility functions (allocateSongInfos, freeSongInfos, printTableHeader, printTableRow, printPartingLine),
 * and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, fgets, charReplace, strstr, allocateSongInfos,
 * freeSongInfos, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByGenre();

/**
 * @brief Displays a submenu for sorting and filtering songs by year of publishing.
 *
 * This function presents a menu on the console screen, allowing the user to choose from various options
 * to display the list of songs based on the year of publishing. The options include sorting the list from
 * newest to oldest, from oldest to newest, displaying songs newer than a given year, displaying songs older
 * than a given year, displaying songs with a given year of publishing, and displaying the entire list sorted.
 * The function uses arrow keys for navigation, reads user input, and calls the corresponding functions based
 * on the selected option. It ensures proper user interaction and navigation through the menu.
 *
 * @note Assumes the availability of console-related functions (system, printListOptionsTitleScreen,
 * printSortedListByYearOfPublishingOptions, getch), sorting and filtering functions
 * (displayListedSongsByYearOfPublishingNew2Old, displayListedSongsByYearOfPublishingOld2New,
 * displayListedSongsNewerThanTheGivenYear, displayListedSongsOlderThanTheGivenYear,
 * displayListedSongsWithAGivenYearOfPublishing, displayListedSongsSorted), and constant definitions (TRUE).
 *
 * @see system, printListOptionsTitleScreen, printSortedListByYearOfPublishingOptions, getch,
 * displayListedSongsByYearOfPublishingNew2Old, displayListedSongsByYearOfPublishingOld2New,
 * displayListedSongsNewerThanTheGivenYear, displayListedSongsOlderThanTheGivenYear,
 * displayListedSongsWithAGivenYearOfPublishing, displayListedSongsSorted, TRUE
 */
void displayListedSongsByYearOfPublishing();

/**
 * @brief Displays the list of songs sorted by year of publishing from newest to oldest.
 *
 * This function allocates memory for an array of song information structures, reads the song information from
 * the song list file, dynamically allocates memory for each song element, sorts the songs by year of publishing
 * in descending order using the qsort function, and then prints the sorted list in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for file
 * handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsByYearOfPublishingNew2Old, printTableHeader, printTableRow,
 * printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsByYearOfPublishingNew2Old, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByYearOfPublishingNew2Old();

/**
 * @brief Displays the list of songs sorted by year of publishing from oldest to newest.
 *
 * This function allocates memory for an array of song information structures, reads the song information from
 * the song list file, dynamically allocates memory for each song element, sorts the songs by year of publishing
 * in ascending order using the qsort function, and then prints the sorted list in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for file
 * handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow,
 * printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByYearOfPublishingOld2New();

/**
 * @brief Displays the list of songs published newer than the given year.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * prompts the user to enter the desired publication year, and then prints the songs published on or after
 * the specified year in a tabular format. The function ensures proper memory allocation, error handling,
 * and resource release. It relies on utility functions for file handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow,
 * printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsNewerThanTheGivenYear();

/**
 * @brief Displays the list of songs published older than the given year.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * prompts the user to enter the desired publication year, and then prints the songs published before the
 * specified year in a tabular format. The function ensures proper memory allocation, error handling, and
 * resource release. It relies on utility functions for file handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow,
 * printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsByYearOfPublishingOld2New, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsOlderThanTheGivenYear();

/**
 * @brief Displays the list of songs with a given year of publishing.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * prompts the user to enter the desired publication year, and then prints the songs published in the specified
 * year in a tabular format. The function ensures proper memory allocation, error handling, and resource release.
 * It relies on utility functions for file handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, printTableHeader, printTableRow, printPartingLine), and other system-related
 * functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsWithAGivenYearOfPublishing();

/**
 * @brief Displays the list of songs sorted by rating according to user-selected options.
 *
 * This function clears the console screen, prompts the user to select a sorting option (best to worst,
 * worst to best, or a specific rating), reads the user's choice, and then calls the corresponding function
 * to display the sorted list. The function relies on utility functions for console interaction, printing,
 * and sorting. It ensures proper user input handling, error prevention, and resource release.
 *
 * @note Assumes the availability of console-related functions (system, printf, getch), utility functions
 * (printListOptionsTitleScreen, printSortedListByRatingOptions, displayListedSongsByRatingBest2Worse,
 * displayListedSongsByRatingWorse2Best, displayListedSongsWithAGivenRating, displayListedSongsSorted),
 * and other system-related functions (exit).
 *
 * @see system, printf, getch, printListOptionsTitleScreen, printSortedListByRatingOptions,
 * displayListedSongsByRatingBest2Worse, displayListedSongsByRatingWorse2Best, displayListedSongsWithAGivenRating,
 * displayListedSongsSorted, exit
 */
void displayListedSongsByRating();

/**
 * @brief Displays the list of songs sorted by rating from best to worst.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * and prints the songs sorted by rating in descending order (best to worst) in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for
 * file handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsWorse2Best, printTableHeader, printTableRow, printPartingLine),
 * and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsWorse2Best, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByRatingBest2Worse();

/**
 * @brief Displays the list of songs sorted by rating from worst to best.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * and prints the songs sorted by rating in ascending order (worst to best) in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for
 * file handling, memory management, sorting, and printing.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, compareSongsBest2Worse, printTableHeader, printTableRow, printPartingLine),
 * and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * compareSongsBest2Worse, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByRatingWorse2Best();

/**
 * @brief Displays the list of songs with a given rating.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * takes user input for the desired rating, and prints the songs with the specified rating in a tabular format.
 * The function ensures proper memory allocation, error handling, and resource release. It relies on utility
 * functions for file handling, memory management, printing, and other system-related functions.
 *
 * @note Assumes the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), utility functions (allocateSongInfos,
 * freeSongInfos, printTableHeader, printTableRow, printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, allocateSongInfos, freeSongInfos,
 * printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsWithAGivenRating();

/**
 * @brief Exits the program with a specified return value.
 *
 * This function clears the console screen, prints a closing message, introduces a delay using usleep,
 * and then pauses the program before exiting with the specified return value. The function is designed
 * to provide a clean and user-friendly way to exit the program.
 *
 * @param returnValue The return value to be passed to the operating system.
 *
 * @note Assumes the availability of console-related functions (system, printf, usleep, PAUSE) and
 * program termination function (exit).
 *
 * @see system, printf, usleep, PAUSE, exit
 */
void exitProgramm(const int returnValue);

/**
 * @brief Generates a music file name based on song information.
 *
 * This function generates a music file name by concatenating the artist and song name,
 * replacing spaces and special characters with underscores, converting the result to
 * lowercase, and appending the ".wav" extension.
 *
 * @param songInfos The song information used to generate the file name.
 *
 * @return A dynamically allocated string containing the generated music file name.
 *         It is the responsibility of the caller to free the allocated memory.
 *
 * @note Assumes the availability of string-related functions (malloc, mergeStr,
 *       convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase).
 *
 * @see malloc, mergeStr, convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase
 */
String generateMusicFileName(const TSongInfos songInfos);

/**
 * @brief Replaces occurrences of a character in a string.
 *
 * This function replaces all occurrences of the specified old character with
 * the new character in the given string, up to the maximum length.
 *
 * @param old The character to be replaced.
 * @param new The character to replace 'old' with.
 * @param haystack The string in which replacements are made.
 * @param maxLength The maximum length to process in the string.
 *
 * @note The function modifies the input string directly.
 *
 * @see None
 */
void charReplace(const char old, const char new, char *haystack, const int maxLength);

/**
 * @brief Concatenates two strings and returns the result.
 *
 * This function concatenates the two input strings and returns a new
 * dynamically allocated string containing the result.
 *
 * @param str1 The first string.
 * @param str2 The second string.
 *
 * @return A dynamically allocated string containing the concatenated result.
 *         The caller is responsible for freeing the memory.
 *
 * @note The function exits the program if memory allocation fails.
 *
 * @see None
 */
String mergeStr(const char *str1, const char *str2);

/**
 * @brief Compares two strings for equality, ignoring case.
 *
 * This function compares the input strings for equality, ignoring case.
 *
 * @param str1 The first string.
 * @param str2 The second string.
 *
 * @return 1 if the strings are equal (ignoring case), 0 otherwise.
 *
 * @see None
 */
Boolean strCmpIgnoreCase(const char *str1, const char *str2);

/**
 * @brief Allocates memory for a new song information structure.
 *
 * This function allocates memory for a new instance of the TSongInfos structure, which represents information
 * about a song, including its name, album, artist, genre, duration, release year, music file name, and a flag
 * indicating whether the song is marked as a favorite. The allocated memory for each field is determined by
 * the MAX_STR_LEN constant. If memory allocation fails for any field, an error message is printed to the console.
 *
 * @return TSongInfos - A newly allocated TSongInfos structure with memory for each field.
 *
 * @note Assumes the existence of the TSongInfos structure, MAX_STR_LEN constant, String type, malloc function,
 * and the FALSE constant. Additionally, the function assumes that the caller will handle the deallocation of
 * memory associated with the TSongInfos structure when it is no longer needed.
 *
 * @see TSongInfos, MAX_STR_LEN, String, malloc, FALSE
 */
TSongInfos allocateSongInfos();

/**
 * @brief Sets the global index count based on the number of valid entries in the song list file.
 *
 * This function opens the song list file in read text mode and iterates through each line,
 * checking for validity and counting the number of valid entries. A valid line is one that is
 * not empty or composed only of whitespaces and matches the expected format using sscanf.
 * The function increments the global indexCount for each valid entry found.
 *
 * @note Assumes the availability of file-related functions (fopen, fclose, fgets), the global variable
 * (fullSongListFilePath), the global variable (indexCount), and standard library functions (isspace, sscanf).
 * Also, assumes the structure of the song list file with entries formatted as "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd".
 *
 * @see fopen, fclose, fgets, fullSongListFilePath, indexCount, isspace, sscanf
 */
void setIndexCount();

/**
 * @brief Retrieves the full path of the executable's directory.
 *
 * This function allocates dynamic memory for a buffer to store the full path of the executable.
 * It then uses the Windows API function GetModuleFileName to obtain the full path and filename of the
 * executable, and subsequently removes the filename, keeping only the directory path. The dynamic memory
 * allocated for the buffer must be freed by the caller after use.
 *
 * @return String - A dynamically allocated string containing the full path of the executable's directory.
 *                 NULL is returned in case of a memory allocation error.
 *
 * @note Assumes the availability of the Windows API function GetModuleFileName, the String type, malloc,
 * free, MAX_PATH constant, and the standard library functions (strrchr).
 *
 * @see GetModuleFileName, String, malloc, free, MAX_PATH, strrchr
 */
String getExecutablePath();

/**
 * @brief Checks if a file exists at the specified full file path.
 *
 * This function attempts to open the file at the given full file path in binary read mode.
 * If the file can be successfully opened, it is closed, and the function returns TRUE, indicating
 * that the file exists. If the file cannot be opened, the function returns FALSE, indicating that
 * the file does not exist or cannot be accessed.
 *
 * @param fullFilePath - The full path of the file to be checked for existence.
 * @return Boolean - TRUE if the file exists, FALSE otherwise.
 *
 * @note Assumes the availability of file-related functions (fopen, fclose), the Boolean type, and the
 * standard library headers. The function does not differentiate between a file that does not exist and
 * a file that cannot be accessed due to permissions or other reasons.
 *
 * @see fopen, fclose, Boolean
 */
Boolean fileExists(const String fullFilePath);

/**
 * @brief Converts spaces and specified special characters in a string to underscores.
 *
 * This function takes a null-terminated string as input and iterates through each character.
 * If the character is a space, '/', '\', or '|', it is replaced with an underscore ('_'). The
 * function modifies the input string in-place. If the input string is NULL, the function
 * returns immediately without making any changes.
 *
 * @param str - The null-terminated string to be processed.
 *
 * @note Assumes the input string is a null-terminated character array. The function modifies the
 * input string in place and does not allocate new memory. Special characters considered for
 * replacement are space (' '), forward slash ('/'), backslash ('\'), and vertical bar ('|').
 *
 * @see None
 */
void convertSpacesAndSpecialCharsToUnderscores(char *str);

/**
 * @brief Converts a string to lowercase.
 *
 * This function takes a null-terminated string as input and iterates through each character,
 * converting it to lowercase without using the string library's tolower function. The function
 * modifies the input string in-place. If the input string is NULL, the function returns
 * immediately without making any changes.
 *
 * @param str - The null-terminated string to be converted to lowercase.
 *
 * @note Assumes the input string is a null-terminated character array. The function modifies the
 * input string in place and does not allocate new memory.
 */
void convertToLowerCase(char *str);

/**
 * @brief Compares two songs based on their names for use in sorting functions.
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their names,
 * and compares them lexicographically using the strcmp function. The result is used to
 * determine the order of the elements during sorting.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the name of songA is lexicographically less than
 *               the name of songB, a positive value if greater, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure, strcmp function, and standard
 * pointer types. The function is suitable for use with sorting algorithms that expect
 * a comparison function taking const void pointers.
 *
 * @see TSongInfos, strcmp
 */
int compareSongsByName(const void *a, const void *b);

/**
 * @brief Compares two songs based on their albums for use in sorting functions.
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their album names,
 * and compares them lexicographically using the strcmp function. The result is used to
 * determine the order of the elements during sorting.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the album of songA is lexicographically less than
 *               the album of songB, a positive value if greater, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure, strcmp function, and standard
 * pointer types. The function is suitable for use with sorting algorithms that expect
 * a comparison function taking const void pointers.
 *
 * @see TSongInfos, strcmp
 */
int compareSongsByAlbum(const void *a, const void *b);

/**
 * @brief Compares two songs based on their artists for use in sorting functions.
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their artist names,
 * and compares them lexicographically using the strcmp function. The result is used to
 * determine the order of the elements during sorting.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the artist of songA is lexicographically less than
 *               the artist of songB, a positive value if greater, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure, strcmp function, and standard
 * pointer types. The function is suitable for use with sorting algorithms that expect
 * a comparison function taking const void pointers.
 *
 * @see TSongInfos, strcmp
 */
int compareSongsByArtist(const void *a, const void *b);

/**
 * @brief Compares two songs based on their years of publishing in descending order (new to old).
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their years of
 * publishing, and compares them. The result is used to determine the order of the elements
 * during sorting, with newer years coming before older years.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the year of songA is greater than the year of songB,
 *               a positive value if lesser, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure and standard pointer types.
 * The function is suitable for use with sorting algorithms that expect a comparison
 * function taking const void pointers.
 *
 * @see TSongInfos
 */
int compareSongsByYearOfPublishingNew2Old(const void *a, const void *b);

/**
 * @brief Compares two songs based on their years of publishing in ascending order (old to new).
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their years of
 * publishing, and compares them. The result is used to determine the order of the elements
 * during sorting, with older years coming before newer years.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the year of songA is less than the year of songB,
 *               a positive value if greater, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure and standard pointer types.
 * The function is suitable for use with sorting algorithms that expect a comparison
 * function taking const void pointers.
 *
 * @see TSongInfos
 */
int compareSongsByYearOfPublishingOld2New(const void *a, const void *b);

/**
 * @brief Compares two songs based on their ratings in descending order (worse to best).
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their ratings,
 * and compares them. The result is used to determine the order of the elements during
 * sorting, with lower ratings coming before higher ratings.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the rating of songA is greater than the rating of songB,
 *               a positive value if lesser, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure and standard pointer types.
 * The function is suitable for use with sorting algorithms that expect a comparison
 * function taking const void pointers.
 *
 * @see TSongInfos
 */
int compareSongsWorse2Best(const void *a, const void *b);

/**
 * @brief Compares two songs based on their ratings in ascending order (best to worse).
 *
 * This function is designed to be used as a comparison function with sorting algorithms,
 * such as qsort. It takes two pointers to TSongInfos structures, extracts their ratings,
 * and compares them. The result is used to determine the order of the elements during
 * sorting, with higher ratings coming before lower ratings.
 *
 * @param a - Pointer to the first TSongInfos structure.
 * @param b - Pointer to the second TSongInfos structure.
 * @return int - A negative value if the rating of songA is less than the rating of songB,
 *               a positive value if greater, and 0 if they are equal.
 *
 * @note Assumes the availability of the TSongInfos structure and standard pointer types.
 * The function is suitable for use with sorting algorithms that expect a comparison
 * function taking const void pointers.
 *
 * @see TSongInfos
 */
int compareSongsBest2Worse(const void *a, const void *b);

/**
 * @brief Frees the dynamically allocated memory within a TSongInfos structure.
 *
 * This function takes a TSongInfos structure as input and frees the dynamically
 * allocated memory associated with its fields (name, album, artist, genre, and
 * musicFileName). It is essential to call this function to prevent memory leaks
 * when the TSongInfos structure is no longer needed.
 *
 * @param songInfos - The TSongInfos structure whose memory is to be freed.
 *
 * @note Assumes the availability of the TSongInfos structure and the free function.
 * The function does not set the pointers in the structure to NULL after freeing
 * the memory.
 *
 * @see TSongInfos, free
 */
void freeSongInfos(const TSongInfos songInfos);

/**
 * @brief Performs cleanup operations before exiting the program.
 *
 * This function is an exit handler that frees dynamically allocated memory for global
 * variables related to file paths (fullSongListFilePath, fullMusicFolderFilePath,
 * fullUserDataFilePath). It is intended to be called before exiting the program to
 * prevent memory leaks.
 *
 * @note Assumes the availability of the free function and the global variables
 * (fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath).
 *
 * @see free, fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath
 */
void exitHandler();

#endif //SONGS_H

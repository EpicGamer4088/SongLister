#ifndef SONGLISTER_UTILS_H
#define SONGLISTER_UTILS_H

#include <stdio.h>

/**
 * @brief Maximum length for strings in the program.
 *
 * This line defines the constant MAX_STR_LEN with a value of 255, representing the
 * maximum length for strings in the program. It is commonly used to define the size
 * of character arrays to avoid hardcoding values and enhance code maintainability.
 *
 * @note This constant is used consistently in the program for defining
 * string lengths.
 */
#define MAX_STR_LEN 255

/**
 * @brief File name for the user data file.
 *
 * This line defines the constant USERDATA_FILE_NAME with the value "/userdata.bin",
 * representing the file name for the user data file.
 *
 * @note This constant is used as the user data file name in the program.
 */
#define USERDATA_FILE_NAME "/userdata.bin"

/**
 * @brief Definition of the String type as a character pointer.
 *
 * This line defines the String type as a synonym for a character pointer (char *).
 * It is commonly used to improve code readability and provide a more descriptive
 * name for character arrays or strings in C.
 *
 * @note This type definition is used for Dynamic String Variables in the program.
 *
 * @see char
 */
typedef char *String;

/**
 * @brief External declaration of the index count variable.
 *
 * This line declares an external integer variable named indexCount.
 *
 * @note The int type is declared int utils.c and defined in the Main function.
 *
 * @see int
 */
extern int indexCount;

/**
 * @brief External declaration of the full song list file path.
 *
 * This line declares an external String variable named fullSongListFilePath.
 *
 * @note The String type is declared in utils.c and defined in the Main function.
 *
 * @see String
 */
extern String fullSongListFilePath;

/**
 * @brief External declaration of the full music folder file path.
 *
 * This line declares an external String variable named fullMusicFolderFilePath.
 *
 * @note The String type is declared in utils.c and defined in the Main function.
 *
 * @see String
 */
extern String fullMusicFolderFilePath;

/**
 * @brief External declaration of the full user data file path.
 *
 * This line declares an external String variable named fullUserDataFilePath.
 *
 * @note The String type is declared in utils.c and defined in the Main function.
 *
 * @see String
 */
extern String fullUserDataFilePath;

/**
 * @brief Enumeration representing boolean values.
 *
 * This enumeration, named Boolean, defines two constant values: FALSE and TRUE,
 * representing boolean values in C.
 *
 * @note The enumeration is used in contexts where Boolean values are
 * needed, and TRUE is considered equivalent to a non-zero value, while FALSE is zero.
 *
 * @see None
 */
typedef enum Boolean {
    FALSE, ///< Represents the boolean value false.
    TRUE   ///< Represents the boolean value true.
} Boolean;

/**
 * @brief Structure representing information about a song.
 *
 * This structure, named TSongInfos, encapsulates details about a song, including its name,
 * album, artist, genre, year of publishing, rating, music file name, and a flag indicating
 * whether a music file is associated with the song. The String type is a
 * dynamic character array, and Boolean is used for representing true/false values. The structure is
 * designed to hold dynamic strings for various fields, and it is used to manage
 * information about songs in the program.
 *
 * @note The structure is used in conjunction with functions and
 * operations related to managing and manipulating song information.
 *
 * @see String, Boolean
 */
typedef struct SongInfos {
    String name;          ///< Name of the song.
    String album;         ///< Album of the song.
    String artist;        ///< Artist of the song.
    String genre;         ///< Genre of the song.
    short yearPublished;  ///< Year the song was published.
    short rating;         ///< Rating assigned to the song.
    String musicFileName; ///< File name of the associated music file.
    Boolean musicFile;    ///< Flag indicating whether a music file is associated with the song.
} TSongInfos;


/**
 * @brief Main function for the program.
 *
 * This function serves as the entry point for the program. It initializes signal handlers for
 * SIGINT (Ctrl+C) and SIGTERM (termination signal). Memory is allocated for file path strings
 * (fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath). It checks and handles
 * the existence and content of the user data file, the song list file and the music file folder.
 * The index count is set based on the number of entries in the user data file. It further checks
 * the validity of all music file entries.
 *
 * @warning Ensure proper memory deallocation after program execution.
 */
void Main();

/**
 * @brief Sets the global index count based on the number of valid entries in the song list file.
 *
 * This function opens the song list file in read text mode and iterates through each line,
 * checking for validity and counting the number of valid entries. A valid line is one that is
 * not empty or composed only of whitespaces and matches the expected format using sscanf.
 * The function increments the global indexCount for each valid entry found.
 *
 * @note @note Requires the presence of file-related functions (fopen, fclose, fgets), the global variable
 * (fullSongListFilePath), (indexCount), and standard library functions (isspace, sscanf).
 * Additionally, the song list file is expected to have entries formatted as "%hd;%[^;];%[^;];%[^;];%[^;];%hd;%hd".
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
 * @note Requires the availability of the Windows API function GetModuleFileName, the String type, malloc,
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
 * @note Requires the availability of file-related functions (fopen, fclose), the Boolean type, and the
 * standard library headers. The function does not differentiate between a file that does not exist and
 * a file that cannot be accessed due to permissions or other reasons.
 *
 * @see fopen, fclose, Boolean
 */
Boolean fileExists(const String fullFilePath);

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
 * @note Requires the availability of the Windows API and the GetOpenFileName function.
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
 * @note Requires the availability of the Windows API and the SHBrowseForFolder and SHGetPathFromIDList functions.
 *
 * @see BROWSEINFO, SHBrowseForFolder, SHGetPathFromIDList
 */
String openFolderDialog();

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
 * @note Requires the existence of helper functions such as allocateSongInfos, freeSongInfos, mergeStr,
 *       convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase, fileExists, and strCmpIgnoreCase.
 * @note Exits the program with an error message if memory allocation or file operations encounter issues.
 *
 * @see allocateSongInfos, freeSongInfos, mergeStr, convertSpacesAndSpecialCharsToUnderscores,
 *      convertToLowerCase, fileExists, strCmpIgnoreCase
 */
void checkIfAllMusicFileEntriesAreValid();

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
 * @brief Checks and handles the existence of the song list file.
 *
 * This function checks if the song list file exists. If the file does not exist, it opens a file dialog
 * to prompt the user to select a CSV file. If the file already exists, it closes the file handle.
 *
 * @note Requires the availability of the file-related functions (fopen, fclose) and the file dialog function (openCSVFileDialog).
 *
 * @see fopen, fclose, openCSVFileDialog
 */
void checkAndHandleSongListFile();

/**
 * @brief Checks and handles the existence of the music file folder.
 *
 * This function checks if the music file folder exists. If the folder does not exist, it opens a folder dialog
 * to prompt the user to select a folder. If the folder already exists, it does nothing.
 *
 * @note Requires the availability of the Windows API functions (PathFileExistsA, CreateDirectoryA) and the folder dialog function (openFolderDialog).
 *
 * @see PathFileExistsA, CreateDirectoryA, openFolderDialog
 */
void checkAndHandleMusicFolder();

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
 * @note Requires the availability of the Windows API and the CopyFile and GetLastError functions.
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
 * @note Requires the availability of the Windows API and the remove and GetLastError functions.
 *
 * @see remove, GetLastError
 */
void removeMusicFileFromMusicFolder(const String filePath);

/**
 * @brief Sets user data by prompting the user to select a song list file and a music folder.
 *
 * This function sets the user data by using file dialogs to prompt the user to select a song list file
 * and a music folder. The selected file paths are stored in global variables for later use.
 *
 * @note Requires the availability of the file dialog functions (openCSVFileDialog, openFolderDialog).
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
 * @note Requires the availability of the file-related functions (fopen, fclose, fwrite) and global variables
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
 * @note Requires the availability of the file-related functions (fopen, fclose, fread) and global variables
 * (fullSongListFilePath, fullMusicFolderFilePath).
 *
 * @see fopen, fclose, fread
 */
void readUserDataFromUserDataFile();

/**
 * @brief Updates the song list file path in the user data file.
 *
 * This function prompts the user to select a new song list file path using a file dialog.
 * The selected path is then updated in the user data file, and a success message is displayed.
 *
 * @note Requires the availability of the console-related functions (system), UI-related functions,
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
 * @note Requires the availability of the console-related functions (system), UI-related functions,
 * folder dialog function (openFolderDialog), and user data writing function (writeUserDataIntoUserDataFile).
 *
 * @see system, openFolderDialog, writeUserDataIntoUserDataFile
 */
void updateMusicFolderPathInUserDataFile();

/**
 * @brief Plays a wave file asynchronously.
 *
 * This function sets the playback status to playing and uses the Windows API PlaySound function
 * to play the specified wave file asynchronously.
 *
 * @param fullMusicFilePath Full path to the wave file to be played.
 * @param isPlaying Pointer to a Boolean flag indicating the playback status.
 *
 * @note Requires the availability of PlaySound and SND_ASYNC.
 *
 * @see PlaySound, SND_ASYNC
 */
void playWaveFile(const String fullMusicFilePath, Boolean *isPlaying);

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
 * @note Requires the availability of PlaySound, SND_PURGE, and playWaveFile function.
 *
 * @see PlaySound, SND_PURGE, playWaveFile
 */
void pauseResumePlayback(const String fullMusicFilePath, Boolean *isPlaying);

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
 * @note Requires the availability of string-related functions (malloc, mergeStr,
 *       convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase).
 *
 * @see malloc, mergeStr, convertSpacesAndSpecialCharsToUnderscores, convertToLowerCase
 */
String generateMusicFileName(const TSongInfos songInfos);

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
 * @note Requires the input string is a null-terminated character array. The function modifies the
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
 * @note Requires the input string is a null-terminated character array. The function modifies the
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
 * @note Requires the availability of the TSongInfos structure, strcmp function, and standard
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
 * @note Requires the availability of the TSongInfos structure, strcmp function, and standard
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
 * @note Requires the availability of the TSongInfos structure, strcmp function, and standard
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
 * @note Requires the availability of the TSongInfos structure and standard pointer types.
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
 * @note Requires the availability of the TSongInfos structure and standard pointer types.
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
 * @note Requires the availability of the TSongInfos structure and standard pointer types.
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
 * @note Requires the availability of the TSongInfos structure and standard pointer types.
 * The function is suitable for use with sorting algorithms that expect a comparison
 * function taking const void pointers.
 *
 * @see TSongInfos
 */
int compareSongsBest2Worse(const void *a, const void *b);

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
 * @return TRUE if the strings are equal (ignoring case), FALSE otherwise.
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
 * @note Requires the existence of the TSongInfos structure, MAX_STR_LEN constant, String type, malloc function,
 * and the FALSE constant. Additionally, the function assumes that the caller will handle the deallocation of
 * memory associated with the TSongInfos structure when it is no longer needed.
 *
 * @see TSongInfos, MAX_STR_LEN, String, malloc, FALSE
 */
TSongInfos allocateSongInfos();

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
 * @note Requires the availability of the TSongInfos structure and the free function.
 * The function does not set the pointers in the structure to NULL after freeing
 * the memory.
 *
 * @see TSongInfos, free
 */
void freeSongInfos(const TSongInfos songInfos);

/**
 * @brief Exits the program with a specified return value.
 *
 * This function clears the console screen, prints a closing message, introduces a delay using usleep,
 * and then pauses the program before exiting with the specified return value. The function is designed
 * to provide a clean and user-friendly way to exit the program.
 *
 * @param returnValue The return value to be passed to the operating system.
 *
 * @note Requires the availability of console-related functions (system, printf, usleep, PAUSE) and
 * program termination function (exit).
 *
 * @see system, printf, usleep, PAUSE, exit
 */
void exitProgramm(const int returnValue);

/**
 * @brief Performs cleanup operations before exiting the program.
 *
 * This function is an exit handler that frees dynamically allocated memory for global
 * variables related to file paths (fullSongListFilePath, fullMusicFolderFilePath,
 * fullUserDataFilePath). It is intended to be called before exiting the program to
 * prevent memory leaks.
 *
 * @note Requires the availability of the free function and the global variables
 * (fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath).
 *
 * @see free, fullSongListFilePath, fullMusicFolderFilePath, fullUserDataFilePath
 */
void exitHandler();


#endif //SONGLISTER_UTILS_H

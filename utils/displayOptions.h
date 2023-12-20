#ifndef SONGLISTER_DISPLAYOPTIONS_H
#define SONGLISTER_DISPLAYOPTIONS_H


/**
 * @brief Prints a formatted line for visual separation or boundary in a table-like display.
 *
 * This function prints a line with fixed-length segments, creating a visual separation or boundary.
 * It is commonly used in table-like displays to enhance readability and structure.
 *
 * @note This function requires the availability of a console environment for text output.
 *
 * @see printf
 */
void printPartingLine();

/**
 * @brief Prints the table header with column labels for a music information display.
 *
 * This function clears the console screen, prints a visual separation line, and then prints the column labels
 * for a table displaying music information, including Name, Album, Artist, Genre, Year, Rating, and Music File.
 * Another visual separation line is printed below the header for a structured appearance.
 *
 * @note Requires the availability of system and printPartingLine functions.
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
 *
 * @note Requires the availability of a console environment for text output.
 *
 * @see printf
 */
void printTableRow(const TSongInfos song);

/**
 * @brief Displays a static list of songs, including details like name, album, artist, genre, year, rating, and music file.
 *
 * This function allocates memory for song information, reads song details from a file, and prints a formatted table
 * displaying each song's information. It prints a header with column names and separates each song entry with a line.
 * After displaying the list, it releases allocated memory and pauses the program.
 *
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, and indexCount.
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
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, and indexCount.
 * @note Requires the availability of strCmpIgnoreCase.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, freeSongInfos, strCmpIgnoreCase, indexCount
 */
void displayListedSongsWithValidMusicFile();

/**
 * @brief Displays a sorted list of songs by name in alphabetical order (A-Z).
 *
 * This function reads the song information from the file, allocates memory for each song element, and then sorts the songs
 * alphabetically by name. It prints the sorted list to the console, including song details such as name, album, artist, genre,
 * year of publishing, rating, and music file. After displaying the sorted list, it releases the allocated memory and prompts
 * the user to continue by pressing any key.
 *
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
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
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *       charReplace, strCmpIgnoreCase, freeSongInfos.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *      charReplace, strCmpIgnoreCase, freeSongInfos
 */
void displayListedSongInfosFromAGivenSong();

/**
 * @brief Displays a sorted list of songs by album in alphabetical order (A-Z).
 *
 * This function reads the song information from the file, allocates memory for each song element, and then sorts the songs
 * alphabetically by album. It prints the sorted list to the console, including song details such as name, album, artist, genre,
 * year of publishing, rating, and music file. After displaying the sorted list, it releases the allocated memory and prompts
 * the user to continue by pressing any key.
 *
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, qsort,
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
 * @note Requires the availability of system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *       charReplace, strCmpIgnoreCase, freeSongInfos.
 *
 * @see system, printTableHeader, printTableRow, printPartingLine, fclose, fopen, printf, fgets,
 *      charReplace, strCmpIgnoreCase, freeSongInfos
 */
void displayListedSongsWithAGivenAlbum();

/**
 * @brief Displays the list of songs sorted by artist name in ascending order (A to Z).
 *
 * This function allocates memory for an array of song information structures, reads the song information from the
 * song list file, dynamically allocates memory for each song element, sorts the songs alphabetically by artist name
 * using the qsort function, and then prints the sorted list in a tabular format. The function also ensures proper
 * memory allocation, error handling, and resource release. It relies on utility functions for file handling,
 * memory management, sorting, and printing.
 *
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), string-related functions (fgets, charReplace,
 * strstr), utility functions (allocateSongInfos, freeSongInfos, printTableHeader, printTableRow, printPartingLine),
 * and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, fgets, charReplace, strstr, allocateSongInfos,
 * freeSongInfos, printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsByGenre();

/**
 * @brief Displays the list of songs sorted by year of publishing from newest to oldest.
 *
 * This function allocates memory for an array of song information structures, reads the song information from
 * the song list file, dynamically allocates memory for each song element, sorts the songs by year of publishing
 * in descending order using the qsort function, and then prints the sorted list in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for file
 * handling, memory management, sorting, and printing.
 *
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), sorting function (qsort), utility functions
 * (allocateSongInfos, freeSongInfos, printTableHeader, printTableRow, printPartingLine), and other system-related
 * functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, qsort, allocateSongInfos, freeSongInfos,
 * printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsWithAGivenYearOfPublishing();

/**
 * @brief Displays the list of songs sorted by rating from best to worst.
 *
 * This function clears the console screen, allocates memory for an array of song information structures,
 * reads the song information from the song list file, dynamically allocates memory for each song element,
 * and prints the songs sorted by rating in descending order (best to worst) in a tabular format. The function
 * ensures proper memory allocation, error handling, and resource release. It relies on utility functions for
 * file handling, memory management, sorting, and printing.
 *
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
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
 * @note Requires the availability of console-related functions (system, printf, pause), file-related functions
 * (fopen, fscanf, fclose), memory-related functions (malloc, free), utility functions (allocateSongInfos,
 * freeSongInfos, printTableHeader, printTableRow, printPartingLine), and other system-related functions (exit).
 *
 * @see system, printf, pause, fopen, fscanf, fclose, malloc, free, allocateSongInfos, freeSongInfos,
 * printTableHeader, printTableRow, printPartingLine, exit
 */
void displayListedSongsWithAGivenRating();


#endif //SONGLISTER_DISPLAYOPTIONS_H

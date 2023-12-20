#ifndef SONGLISTER_MENUES_H
#define SONGLISTER_MENUES_H


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
 * @brief Prints the title screen of the program to the console.
 *
 * This function displays a simple ASCII art title screen for the Song Rater program.
 * The title is enclosed in a box for aesthetic presentation. It uses the printf function
 * to output the formatted title screen to the console.
 *
 * @note This function requires the availability of a console environment for text output.
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
 * @note This function requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
 *
 * @see printf
 */
void printPlayMusicScreen(TSongInfos songs);

/**
 * @brief Updates user data by providing options to change the song list file path or music folder path.
 *
 * This function displays a menu allowing the user to choose between updating the song list file path,
 * updating the music folder path, or returning to the main menu. The user's selection determines the
 * action to be taken.
 *
 * @note Requires the availability of the console-related functions (system, getch), UI-related functions
 * (printTitleScreen, printChangeUserDataOptions), and other functions for updating specific user data.
 *
 * @see system, getch, printTitleScreen, printChangeUserDataOptions, updateSongListFilePathInUserDataFile,
 * updateMusicFolderPathInUserDataFile, MainMenu
 */
void updateUserDataMenu();

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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
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
 * @note Requires the availability of a console environment for text output.
 *
 * @see printf
 */
void printSortedListByRatingOptions(const int selectedOption);

/**
 * @brief Displays the music-related menu and handles user interactions.
 *
 * This function continuously displays the music menu, reads user input, and responds based on the selected option.
 * The menu includes options for adding, removing, changing, listing songs with valid music files, playing music,
 * and returning to the main menu. It uses arrow keys for navigation and the Enter key to select an option.
 * The selected option is then processed, and the corresponding action is performed. The menu is redisplayed until
 * the user chooses to return to the main menu.
 *
 * @note Requires the availability of system, getch, printListOptionsTitleScreen, printMusicOptions, addMusicFile,
 * removeMusicFile, changeMusicFile, displayListedSongsWithValidMusicFile, playMusic, and MainMenu functions.
 *
 * @see system, getch, printListOptionsTitleScreen, printMusicOptions, addMusicFile, removeMusicFile, changeMusicFile,
 * displayListedSongsWithValidMusicFile, playMusic, MainMenu
 */
void displayMusicMenu();

/**
 * @brief Displays options for listing songs and performs the selected action.
 *
 * This function prompts the user with options to list songs statically, list songs sorted, display songs
 * with valid music files, or return to the main menu. It interacts with the user to select different display
 * options and performs the corresponding actions based on the user's choice.
 *
 * @note Requires the availability of system, getch, printListOptionsTitleScreen, printListOptions,
 * displayListedSongsStatic, displayListedSongsSorted, displayListedSongsWithValidMusicFile, and MainMenu functions.
 *
 * @see system, getch, printListOptionsTitleScreen, printListOptions,
 * displayListedSongsStatic, displayListedSongsSorted, displayListedSongsWithValidMusicFile, MainMenu
 */
void displayListedSongs();

/**
 * @brief Displays a sorted list of songs based on user-selected criteria, allowing sorting by name, album, artist, genre, year, or rating.
 *
 * This function presents a menu to the user for selecting the sorting criteria, and then displays the list of songs
 * accordingly. It continuously prompts the user until they choose to exit. The available sorting options include sorting
 * by name, album, artist, genre, year of publishing, and rating. After displaying the sorted list, it redirects to the main
 * menu or other relevant functions based on user choice.
 *
 * @note Requires the availability of system, printListOptionsTitleScreen, printSortedListOptions, getch,
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
 * @note Requires the availability of system, printListOptionsTitleScreen, printSortedListByNameOptions, getch,
 *       displayListedSongsSortedByNameA2Z, displayListedSongInfosFromAGivenSong, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByNameOptions, getch,
 *      displayListedSongsSortedByNameA2Z, displayListedSongInfosFromAGivenSong, displayListedSongsSorted
 */
void displayListedSongsSortedByName();

/**
 * @brief Displays a menu for sorting songs by album, allowing options for alphabetical order or searching for songs with a specific album.
 *
 * This function prompts the user to choose between sorting songs by album in alphabetical order or searching for songs
 * with a specific album. It continuously prompts the user until they choose to exit. If sorting alphabetically, it redirects
 * to the relevant sorting function. If searching, it allows the user to input the album name and displays information for the
 * matching songs. After completion, it redirects back to the main sorted list menu or other relevant functions based on user choice.
 *
 * @note Requires the availability of system, printListOptionsTitleScreen, printSortedListByAlbumOptions, getch,
 *       displayListedSongsSortedByAlbumA2Z, displayListedSongsWithAGivenAlbum, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByAlbumOptions, getch,
 *      displayListedSongsSortedByAlbumA2Z, displayListedSongsWithAGivenAlbum, displayListedSongsSorted
 */
void displayListedSongsSortedByAlbum();

/**
 * @brief Displays a menu for sorting songs by artist, allowing options for alphabetical order or searching for songs with a specific artist.
 *
 * This function prompts the user to choose between sorting songs by artist in alphabetical order or searching for songs
 * with a specific artist. It continuously prompts the user until they choose to exit. If sorting alphabetically, it redirects
 * to the relevant sorting function. If searching, it allows the user to input the artist name and displays information for the
 * matching songs. After completion, it redirects back to the main sorted list menu or other relevant functions based on user choice.
 *
 * @note Requires the availability of system, printListOptionsTitleScreen, printSortedListByArtistOptions, getch,
 *       displayListedSongsSortedByArtistA2Z, displayListedSongsWithAGivenArtist, displayListedSongsSorted.
 *
 * @see system, printListOptionsTitleScreen, printSortedListByArtistOptions, getch,
 *      displayListedSongsSortedByArtistA2Z, displayListedSongsWithAGivenArtist, displayListedSongsSorted
 */
void displayListedSongsSortedByArtist();

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
 * @note Requires the availability of console-related functions (system, printListOptionsTitleScreen,
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
 * @brief Displays the list of songs sorted by rating according to user-selected options.
 *
 * This function clears the console screen, prompts the user to select a sorting option (best to worst,
 * worst to best, or a specific rating), reads the user's choice, and then calls the corresponding function
 * to display the sorted list. The function relies on utility functions for console interaction, printing,
 * and sorting. It ensures proper user input handling, error prevention, and resource release.
 *
 * @note Requires the availability of console-related functions (system, printf, getch), utility functions
 * (printListOptionsTitleScreen, printSortedListByRatingOptions, displayListedSongsByRatingBest2Worse,
 * displayListedSongsByRatingWorse2Best, displayListedSongsWithAGivenRating, displayListedSongsSorted),
 * and other system-related functions (exit).
 *
 * @see system, printf, getch, printListOptionsTitleScreen, printSortedListByRatingOptions,
 * displayListedSongsByRatingBest2Worse, displayListedSongsByRatingWorse2Best, displayListedSongsWithAGivenRating,
 * displayListedSongsSorted, exit
 */
void displayListedSongsByRating();

#endif //SONGLISTER_MENUES_H

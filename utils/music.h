#ifndef SONGLISTER_MUSIC_H
#define SONGLISTER_MUSIC_H


/**
 * @brief Inputs information for a new song.
 *
 * This function allocates memory for a new song, prompts the user to input various information such as
 * name, album, artist, genre, year published, and rating. It also provides an option to add a music file
 * for the song. The input is validated, and the song information is returned.
 *
 * @return TSongInfos The structure containing the input song information.
 *
 * @note Requires the availability of the console-related functions (printf, fgets, scanf, getchar, fflush),
 * memory allocation functions (allocateSongInfos), string manipulation functions (charReplace),
 * and other utility functions (addMusicFileForNewSong).
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
 * @note Requires the availability of the console-related functions (system, printf, usleep),
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
 * @note Requires the availability of the console-related functions (system, printf, usleep), file-related
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
 * @note Requires the availability of the console-related functions (system, printf, usleep), file-related
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
 * @note Requires the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf,
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
 * @note Requires the availability of system, printf, usleep, malloc, free, fopen, fclose, perror,
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
 * @note Requires the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose,
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
 * @note Requires the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose,
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
 * @note Requires the availability of system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf,
 * fgets, fflush, charReplace, strCmpIgnoreCase, displayMusicMenu, printPlayMusicScreen, playWaveFile,
 * pauseResumePlayback, getch, and other related functions.
 *
 * @see system, printf, usleep, malloc, free, perror, exit, fopen, fclose, fscanf, fgets, fflush, charReplace,
 * strCmpIgnoreCase, displayMusicMenu, printPlayMusicScreen, playWaveFile, pauseResumePlayback, getch
 */
void playMusic();


#endif //SONGLISTER_MUSIC_H

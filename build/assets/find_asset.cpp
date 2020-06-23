/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** find_asset
*/

#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define NEXT_FOLDER "\\"
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define NEXT_FOLDER "/"
#endif
 
std::string findAsset( std::string asset ) {
    size_t pos = 0;
    char buff[FILENAME_MAX];

    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    if (current_working_dir.find("OOP_indie_studio_2019") == std::string::npos &&
        current_working_dir.find("indie") == std::string::npos &&
        current_working_dir.find("bomberman") == std::string::npos) {
        current_working_dir += NEXT_FOLDER;
        current_working_dir += "OOP_indie_studio_2019";
    }
    if ((pos = current_working_dir.find("bin")) && pos == (current_working_dir.length() - 3)) {
        current_working_dir += NEXT_FOLDER;
        current_working_dir += "..";
        current_working_dir += NEXT_FOLDER;
    }
    current_working_dir += NEXT_FOLDER;
    current_working_dir += "assets";
    current_working_dir += NEXT_FOLDER;
    current_working_dir += asset;
    return current_working_dir;
}
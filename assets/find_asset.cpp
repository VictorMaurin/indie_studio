/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** find_asset
*/

#include <string>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define NEXT_FOLDER "\"
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define NEXT_FOLDER "/"
#endif
 
std::string findAsset( std::string asset ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    if (current_working_dir.find("OOP_indie_studio_2019") == std::string::npos ||
        current_working_dir.find("indie") == std::string::npos ||
        current_working_dir.find("bomberman") == std::string::npos) {
        current_working_dir += NEXT_FOLDER;
        current_working_dir += "OOP_indie_studio_2019";
    }
    current_working_dir += NEXT_FOLDER;
    current_working_dir += "assets";
    current_working_dir += NEXT_FOLDER;
    current_working_dir += asset;
    return current_working_dir;
}
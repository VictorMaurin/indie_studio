/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** assets
*/

#ifndef ASSETS_H_
#define ASSETS_H_

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <string.h>

#define ASSETS_PATH(x) ({                           \
    char a[255];                                    \
    getcwd(a, 255);                                 \
    if (!strstr(a, "OOP_indie_studio_2019"))        \
        strcat(a, "/OOP_indie_studio_2019");        \
    strcat(a, "/assets/");                          \
    strcat(a, x);                                   \
    a;                                              \
})

#endif /* !ASSETS_H_ */

/*
** EPITECH PROJECT, 2023
** directory
** File description:
** directory
*/

#include "myteams.h"

bool create_directory_if_not_exists(const char *dir)
{
    char *tmp = strdup(dir);
    char *p = NULL;
    size_t len = strlen(tmp);

    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for (p = tmp + 1; *p; p++)
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    mkdir(tmp, S_IRWXU);
    free(tmp);
    return true;
}

bool directory_exists(const char *dir_path)
{
    struct stat info;
    if (stat(dir_path, &info) != 0) {
        return false;
    }
    return S_ISDIR(info.st_mode);
}

bool file_exists(const char *path)
{
    struct stat st;
    return (stat(path, &st) == 0);
}

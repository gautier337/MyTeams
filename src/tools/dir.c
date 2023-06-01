/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** dir
*/

#include "myteams.h"

bool is_empty_dir(DIR *dir)
{
    struct dirent *entry = NULL;

    if (!dir)
        return true;
    for (entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] != '.' && entry->d_type == DT_DIR)
            return false;
    }
    return true;
}

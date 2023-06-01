/*
** EPITECH PROJECT, 2023
** replace_str
** File description:
** replace_str
*/

#include "myteams.h"

char *replace_str(char *string)
{
    if (!string)
        return NULL;
    for (int i = 0; string[i]; i++)
        if (string[i] == ',')
            string[i] = '_';
    return string;
}

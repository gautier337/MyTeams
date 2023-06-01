/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** my_strcasecmp
*/

#include "my.h"

int tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int my_strcasecmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;
    while (s1[i] && s2[i]) {
        if (tolower(s1[i]) != tolower(s2[i]))
            return 1;
        i += 1;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
        return 0;
    if (s1[i] == '\0')
        return -1;
    return 1;
}

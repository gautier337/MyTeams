/*
** EPITECH PROJECT, 2021
** my_strncasecmp
** File description:
** Function my_strncasecmp
*/

#include "my.h"

static int tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int my_strncasecmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;
    while (s1[i] && s2[i] && i < n) {
        if (tolower(s1[i]) != tolower(s2[i]))
            return 1;
        i += 1;
    }
    if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
        return 0;
    if (s1[i] == '\0')
        return -1;
    return 1;
}

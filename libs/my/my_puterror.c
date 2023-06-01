/*
** EPITECH PROJECT, 2021
** my_puterror
** File description:
** Function that prints a str on the error output
*/

#include "my.h"

int my_puterror(char const *str)
{
    if (str == NULL)
        return 84;
    write(1, KRED, my_strlen(KRED));
    write(1, str, my_strlen(str));
    write(1, KRESET, my_strlen(KRESET));
    return 84;
}

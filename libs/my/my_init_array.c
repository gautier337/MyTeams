/*
** EPITECH PROJECT, 2023
** my_init_array
** File description:
** Function my_init_array
*/

#include "my.h"

char **my_init_array(int size)
{
    char **array = NULL;

    if (size == 0)
        return NULL;
    if (!(array = malloc(sizeof(char *) * size + 1)))
        return NULL;
    for (int i = 0; i <= size; i++)
        array[i] = NULL;
    return array;
}

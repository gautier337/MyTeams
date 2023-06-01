/*
** EPITECH PROJECT, 2023
** clear_pointer
** File description:
** pointer
*/

#include "myteams.h"

void clear_pointer(void **ptr)
{
    if (*ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

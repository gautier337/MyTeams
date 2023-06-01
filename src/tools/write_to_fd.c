/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** write_to_fd.c
*/

#include "myteams.h"

void write_to_fd(int fd, const char *buffer)
{
    if (!buffer)
        exit_error("Buffer is NULL!\n");
    if (write(fd, buffer, my_strlen(buffer)) < 0)
        exit_error("write()");
}

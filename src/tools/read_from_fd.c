/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** read_from_fd.c
*/

#include "tools.h"

char *read_from_fd(int fd, size_t size)
{
    char *buffer = malloc(sizeof(char) * size);
    ssize_t read_size = 0;

    if (buffer == NULL)
        exit_error("Malloc failed!");
    read_size = read(fd, buffer, size);
    if (read_size == -1) {
        free(buffer);
        exit_error("read()");
    }
    buffer[read_size] = '\0';
    return buffer;
}

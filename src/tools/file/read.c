/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** read_file
*/

#include "tools.h"

size_t get_file_size(FILE *fp)
{
    struct stat st;

    if (fstat(fileno(fp), &st) == -1)
        return -1;
    return st.st_size;
}

char *malloc_buffer_from_file_size(FILE *fp)
{
    struct stat st;
    char *buffer = NULL;

    if (fstat(fileno(fp), &st) == -1)
        return NULL;
    if (!(buffer = malloc((st.st_size + 1) * sizeof(char))))
        return NULL;
    return buffer;
}

char *return_and_close(FILE *fp, char *buffer)
{
    fclose(fp);
    return buffer;
}

char *read_file(const char *filename)
{
    FILE *fp;
    size_t len = 0;
    ssize_t read;
    char *buffer = NULL;

    if (!filename)
        return NULL;
    if (!(fp = fopen(filename, "r")))
        return NULL;
    if (!(buffer = malloc_buffer_from_file_size(fp)))
        return return_and_close(fp, NULL);
    len = get_file_size(fp);
    if ((read = fread(buffer, sizeof(char), len, fp)) != (ssize_t)len) {
        free(buffer);
        return return_and_close(fp, NULL);
    }
    buffer[read] = '\0';
    return return_and_close(fp, buffer);
}

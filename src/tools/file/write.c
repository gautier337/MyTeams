/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** write_file
*/

#include "tools.h"

void write_file(const char *filename, const char *content)
{
    FILE *fp;

    if (!filename || !content)
        exit_error("write_file()");
    fp = fopen(filename, "w+");
    if (fp == NULL)
        exit_error("write_file(): Can't open file");
    fprintf(fp, "%s", content);
    fclose(fp);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** append_file
*/

#include "tools.h"

int append_file(const char *filename, const char *content)
{
    FILE *fp;

    if (!filename || !content)
        return ERROR;
    fp = fopen(filename, "a+");
    if (fp == NULL)
        return ERROR;
    fprintf(fp, "%s", content);
    fclose(fp);
    return SUCCESS;
}

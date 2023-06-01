/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** parsing
*/

#include "myteams.h"

bool go_to_next_quote(char *buffer, int *i)
{
    for (; buffer[*i] != '"'; (*i)++)
        if (buffer[*i] == '\0')
            return false;
    return true;
}

int go_to_next_arg(char *buffer, int *i, int *nb_args)
{
    if (buffer[*i] == '"') {
        (*i)++;
        (*nb_args)++;
        if (!go_to_next_quote(buffer, i))
            return 0;
        return 2;
    }
    if (buffer[*i] != ' ')
        return 0;
    return 1;
}

int get_nb_args(char *buffer)
{
    int i = 0;
    int nb_args = 0;
    int is_valid = true;

    if (!buffer)
        return 0;
    for (; buffer[i] != ' '; i++)
        if (buffer[i] == '\0')
            return 1;
    for (; buffer[i] != '\0'; i++) {
        is_valid = go_to_next_arg(buffer, &i, &nb_args);
        if (!is_valid)
            return 0;
        if (is_valid == 2)
            continue;
    }
    return nb_args + 1;
}

int *init_args_size(int nb_args)
{
    int *args_size = NULL;

    if (nb_args == 0)
        return NULL;
    if (!(args_size = malloc(sizeof(int) * nb_args)))
        return NULL;
    args_size[0] = 0;
    for (int i = 1; i < nb_args; i++)
        args_size[i] = -2;
    return args_size;
}

int *get_args_size(int nb_args, char *buffer)
{
    int *args_size = init_args_size(nb_args);
    int j = 0;
    int in_quote = 0;

    if (!buffer || nb_args == 0 || !args_size)
        return NULL;
    for (int i = 0; buffer[i] != '\0' && j < nb_args; ) {
        if (buffer[i] == '"')
            in_quote = !in_quote;
        if (buffer[i] == ' ' && !in_quote) {
            i++;
            continue;
        }
        args_size[j]++;
        i++;
        if (buffer[i] == '\0' || (buffer[i] == ' ' && !in_quote))
            j++;
    }
    return args_size;
}

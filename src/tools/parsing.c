/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** parsing
*/

#include "myteams.h"

char **my_parse_args(char *buffer)
{
    char **args = NULL;
    int j = 0;
    int nb_args = get_nb_args(buffer);
    int *args_size = get_args_size(nb_args, buffer);

    if (!buffer || nb_args == 0 || !args_size)
        return NULL;
    if (!(args = my_init_array(nb_args)))
        return NULL;
    for (int i = 0; i < nb_args; i++) {
        args[i] = strndup(buffer + j + (i == 0 ? 0 : 1), args_size[i]);
        j += args_size[i] + (i == 0 ? 1 : 3);
    }
    free(args_size);
    return args;
}

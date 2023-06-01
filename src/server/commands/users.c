/*
** EPITECH PROJECT, 2023
** users cmd
** File description:
** users
*/

#include "myteams.h"

void users_command(server_t *server, client_t *client, const char **params)
{
    char *file_content_users = NULL;

    if (!server || !client || !params)
        exit_error("users_command()");
    if (!(file_content_users = read_file(USERS_LIST_PATH)))
        return;
    send_to_user(client, file_content_users);
    free(file_content_users);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** help.c
*/

#include "myteams.h"

void help_command(server_t *server, client_t *client,
    const char **params)
{
    char *file_content = NULL;

    (void)server;
    (void)params;
    if (!client)
        exit_error("help_command()");
    file_content = read_file("server_helper");
    if (!file_content)
        return send_to_user(client, API_NO_CONTENT);
    send_to_user(client, file_content);
    free(file_content);
}

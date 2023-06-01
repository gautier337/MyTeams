/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** command_manager.c
*/

#include "myteams.h"
#include <string.h>

void remove_crlf(char *str)
{
    int param_length = 0;

    if (!str)
        return;
    param_length = my_strlen(str);
    if (str[param_length - 1] == '\n')
        str[param_length - 1] = '\0';
    if (str[param_length - 2] == '\r')
        str[param_length - 2] = '\0';
}

bool is_authorized_command(client_t *client, const char *command)
{
    const server_command_t commands[] = SERVER_COMMANDS;
    bool is_known_command = false;

    if (client->is_logged_in)
        return true;
    for (int i = 0; i < SERVER_COMMANDS_COUNT; i++) {
        if (!my_strncasecmp(
            commands[i].name, command, my_strlen(commands[i].name)))
            is_known_command = true;
    }
    if (!is_known_command)
        return true;
    if (!strcasecmp(command, "/login") || !strcasecmp(command, "/help"))
        return true;
    send_to_user(client, API_UNAUTHORIZED);
    return false;
}

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++) {
        if (array[i] != NULL)
            free(array[i]);
    }
    free(array);
}

void command_manager(server_t *server, client_t *client)
{
    int ret = -1;
    char **params = NULL;
    const server_command_t commands[] = SERVER_COMMANDS;

    if (!client || !client->buffer)
        exit_error("command_manager()");
    remove_crlf(client->buffer);
    if (!(params = my_parse_args(client->buffer)) || !params[0])
        return send_to_user(client, API_NOT_FOUND);
    for (int i = 0; i < SERVER_COMMANDS_COUNT; i++) {
        if (!is_authorized_command(client, params[0]))
            return free_array(params);
        if (!my_strcasecmp(commands[i].name, params[0])) {
            commands[i].function(server, client, (const char **)params);
            ret = 0;
            break;
        }
    }
    free_array(params);
    ret == -1 ? send_to_user(client, API_NOT_FOUND) : 0;
}

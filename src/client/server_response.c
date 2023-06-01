/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** server_response
*/

#include "myteams.h"

bool handle_default_response_2(client_t *client, char *response)
{
    if (!client)
        exit_error("handle_default_response()");
    if (!strncmp(API_NOT_FOUND, response, 3)) {
        my_printf("Unknown command (check /help)\r\n");
        return true;
    }
    return false;
}

bool handle_default_response(client_t *client, char *response)
{
    if (!client)
        exit_error("handle_default_response()");
    if (!response)
        return false;
    if (!strncmp(API_UNAUTHORIZED, response, 3)) {
        client_error_unauthorized();
        return true;
    }
    if (!strncmp(API_NOTIFIED, response, 3)) {
        handle_notification(client, response);
        return true;
    }
    if (!strncmp(API_LOG_EVENT, response, 3))
        return handle_log_events(client, response);
    if (!strncmp(API_REPLY_EVENT, response, 3))
        return handle_reply_events(client, response);
    return handle_default_response_2(client, response);
}

void handle_server_response(client_t *client, char *response)
{
    const client_command_t commands[] = CLIENT_COMMANDS;
    char *command = NULL;

    if (!client)
        exit_error("handle_server_response()");
    if (!response)
        return;
    if (!client->buffer) {
        my_printf("%s", response);
        return;
    }
    command = strtok(client->buffer, " \n");
    for (int i = 0; i < CLIENT_COMMANDS_COUNT; i++) {
        if (handle_default_response(client, response))
            return;
        if (!strcasecmp(commands[i].name, command)) {
            commands[i].function(client, response);
            return;
        }
    }
}

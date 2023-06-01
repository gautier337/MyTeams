/*
** EPITECH PROJECT, 2023
** subscribe
** File description:
** subscribe
*/

#include "myteams.h"

bool handle_subscribe_errors(client_t *client,
    const char *response, char *team_uuid)
{
    if (!client || !response)
        return false;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax. Please use: /subscribe \"team_uuid\"\r\n");
        return false;
    }
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        client_error_unknown_team(team_uuid);
        return false;
    }
    if (!strncmp(API_METHOD_NOT_ALLOWED, response, 3)) {
        my_printf("You are already subscribed to this team.\r\n");
        return false;
    }
    return true;
}

void subscribe_client(client_t *client, const char *response)
{
    char *team_uuid = NULL;
    char *user_uuid = NULL;

    team_uuid = strtok((char *)response, ",");
    user_uuid = strtok(NULL, ",");
    if (!handle_subscribe_errors(client, response, team_uuid))
        return;
    if (!team_uuid || !user_uuid) {
        my_printf("Error response from server.\r\n");
        return;
    }
    client_print_subscribed(user_uuid, team_uuid);
}

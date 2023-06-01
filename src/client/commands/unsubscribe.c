/*
** EPITECH PROJECT, 2023
** unsubscribe
** File description:
** unsubscribe
*/

#include "myteams.h"

bool handle_unsubscribe_errors(client_t *client,
    const char *response, char *team_uuid)
{
    if (!client || !response)
        return false;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax.Please use: /unsubscribe 'team_uuid'\r\n");
        return false;
    }
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        client_error_unknown_team(team_uuid);
        return false;
    }
    if (!strncmp(API_METHOD_NOT_ALLOWED, response, 3)) {
        my_printf("You are not subscribed to this team.\r\n");
        return false;
    }
    return true;
}

void unsubscribe_client(client_t *client, const char *response)
{
    char *team_uuid = NULL;
    char *user_uuid = NULL;

    team_uuid = strtok((char *)response, ",");
    user_uuid = strtok(NULL, ",");
    if (!handle_unsubscribe_errors(client, response, team_uuid))
        return;
    client_print_unsubscribed(user_uuid, team_uuid);
}

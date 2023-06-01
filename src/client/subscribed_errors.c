/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** subscribed_errors
*/

#include "myteams.h"

bool handle_susbcribed_errors_teams(client_t *client, char *data)
{
    if (!client)
        return false;
    if (!strncmp(API_NO_CONTENT, data, 3)) {
        my_printf("No subscribed teams.\r\n");
        return true;
    }
    return false;
}

bool handle_susbcribed_errors_users(client_t *client, char *data)
{
    char *team_uuid = NULL;

    if (!client)
        return true;
    if (!strncmp(API_NOT_FOUND, data, 3)) {
        strtok(data, ",");
        team_uuid = strtok(NULL, "\0");
        client_error_unknown_team(team_uuid);
        return true;
    }
    if (!strncmp(API_NO_CONTENT, data, 3)) {
        my_printf("No subscribed users.\r\n");
        return true;
    }
    return false;
}

bool handle_subscribed_errors(client_t *client, int context, char *data)
{
    if (!client)
        return true;
    if (!strncmp(API_INVALID_SYNTAX, data, 3)) {
        my_printf(
            "Invalid syntax. Please use: /subscribed ?\"team_uuid\"\r\n");
        return true;
    }
    switch (context) {
        case 0:
            return handle_susbcribed_errors_teams(client, data);
        case 1:
            return handle_susbcribed_errors_users(client, data);
        default:
            return false;
    }
    return false;
}

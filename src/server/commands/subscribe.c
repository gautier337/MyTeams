/*
** EPITECH PROJECT, 2023
** subscribe
** File description:
** subscribe
*/

#include "myteams.h"

void add_user_uuid_to_users_file_of_the_team(char *team_uuid, char *user_uuid)
{
    char *file_path = NULL;

    if (!team_uuid || !user_uuid)
        return;
    file_path = msprintf("data/teams/%s/users.csv", team_uuid);
    append_file(file_path, user_uuid);
    append_file(file_path, "\n");
    free(file_path);
}

void subscribe_command(server_t *server, client_t *client,
        const char **params)
{
    char *response = NULL;

    if (!server || !client || !params)
        return;
    if (!params[1])
        return send_to_user(client, API_INVALID_SYNTAX);
    if (!does_team_exist(params[1]))
        return send_to_user(client, API_NO_CONTENT);
    if (check_if_user_is_subscribe_to_the_team((char *)params[1],
        client->user_uuid))
        return send_to_user(client, API_METHOD_NOT_ALLOWED);
    if (!(response = msprintf("%s,%s", params[1], client->user_uuid)))
        return send_to_user(client, API_INTERNAL_ERROR);
    add_user_uuid_to_users_file_of_the_team((char *)params[1],
        client->user_uuid);
    server_event_user_subscribed(params[1], client->user_uuid);
    send_to_user(client, response);
    free(response);
}

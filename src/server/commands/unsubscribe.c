/*
** EPITECH PROJECT, 2023
** unsubscribe
** File description:
** unsubscribe
*/

#include "myteams.h"

void remove_user_from_team_file(FILE *file, char *file_content,
    char *user_uuid)
{
    char *line = NULL;
    char *saveptr;

    if (!file || !file_content || !user_uuid)
        return;

    line = strtok_r(file_content, "\n", &saveptr);
    while (line) {
        if (strcmp(line, user_uuid))
            fprintf(file, "%s\n", line);
        line = strtok_r(NULL, "\n", &saveptr);
    }
}

void unsubscribe_user_in_users_of_a_team(char *team_uuid, char *user_uuid)
{
    char *file_path = NULL;
    char *file_content = NULL;
    FILE *file;

    if (!team_uuid || !user_uuid)
        return;
    if (!(file_path = msprintf("data/teams/%s/users.csv", team_uuid)))
        return;
    if (!(file_content = read_file(file_path))) {
        free(file_path);
        return;
    }
    file = fopen(file_path, "w");
    if (!file) {
        free(file_path);
        free(file_content);
        return;
    }
    remove_user_from_team_file(file, file_content, user_uuid);
    fclose(file);
}

void unsubscribe_command(server_t *server, client_t *client,
        const char **params)
{
    char *response = NULL;

    if (!server || !client || !params)
        return;
    if (!params[1])
        return send_to_user(client, API_INVALID_SYNTAX);
    if (!does_team_exist(params[1]))
        return send_to_user(client, API_NO_CONTENT);
    if (!check_if_user_is_subscribe_to_the_team((char *)params[1],
        client->user_uuid))
        return send_to_user(client, API_METHOD_NOT_ALLOWED);
    server_event_user_unsubscribed(params[1], client->user_uuid);
    unsubscribe_user_in_users_of_a_team((char *)params[1], client->user_uuid);
    response = msprintf("%s,%s", params[1], client->user_uuid);
    if (!response)
        return send_to_user(client, API_INTERNAL_ERROR);
    send_to_user(client, response);
    free(response);
}

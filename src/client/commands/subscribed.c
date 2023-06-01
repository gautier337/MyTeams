/*
** EPITECH PROJECT, 2023
** subscribe
** File description:
** subscribe
*/

#include "myteams.h"

void subscribed_teams(client_t *client, char *data)
{
    char *line = NULL;
    char *line_save_ptr = NULL;
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_description = NULL;

    if (!client || !data)
        return;
    line = strtok_r(data, "\n", &line_save_ptr);
    while (line) {
        team_uuid = strtok(line, ",");
        team_name = strtok(NULL, ",");
        team_description = strtok(NULL, "\n");
        if (!team_uuid || !team_name || !team_description) {
            my_printf("Error response from server.\r\n");
            return;
        }
        client_print_teams(team_uuid, team_name, team_description);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void subscribed_users(client_t *client, char *data)
{
    char *line = NULL;
    char *line_save_ptr = NULL;
    char *user_uuid = NULL;
    char *user_name = NULL;
    char *user_status = NULL;

    if (!client || !data)
        return;
    line = strtok_r(data, "\n", &line_save_ptr);
    while (line) {
        user_name = strtok(line, ",");
        user_uuid = strtok(NULL, ",");
        user_status = strtok(NULL, "\n");
        if (!user_uuid || !user_name || !user_status) {
            my_printf("Error response from server.\r\n");
            return;
        }
        client_print_users(user_uuid, user_name, atoi(user_status));
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void subscribed_client(client_t *client, const char *response)
{
    char *context = NULL;
    char *data = NULL;

    if (!client || !response)
        return;
    context = strtok((char *)response, ",");
    data = strtok(NULL, "\0");
    if (handle_subscribed_errors(client, atoi(context), data))
        return;
    switch (atoi(context)) {
        case 0:
            subscribed_teams(client, data);
            break;
        case 1:
            subscribed_users(client, data);
            break;
        default:
            break;
    }
}

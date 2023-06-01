/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** list
*/

#include "myteams.h"

void list_team_client(client_t *client, char *data)
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
        client_print_teams(team_uuid, team_name, team_description);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void list_channel_client(client_t *client, char *data)
{
    char *line = NULL;
    char *line_save_ptr = NULL;
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;

    if (!client || !data)
        return;
    line = strtok_r(data, "\n", &line_save_ptr);
    while (line) {
        channel_uuid = strtok(line, ",");
        channel_name = strtok(NULL, ",");
        channel_description = strtok(NULL, "\n");
        client_team_print_channels(
            channel_uuid, channel_name, channel_description);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void list_thread_client(client_t *client, char *data)
{
    char *line = NULL;
    char *line_save_ptr = NULL;

    if (!client || !data)
        return;
    line = strtok_r(data, "\n", &line_save_ptr);
    while (line) {
        parse_thread_client(line);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void list_reply_client(client_t *client, char *data)
{
    char *line = NULL;
    char *line_save_ptr = NULL;

    if (!client || !data)
        return;
    line = strtok_r(data, "\n", &line_save_ptr);
    while (line) {
        parse_reply_client(line);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }
}

void list_client(client_t *client, const char *response)
{
    char *context = NULL;
    char *data = NULL;

    if (!client || !response)
        return;
    context = strtok((char *)response, ",");
    data = strtok(NULL, "\0");
    if (handle_api_errors_list(data))
        return;
    if (atoi(context) == NO_CONTEXT)
        return list_team_client(client, data);
    if (atoi(context) == TEAM)
        return list_channel_client(client, data);
    if (atoi(context) == CHANNEL)
        return list_thread_client(client, data);
    if (atoi(context) == THREAD)
        return list_reply_client(client, data);
    exit_error("Unknown context");
}

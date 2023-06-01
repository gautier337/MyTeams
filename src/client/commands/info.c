/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** info
*/

#include "myteams.h"

void info_user_client(client_t *client, char *data)
{
    char *user_uuid = NULL;
    char *user_name = NULL;
    char *user_status = NULL;

    if (!client || !data)
        return;
    user_uuid = strtok(data, ",");
    user_name = strtok(NULL, ",");
    user_status = strtok(NULL, "\n");
    client_print_user(user_uuid, user_name, atoi(user_status));
}

void info_team_client(client_t *client, char *data)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_description = NULL;

    if (!client || !data)
        return;
    team_uuid = strtok(data, ",");
    team_name = strtok(NULL, ",");
    team_description = strtok(NULL, "\n");
    client_print_team(team_uuid, team_name, team_description);
}

void info_channel_client(client_t *client, char *data)
{
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;

    if (!client || !data)
        return;
    channel_uuid = strtok(data, ",");
    channel_name = strtok(NULL, ",");
    channel_description = strtok(NULL, "\n");
    client_print_channel(channel_uuid, channel_name, channel_description);
}

void info_thread_client(client_t *client, char *data)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *thread_timestamp = NULL;
    char *thread_title = NULL;
    char *thread_body = NULL;

    if (!client || !data)
        return;
    thread_uuid = strtok(data, ",");
    user_uuid = strtok(NULL, ",");
    thread_timestamp = strtok(NULL, ",");
    thread_title = strtok(NULL, ",");
    thread_body = strtok(NULL, ",");
    client_print_thread(thread_uuid, user_uuid,
        parse_timestamp(thread_timestamp), thread_title, thread_body);
}

void info_client(client_t *client, const char *response)
{
    char *context = NULL;
    char *data = NULL;

    if (!client || !response)
        return;
    context = strtok((char *)response, ",");
    data = strtok(NULL, "\0");
    if (handle_api_errors_info(data))
        return;
    if (atoi(context) == NO_CONTEXT)
        return info_user_client(client, data);
    if (atoi(context) == TEAM)
        return info_team_client(client, data);
    if (atoi(context) == CHANNEL)
        return info_channel_client(client, data);
    if (atoi(context) == THREAD)
        return info_thread_client(client, data);
    exit_error("Invalid context");
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** create
*/

#include "myteams.h"

void create_team_client(client_t *client, char *data)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_description = NULL;

    if (!client || !data)
        return;
    team_uuid = strtok(data, ",");
    team_name = strtok(NULL, ",");
    team_description = strtok(NULL, ",");
    client_event_team_created(team_uuid, team_name, team_description);
    client_print_team_created(team_uuid, team_name, team_description);
}

void create_channel_client(client_t *client, char *data)
{
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;

    if (!client || !data)
        return;
    channel_uuid = strtok(data, ",");
    channel_name = strtok(NULL, ",");
    channel_description = strtok(NULL, ",");
    client_event_channel_created(
        channel_uuid, channel_name, channel_description);
    client_print_channel_created(
        channel_uuid, channel_name, channel_description);
}

void create_thread_client(client_t *client, char *data)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *thread_timestamp = NULL;
    char *thread_title = NULL;
    char *thread_body = NULL;

    if (!client || !data)
        return;
    my_printf("data: [%s]\n", data);
    thread_uuid = strtok(data, ",");
    user_uuid = strtok(NULL, ",");
    thread_timestamp = strtok(NULL, ",");
    thread_title = strtok(NULL, ",");
    thread_body = strtok(NULL, ",");
    client_event_thread_created(thread_uuid, user_uuid,
        parse_timestamp(thread_timestamp), thread_title, thread_body);
    client_print_thread_created(thread_uuid, user_uuid,
        parse_timestamp(thread_timestamp), thread_title, thread_body);
}

void create_reply_client(client_t *client, char *data)
{
    char *user_uuid = NULL;
    char *thread_uuid = NULL;
    char *reply_body = NULL;
    char *reply_timestamp = NULL;

    if (!client || !data)
        return;
    strtok(data, "¤");
    user_uuid = strtok(NULL, "¤");
    thread_uuid = strtok(NULL, "¤");
    reply_body = strtok(NULL, "¤");
    reply_timestamp = strtok(NULL, "¤");
    client_print_reply_created(thread_uuid, user_uuid,
        parse_timestamp(reply_timestamp), reply_body);
}

void create_fn_client(client_t *client, const char *response)
{
    char *context = NULL;
    char *data = NULL;

    if (!client || !response)
        return;
    context = strtok((char *)response, ",");
    data = strtok(NULL, "\0");
    if (handle_api_errors_create(data, atoi(context)))
        return;
    if (atoi(context) == NO_CONTEXT)
        return create_team_client(client, data);
    if (atoi(context) == TEAM)
        return create_channel_client(client, data);
    if (atoi(context) == CHANNEL)
        return create_thread_client(client, data);
    if (atoi(context) == THREAD)
        return create_reply_client(client, data);
    exit_error("Invalid context");
}

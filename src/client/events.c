/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** events
*/

#include "myteams.h"

bool handle_log_events(client_t *client, char *response)
{
    char *status = NULL;
    char *user_uuid = NULL;
    char *user_name = NULL;

    if (!client || !response)
        exit_error("handle_event()");
    strtok(response, ",");
    status = strtok(NULL, ",");
    user_uuid = strtok(NULL, ",");
    user_name = strtok(NULL, ",");
    if (atoi(status) == 0)
        client_event_logged_out(user_uuid, user_name);
    else
        client_event_logged_in(user_uuid, user_name);
    return true;
}

bool handle_reply_events(client_t *client, char *response)
{
    char *team_uuid = NULL;
    char *user_uuid = NULL;
    char *thread_uuid = NULL;
    char *reply_body = NULL;

    if (!client || !response)
        exit_error("handle_event()");
    strtok(response, "¤");
    team_uuid = strtok(NULL, "¤");
    user_uuid = strtok(NULL, "¤");
    thread_uuid = strtok(NULL, "¤");
    reply_body = strtok(NULL, "¤");
    client_event_thread_reply_received(team_uuid, thread_uuid, user_uuid,
        reply_body);
    return true;
}

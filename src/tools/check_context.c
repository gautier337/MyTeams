/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** check_context
*/

#include "myteams.h"

bool free_and_return(bool return_value, char *str)
{
    if (str)
        free(str);
    return return_value;
}

bool check_context_team(client_t *client)
{
    context_t *c = client->context;
    char *error = NULL;

    if (!does_team_exist(c->team_uuid)) {
        error = msprintf("%s,%s,%s", c->team_uuid, "null", "null");
        send_invalid_context(client, c->type, API_INVALID_CONTEXT, error);
        return free_and_return(true, error);
    }
    return false;
}

bool check_context_channel(client_t *client)
{
    context_t *c = client->context;
    char *error = NULL;
    bool team_exist = true;
    bool channel_exist = true;

    if (!does_team_exist(c->team_uuid))
        team_exist = false;
    if (!does_channel_exist(c->team_uuid, c->channel_uuid))
        channel_exist = false;
    error = msprintf("%s,%s,%s", team_exist ? "null" : c->team_uuid,
        channel_exist ? "null" : c->channel_uuid, "null", "null");
    if (!team_exist || !channel_exist) {
        send_invalid_context(client, c->type, API_INVALID_CONTEXT, error);
        return free_and_return(true, error);
    }
    return free_and_return(false, error);
}

bool check_context_thread(client_t *client)
{
    context_t *c = client->context;
    char *error = NULL;
    bool te = true;
    bool ce = true;
    bool the = true;

    if (!does_team_exist(c->team_uuid))
        te = false;
    if (!does_channel_exist(c->team_uuid, c->channel_uuid))
        ce = false;
    if (!does_thread_exist(c->team_uuid, c->channel_uuid, c->thread_uuid))
        the = false;
    error = msprintf("%s,%s,%s", te ? "null" : c->team_uuid,
        ce ? "null" : c->channel_uuid, the ? "null" : c->thread_uuid);
    if (!te || !ce || !the) {
        send_invalid_context(client, c->type, API_INVALID_CONTEXT, error);
        return free_and_return(true, error);
    }
    return free_and_return(false, error);
}

bool check_context(client_t *client)
{
    enum context_type type = NO_CONTEXT;

    if (!client || !client->context)
        return true;
    type = client->context->type;
    if (type == TEAM)
        return check_context_team(client);
    if (type == CHANNEL)
        return check_context_channel(client);
    if (type == THREAD)
        return check_context_thread(client);
    return false;
}

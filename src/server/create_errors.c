/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** create_errors
*/

#include "myteams.h"

bool handle_errors_create_no_context(client_t *client, const char **params)
{
    if (!client || !params)
        exit_error("handle_errors_create_no_context()");
    if (my_arrlen((char **)params) != 3) {
        send_invalid_context(client, NO_CONTEXT, API_INVALID_SYNTAX, NULL);
        return true;
    }
    if (is_team_in_db(params[1])) {
        send_invalid_context(client, NO_CONTEXT, API_CONFLICT, NULL);
        return true;
    }
    return false;
}

bool handle_errors_create_team(client_t *client, const char **params)
{
    context_t *c = client->context;

    if (my_arrlen((char **)params) != 3) {
        send_invalid_context(client, TEAM, API_INVALID_SYNTAX, NULL);
        return true;
    }
    if (is_channel_in_team(c->team_uuid, params[1])) {
        send_invalid_context(client, TEAM, API_CONFLICT, NULL);
        return true;
    }
    if (!c->team_uuid)
        exit_error("handle_errors_create()");
    return false;
}

bool handle_errors_create_channel(client_t *client, const char **params)
{
    context_t *c = client->context;

    if (my_arrlen((char **)params) != 3) {
        send_invalid_context(client, CHANNEL, API_INVALID_SYNTAX, NULL);
        return true;
    }
    if (is_thread_in_channel(c->team_uuid, c->channel_uuid, params[1])) {
        send_invalid_context(client, CHANNEL, API_CONFLICT, NULL);
        return true;
    }
    if (!c->team_uuid || !c->channel_uuid)
        exit_error("handle_errors_create()");
    return false;
}

bool handle_errors_create_thread(client_t *client, const char **params)
{
    context_t *c = client->context;

    if (my_arrlen((char **)params) != 2) {
        send_invalid_context(client, THREAD, API_INVALID_SYNTAX, NULL);
        return true;
    }
    if (!c->team_uuid || !c->channel_uuid || !c->thread_uuid)
        exit_error("handle_errors_create()");
    return false;
}

bool handle_errors_create(client_t *c, const char **params)
{
    enum context_type type = NO_CONTEXT;

    if (!c || !c->context || !params)
        exit_error("handle_errors_create()");
    type = c->context->type;
    if (type == NO_CONTEXT)
        return handle_errors_create_no_context(c, params);
    if (type == TEAM)
        return handle_errors_create_team(c, params);
    if (type == CHANNEL)
        return handle_errors_create_channel(c, params);
    if (type == THREAD)
        return handle_errors_create_thread(c, params);
    return false;
}

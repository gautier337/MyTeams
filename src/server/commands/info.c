/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** list
*/

#include "myteams.h"

void info_user_command(client_t *client)
{
    char *output = NULL;

    output = msprintf("0,%s,%s,%d",
        client->user_uuid, client->user_name, client->user_status);
    send_to_user(client, output);
    free(output);
}

void info_team_command(client_t *client)
{
    context_t *c = client->context;
    char *infos = NULL;
    char *output = NULL;

    if (!(infos = get_infos_from_context(c->team_uuid, NULL, NULL)))
        return send_invalid_context(client, TEAM, API_NO_CONTENT, NULL);
    output = msprintf("%d,%s,%s", TEAM, c->team_uuid, infos);
    send_to_user(client, output);
    free(output);
    free(infos);
}

void info_channel_command(client_t *client)
{
    context_t *c = client->context;
    char *infos = NULL;
    char *output = NULL;

    if (!(infos = get_infos_from_context(c->team_uuid, c->channel_uuid,
        NULL)))
        return send_invalid_context(client, CHANNEL, API_NO_CONTENT, NULL);
    output = msprintf("%d,%s,%s", CHANNEL, c->channel_uuid, infos);
    send_to_user(client, output);
    free(output);
    free(infos);
}

void info_thread_command(client_t *client)
{
    context_t *c = client->context;
    char *infos = NULL;
    char *output = NULL;

    my_printf("OK\n");
    if (!(infos = get_infos_from_context(c->team_uuid, c->channel_uuid,
        c->thread_uuid)))
        return send_invalid_context(client, c->type, API_NO_CONTENT, NULL);
    output = msprintf("%d,%s,%s,%s", c->type, c->thread_uuid,
        client->user_uuid, infos);
    send_to_user(client, output);
    free(output);
    free(infos);
}

void info_command(server_t *server, client_t *client,
    const char **params)
{
    if (!server || !client || !client->context || !params)
        exit_error("info_command()");
    if (my_arrlen((char **)params) != 1) {
        return send_invalid_context(client, client->context->type,
            API_INVALID_SYNTAX, NULL);
    }
    if (check_context(client))
        return;
    switch (client->context->type) {
        case NO_CONTEXT:
            return info_user_command(client);
        case TEAM:
            return info_team_command(client);
        case CHANNEL:
            return info_channel_command(client);
        case THREAD:
            return info_thread_command(client);
        default:
            return;
    }
}

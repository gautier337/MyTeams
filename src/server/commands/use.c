/*
** EPITECH PROJECT, 2023
** user cmd
** File description:
** use
*/

#include "myteams.h"

void set_new_uuid(char **old_uuid, const char *new_uuid)
{
    if (!old_uuid || !new_uuid)
        exit_error("set_new_uuid()");
    free(*old_uuid);
    *old_uuid = strdup(new_uuid);
}

void set_context(
    client_t *client,
    const char *team_uuid,
    const char *channel_uuid,
    const char *thread_uuid
)
{
    if (!client || !client->context)
        exit_error("set_context()");
    client->context->type = NO_CONTEXT;
    if (team_uuid) {
        client->context->type = TEAM;
        set_new_uuid(&client->context->team_uuid, team_uuid);
    }
    if (channel_uuid) {
        client->context->type = CHANNEL;
        set_new_uuid(&client->context->channel_uuid, channel_uuid);
    }
    if (thread_uuid) {
        client->context->type = THREAD;
        set_new_uuid(&client->context->thread_uuid, thread_uuid);
    }
}

void use_command(server_t *server, client_t *client, const char **params)
{
    int nb_args = my_arrlen((char **)params);

    if (!server || !client || !params)
        exit_error("use_command()");
    if (nb_args > 4)
        return send_to_user(client, API_INVALID_SYNTAX);
    if (nb_args == 1)
        set_context(client, NULL, NULL, NULL);
    if (nb_args == 2)
        set_context(client, params[1], NULL, NULL);
    if (nb_args == 3)
        set_context(client, params[1], params[2], NULL);
    if (nb_args == 4)
        set_context(client, params[1], params[2], params[3]);
    return send_to_user(client, API_SUCCESS);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** create
*/

#include "myteams.h"

void create_team_command(client_t *client, const char **params)
{
    context_t *c = client->context;
    char *team_uuid = NULL;
    char *output = NULL;

    team_uuid = create_team(params[1], params[2]);
    server_event_team_created(team_uuid, params[1], client->user_uuid);
    output = msprintf("%d,%s,%s,%s", c->type, team_uuid, params[1],
        params[2]);
    send_to_user(client, output);
    free(team_uuid);
    free(output);
}

void create_channel_command(client_t *client, const char **params)
{
    context_t *c = client->context;
    char *channel_uuid = NULL;
    char *output = NULL;

    channel_uuid = create_channel(c->team_uuid, params[1], params[2]);
    server_event_channel_created(c->team_uuid, channel_uuid, params[1]);
    output = msprintf("%d,%s,%s,%s", c->type, channel_uuid, params[1],
        params[2]);
    send_to_user(client, output);
    free(channel_uuid);
    free(output);
}

void create_thread_command(client_t *client, const char **params)
{
    context_t *c = client->context;
    char **thread = NULL;
    char *output = NULL;

    thread = create_thread(client, params[1], params[2]);
    server_event_thread_created(c->channel_uuid, thread[0],
        client->user_uuid, params[1], params[2]);
    output = msprintf("%d,%s,%s,%s,%s,%s", c->type, thread[0],
        client->user_uuid, thread[1], params[1], params[2]);
    my_printf("output: [%s]\n", output);
    send_to_user(client, output);
    free_array(thread);
    free(output);
}

void create_reply_command(client_t *client, const char **params)
{
    context_t *c = client->context;
    char *reply_infos = NULL;
    char **reply = NULL;
    char *output = NULL;

    reply = create_reply(client, params[1]);
    server_event_reply_created(c->thread_uuid, client->user_uuid, reply[0]);
    reply_infos = msprintf("%s¤%s¤%s¤%s", c->team_uuid, client->user_uuid,
        c->thread_uuid, reply[0]);
    append_file("data/reply_events.csv", reply_infos);
    free(reply_infos);
    output = msprintf("%d,%s¤%s¤%s¤%s¤%s", c->type, c->team_uuid,
        client->user_uuid, c->thread_uuid, reply[0], reply[1]);
    send_to_user(client, output);
    free_array(reply);
    free(output);
}

void create_command(server_t *server, client_t *client,
    const char **params)
{
    if (!server || !client || !client->context || !params)
        exit_error("create_command()");
    if (check_context(client))
        return;
    if (handle_errors_create(client, params))
        return;
    switch (client->context->type) {
        case NO_CONTEXT:
            return create_team_command(client, params);
        case TEAM:
            return create_channel_command(client, params);
        case CHANNEL:
            return create_thread_command(client, params);
        case THREAD:
            return create_reply_command(client, params);
        default:
            exit_error("Invalid context");
    }
}

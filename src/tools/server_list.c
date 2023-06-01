/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** server_list
*/

#include "myteams.h"

char *create_line_output_from_team(const char *team_uuid)
{
    char *filename = NULL;
    char *file_content = NULL;
    char *team_name = NULL;
    char *team_description = NULL;
    char *line = NULL;

    if (!team_uuid)
        return NULL;
    filename = msprintf("data/teams/%s/infos.csv", team_uuid);
    if (!(file_content = read_file(filename)))
        return NULL;
    team_name = strtok(file_content, ",");
    team_description = strtok(NULL, "\n");
    line = msprintf("%s,%s,%s\n", team_uuid, team_name, team_description);
    free(filename);
    free(file_content);
    return line;
}

char *create_line_output_from_channel(
    client_t *client,
    const char *channel_uuid
)
{
    char *filename = NULL;
    char *file_content = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;
    char *line = NULL;

    if (!client || !client->context || !channel_uuid)
        return NULL;
    filename = msprintf("data/teams/%s/channels/%s/infos.csv",
        client->context->team_uuid, channel_uuid);
    if (!(file_content = read_file(filename)))
        return NULL;
    channel_name = strtok(file_content, ",");
    channel_description = strtok(NULL, "\n");
    line = msprintf("%s,%s,%s\n",
        channel_uuid, channel_name, channel_description);
    free(filename);
    free(file_content);
    return line;
}

char *create_line_output_from_thread(
    client_t *client,
    const char *thread_uuid
)
{
    context_t *c = client->context;
    char *filename = NULL;
    char *file_content = NULL;
    char *line = NULL;

    if (!client || !client->context || !thread_uuid)
        return NULL;
    filename = msprintf("data/teams/%s/channels/%s/threads/%s/infos.csv",
        c->team_uuid, c->channel_uuid, thread_uuid);
    if (!(file_content = read_file(filename)))
        return NULL;
    line = create_line_from_thread_file(client, thread_uuid, file_content);
    free(file_content);
    return line;
}

char *create_line_output_from_reply(
    client_t *client,
    const char *reply_uuid
)
{
    context_t *c = client->context;
    char *reply_dir = NULL;
    char *body = NULL;
    char *timestamp = NULL;
    char *line = NULL;

    if (!client || !client->context || !reply_uuid)
        return NULL;
    reply_dir = msprintf("data/teams/%s/channels/%s/threads/%s/replies/%s",
        c->team_uuid, c->channel_uuid, c->thread_uuid, reply_uuid);
    body = get_data_from_folder_file(reply_dir, "body.txt");
    timestamp = get_data_from_folder_file(reply_dir, "timestamp.txt");
    line = msprintf("%s^%s^%s^%s\n", c->thread_uuid, client->user_uuid,
        timestamp, body);
    free(reply_dir);
    free(body);
    free(timestamp);
    return line;
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** threads
*/

#include "myteams.h"
#include <dirent.h>

char **reply_data_to_array(char *reply_body, char *reply_timestamp)
{
    char **reply_data = NULL;

    if (!reply_body || !reply_timestamp)
        exit_error("reply_data_to_array()");
    if (!(reply_data = malloc(sizeof(char *) * 3)))
        exit_error("malloc()");
    reply_data[0] = reply_body;
    reply_data[1] = reply_timestamp;
    reply_data[2] = NULL;
    return reply_data;
}

char *create_reply_directory(context_t *c, const char *reply_uuid)
{
    DIR *dir = NULL;
    char *thread_dir = NULL;
    char *reply_dir = NULL;

    thread_dir = msprintf("data/teams/%s/channels/%s/threads/%s/replies",
        c->team_uuid, c->channel_uuid, c->thread_uuid);
    if (!(dir = opendir(thread_dir)))
        mkdir(thread_dir, 0777);
    reply_dir = msprintf("%s/%s", thread_dir, reply_uuid);
    mkdir(reply_dir, 0777);
    free(thread_dir);
    return reply_dir;
}

void free_reply_data(char *file_body, char *file_timestamp, char *reply_dir)
{
    if (file_body)
        free(file_body);
    if (file_timestamp)
        free(file_timestamp);
    if (reply_dir)
        free(reply_dir);
}

char **create_reply(
    client_t *client,
    const char *reply_body
)
{
    context_t *c = NULL;
    char *reply_dir = NULL;
    char *reply_uuid = NULL;
    char *reply_time = NULL;
    char *reply_file_body = NULL;
    char *reply_file_timestamp = NULL;

    if (!client || !reply_body)
        exit_error("create_reply()");
    c = client->context;
    reply_uuid = generate_uuid();
    reply_dir = create_reply_directory(c, reply_uuid);
    reply_file_body = msprintf("%s/body.txt", reply_dir);
    reply_file_timestamp = msprintf("%s/timestamp.txt", reply_dir);
    reply_time = timestamp_to_str(get_timestamp());
    write_file(reply_file_body, reply_body);
    write_file(reply_file_timestamp, reply_time);
    free_reply_data(reply_file_body, reply_file_timestamp, reply_dir);
    return reply_data_to_array(strdup(reply_body), reply_time);
}

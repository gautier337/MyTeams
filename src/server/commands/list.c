/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** list
*/

#include "myteams.h"

void list_team_command(client_t *client)
{
    DIR *dir = NULL;
    char *line = NULL;
    char *data = NULL;

    if (!(dir = get_dir_and_error(client, "data/teams")))
        return;
    rewinddir(dir);
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR)
            continue;
        if (!(line = create_line_output_from_team(entry->d_name)))
            continue;
        add_line_to_data(&data, line, NO_CONTEXT);
    }
    send_list_output(client, data);
    closedir(dir);
}

void list_channel_command(client_t *client)
{
    DIR *dir = NULL;
    char *c_dir = NULL;
    char *line = NULL;
    char *data = NULL;

    c_dir = msprintf("data/teams/%s/channels", client->context->team_uuid);
    if (!(dir = get_dir_and_error(client, c_dir)))
        return free(c_dir);
    free(c_dir);
    rewinddir(dir);
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR)
            continue;
        if (!(line = create_line_output_from_channel(client, entry->d_name)))
            continue;
        add_line_to_data(&data, line, TEAM);
    }
    send_list_output(client, data);
    closedir(dir);
}

void list_thread_command(client_t *client)
{
    context_t *c = client->context;
    DIR *dir = NULL;
    char *th_dir = NULL;
    char *line = NULL;
    char *data = NULL;

    th_dir = msprintf("data/teams/%s/channels/%s/threads", c->team_uuid,
        c->channel_uuid);
    if (!(dir = get_dir_and_error(client, th_dir)))
        return free(th_dir);
    free(th_dir);
    rewinddir(dir);
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR ||
            !(line = create_line_output_from_thread(client, entry->d_name)))
            continue;
        add_line_to_data(&data, line, CHANNEL);
    }
    send_list_output(client, data);
    closedir(dir);
}

void list_reply_command(client_t *client)
{
    context_t *c = client->context;
    DIR *dir = NULL;
    char *th_dir = NULL;
    char *line = NULL;
    char *data = NULL;

    th_dir = msprintf("data/teams/%s/channels/%s/threads/%s/replies",
        c->team_uuid, c->channel_uuid, c->thread_uuid);
    if (!(dir = get_dir_and_error(client, th_dir)))
        return free(th_dir);
    free(th_dir);
    rewinddir(dir);
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR ||
            !(line = create_line_output_from_reply(client, entry->d_name)))
            continue;
        add_line_to_data(&data, line, THREAD);
    }
    send_list_output(client, data);
    closedir(dir);
}

void list_command(server_t *server, client_t *client,
    const char **params)
{
    if (!server || !client || !client->context || !params)
        exit_error("list_command()");
    if (my_arrlen((char **)params) != 1) {
        return send_invalid_context(client, client->context->type,
            API_INVALID_SYNTAX, NULL);
    }
    if (check_context(client))
        return;
    switch (client->context->type) {
        case NO_CONTEXT:
            return list_team_command(client);
        case TEAM:
            return list_channel_command(client);
        case CHANNEL:
            return list_thread_command(client);
        case THREAD:
            return list_reply_command(client);
        default:
            exit_error("Invalid context");
    }
}

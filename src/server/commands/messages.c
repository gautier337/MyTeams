/*
** EPITECH PROJECT, 2023
** messages cmd
** File description:
** messages
*/

#include "myteams.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char *get_path_to_messages(const char *asked_uuid, const char *asker_uuid)
{
    const char *base_path = "data/private_messages";
    char *asked_uuid_path = NULL;
    char *path = NULL;

    if (!asked_uuid || !asker_uuid)
        return NULL;
    if (!directory_exists(base_path))
        return NULL;
    asked_uuid_path = msprintf("%s/%s", base_path, asked_uuid);
    if (!directory_exists(asked_uuid_path)) {
        free(asked_uuid_path);
        return NULL;
    }
    if (!file_exists(path = msprintf("%s/%s", asked_uuid_path, asker_uuid))) {
        free(path);
        free(asked_uuid_path);
        return NULL;
    }
    free(asked_uuid_path);
    return path;
}

char *get_messages_content(const char *asked_uuid, const char *asker_uuid)
{
    char *path = NULL;
    char *content = NULL;

    if (!asked_uuid || !asker_uuid)
        return NULL;
    path = get_path_to_messages(asked_uuid, asker_uuid);
    if (!path)
        return NULL;
    content = read_file(path);
    free(path);
    return content;
}

char *append_uuids_to_content(char *content, const char *asked_uuid,
    const char *asker_uuid)
{
    size_t content_len = 0;
    size_t new_content_size = 0;

    if (!content)
        return NULL;
    content_len = strlen(content);
    new_content_size = content_len + strlen(asked_uuid) +
        strlen(asker_uuid) + 5;
    content = realloc(content, new_content_size);
    if (!content)
        return NULL;
    snprintf(content + content_len, new_content_size - content_len,
        "\n\n\n%s\n%s", asked_uuid, asker_uuid);
    return content;
}

char *get_messages_exchange_with_user(const char *asked_uuid,
    const char *asker_uuid)
{
    char *content = get_messages_content(asked_uuid, asker_uuid);
    content = append_uuids_to_content(content, asked_uuid, asker_uuid);
    return content;
}

void messages_command(server_t *server, client_t *client,
    const char **params)
{
    char *file_content_users = NULL;
    char *response_messages = NULL;

    if (!server || !client || !params)
        exit_error("user_command()");
    if (!params[1])
        return send_to_user(client, API_INVALID_SYNTAX);
    response_messages = get_messages_exchange_with_user(params[1],
        client->user_uuid);
    if (!response_messages)
        return send_to_user(client, API_NO_CONTENT);
    send_to_user(client, response_messages);
    if (file_content_users)
        free(file_content_users);
    if (response_messages)
        free(response_messages);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** send.c
*/

#include "myteams.h"
#include <sys/stat.h>
#include <stdbool.h>

void free_pointers(char *sender_dir, char *receiver_dir, char *sender_file,
    char *receiver_file)
{
    free(sender_dir);
    free(receiver_dir);
    free(sender_file);
    free(receiver_file);
}

void save_message(const char *sender_uuid, const char *receiver_uuid,
    const char *message, char *timestamp)
{
    char *sender_dir = msprintf("./data/private_messages/%s", sender_uuid);
    char *receiver_dir = msprintf("./data/private_messages/%s",
        receiver_uuid);
    char *sender_file = msprintf("%s/%s", sender_dir, receiver_uuid);
    char *receiver_file = msprintf("%s/%s", receiver_dir, sender_uuid);
    char *formatted_message = msprintf("S, %s, %s\n", timestamp, message);

    if (create_directory_if_not_exists(sender_dir)
        && create_directory_if_not_exists(receiver_dir)) {
        append_file(sender_file, formatted_message);
        formatted_message[0] = 'R';
        append_file(receiver_file, formatted_message);
    }
    free_pointers(sender_dir, receiver_dir, sender_file, receiver_file);
    free(formatted_message);
}

void create_message_tmp(client_t *client, const char **params)
{
    char *timestamp = NULL;
    char *message = NULL;

    timestamp = timestamp_to_str(get_timestamp());
    save_message(client->user_uuid, params[1], params[2], timestamp);
    message = msprintf("%s,%s,%s,%s\n", params[1],
        client->user_uuid, timestamp, params[2]);
    append_file("./data/messages.csv", message);
    server_event_private_message_sended(
        client->user_uuid, params[1], params[2]);
    send_to_user(client, API_SUCCESS);
    free(timestamp);
    free(message);
}

void send_command(server_t *server, client_t *client, const char **params)
{
    if (!server || !client || !params)
        exit_error("send_command()");
    if (!params[1] || !params[2] || my_arrlen((char **)params) != 3)
        return send_to_user(client, API_INVALID_SYNTAX);
    if (!is_uuid_in_db(params[1]))
        return send_to_user(client, API_NO_CONTENT);
    if (my_strlen(params[2]) > MAX_BODY_LENGTH)
        return send_to_user(client, API_INVALID_SYNTAX);
    create_message_tmp(client, params);
}

/*
** EPITECH PROJECT, 2023
** MyTeams [WSL: Ubuntu]
** File description:
** parse_client_data
*/

#include "myteams.h"

void parse_thread_client(char *line)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *thread_timestamp;
    char *thread_title = NULL;
    char *thread_body = NULL;

    if (!line)
        return;
    thread_uuid = strtok(line, ",");
    user_uuid = strtok(NULL, ",");
    thread_timestamp = strtok(NULL, ",");
    thread_title = strtok(NULL, ",");
    thread_body = strtok(NULL, "\n");
    client_channel_print_threads(thread_uuid, user_uuid,
        parse_timestamp(thread_timestamp), thread_title, thread_body);
}

void parse_reply_client(char *line)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *timestamp = NULL;
    char *body = NULL;

    if (!line)
        return;
    thread_uuid = strtok(line, "^");
    user_uuid = strtok(NULL, "^");
    timestamp = strtok(NULL, "^");
    body = strtok(NULL, "\0");
    client_thread_print_replies(thread_uuid, user_uuid,
        parse_timestamp(timestamp), body);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** messages
*/

#include "myteams.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void process_line(char *line, const char *receiver_uuid,
    const char *sender_uuid)
{
    char direction;
    char timestamp_str[20];
    char message_body[256];

    if (sscanf(line, "%c, %19[^,], %255[^\n]", &direction,
        timestamp_str, message_body) != 3)
        return;

    time_t message_timestamp = parse_timestamp(timestamp_str);
    if (message_timestamp == -1) {
        printf("Invalid timestamp: %s\r", timestamp_str);
        return;
    }
    if (direction == 'S')
        client_private_message_print_messages(sender_uuid,
            message_timestamp, message_body);
    else if (direction == 'R')
        client_private_message_print_messages(receiver_uuid,
            message_timestamp, message_body);
}

char **split_response_into_lines(char *response, int *line_count)
{
    char **lines = NULL;
    int current_line = 0;
    char *line = NULL;

    *line_count = 0;
    for (int i = 0; response[i] != '\0'; i++)
        if (response[i] == '\n')
            (*line_count)++;
    lines = malloc((*line_count + 1) * sizeof(char *));
    if (!lines)
        return NULL;
    line = strtok(response, "\n");
    while (line) {
        lines[current_line++] = line;
        line = strtok(NULL, "\n");
    }
    lines[current_line] = NULL;
    return lines;
}

void parse_response(client_t *client, char *response)
{
    int line_count = 0;
    char **lines = split_response_into_lines(response, &line_count);

    (void)client;
    if (!lines)
        return;
    for (int i = 0; i < line_count - 3; i++)
        process_line(lines[i], lines[line_count - 3],
            lines[line_count - 4]);
    if (lines)
        free(lines);
}

void messages_client(client_t *client, const char *response)
{
    char *response_copy = NULL;
    if (!client || !response)
        return;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("API Invalid syntax.\n");
        my_printf("Please use: /messages [user_uuid]\r\n");
        return;
    }
    if (!strncmp(API_NO_CONTENT, response, 3)) {
        my_printf("API NO CONTENT.\r\n");
        return;
    }
    response_copy = strdup(response);
    if (!response_copy)
        return;
    parse_response(client, response_copy);
    if (response_copy)
        free(response_copy);
}

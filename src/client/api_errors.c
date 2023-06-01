/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** api_errors
*/

#include "myteams.h"

bool handle_api_errors_invalid_context(const char *response)
{
    char *team_uuid = NULL;
    char *channel_uuid = NULL;
    char *thread_uuid = NULL;

    if (!response)
        return true;
    if (!strncmp(API_INVALID_CONTEXT, response, 3)) {
        strtok((char *)response, ",");
        team_uuid = strtok(NULL, ",");
        channel_uuid = strtok(NULL, ",");
        thread_uuid = strtok(NULL, "\0");
        if (strcmp(team_uuid, "null"))
            client_error_unknown_team(team_uuid);
        if (strcmp(channel_uuid, "null"))
            client_error_unknown_channel(channel_uuid);
        if (strcmp(thread_uuid, "null"))
            client_error_unknown_thread(thread_uuid);
        return true;
    };
    return false;
}

bool handle_api_errors_create(
    const char *response, enum context_type context)
{
    if (!response)
        return true;
    if (!strncmp(API_CONFLICT, response, 3)) {
        client_error_already_exist();
        return true;
    }
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax.\nPlease use: /create ");
        if (context == NO_CONTEXT)
            my_printf("\"team_name\" \"team_description\"\r\n");
        if (context == TEAM)
            my_printf("\"channel_name\" \"channel_description\"\r\n");
        if (context == CHANNEL)
            my_printf("\"thread_title\" \"thread_body\"\r\n");
        if (context == THREAD)
            my_printf("\"reply_body\"\r\n");
        return true;
    }
    return handle_api_errors_invalid_context(response);
}

bool handle_api_errors_list(const char *response)
{
    if (!response)
        return true;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax.\nPlease use: /list\n");
        return true;
    }
    if (!strncmp(API_NO_CONTENT, response, 3))
        return true;
    return handle_api_errors_invalid_context(response);
}

bool handle_api_errors_info(const char *response)
{
    if (!response)
        return true;
    if (!strncmp(API_INVALID_SYNTAX, response, 3)) {
        my_printf("Invalid syntax.\nPlease use: /info\n");
        return true;
    }
    if (!strncmp(API_NO_CONTENT, response, 3))
        return true;
    return handle_api_errors_invalid_context(response);
}

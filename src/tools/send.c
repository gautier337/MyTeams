/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** send
*/

#include "myteams.h"

char *msprintf(const char *format, ...)
{
    char *str = NULL;
    va_list args;
    int len = 0;

    va_start(args, format);
    len = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (len >= 0) {
        str = malloc(len + 1);
        if (str) {
            va_start(args, format);
            vsnprintf(str, len + 1, format, args);
            va_end(args);
        }
    }
    return str;
}

void send_to_user(client_t *client, char *buffer)
{
    if (!client)
        exit_error("send_to_user()");
    if (!buffer)
        return;
    if (send(client->sockfd, buffer, strlen(buffer), 0) < 0)
        exit_error("send()");
}

void send_invalid_context(
    client_t *client,
    enum context_type context,
    char *api_code,
    char *data
)
{
    char *buffer = NULL;

    if (!client || !api_code)
        exit_error("send_to_user_invalid_data()");
    if (data)
        buffer = msprintf("%d,%s,%s", context, api_code, data);
    else
        buffer = msprintf("%d,%s", context, api_code);
    send_to_user(client, buffer);
    free(buffer);
}

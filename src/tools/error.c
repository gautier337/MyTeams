/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** error
*/

#include"myteams.h"

void exit_error(char *str)
{
    perror(str);
    exit(ERROR);
}

DIR *get_dir_and_error(client_t *client,const char *folder)
{
    DIR *dir = NULL;

    if (!(dir = opendir(folder)) || is_empty_dir(dir)) {
        send_invalid_context(client, client->context->type,
            API_NO_CONTENT, NULL);
        closedir(dir);
        return NULL;
    }
    return dir;
}

void send_list_output(client_t *client, char *data)
{
    if (!client || !client->context)
        exit_error("send_list_output()");
    if (!data)
        return send_invalid_context(
            client, client->context->type, API_NO_CONTENT, NULL);
    send_to_user(client, data);
    free(data);
}

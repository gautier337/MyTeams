/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** notification
*/

#include "myteams.h"

void handle_notification(client_t *client, char *response)
{
    char *receiver_uuid = NULL;
    char *sender_uuid = NULL;
    char *timestamp = NULL;
    char *message = NULL;

    if (!client)
        exit_error("handle_notification()");
    if (!response)
        return;
    response += 9;
    receiver_uuid = strtok(response, ",");
    sender_uuid = strtok(NULL, ",");
    timestamp = strtok(NULL, ",");
    message = strtok(NULL, ",");
    (void)receiver_uuid;
    (void)timestamp;
    client_event_private_message_received(sender_uuid, message);
}

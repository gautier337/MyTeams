/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** uuid
*/

#include "myteams.h"

char *generate_uuid(void)
{
    uuid_t uuid = {0};
    char *uuid_str = NULL;

    uuid_generate(uuid);
    uuid_str = malloc(sizeof(char) * 37);
    uuid_unparse(uuid, uuid_str);
    return uuid_str;
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** context
*/

#include "myteams.h"

char *get_dir_from_context(
    char *team_uuid,
    char *channel_uuid,
    char *thread_uuid
)
{
    if (team_uuid && channel_uuid && thread_uuid)
        return msprintf("data/teams/%s/channels/%s/threads/%s",
            team_uuid, channel_uuid, thread_uuid);
    if (team_uuid && channel_uuid)
        return msprintf("data/teams/%s/channels/%s", team_uuid, channel_uuid);
    else if (team_uuid)
        return msprintf("data/teams/%s", team_uuid);
    return NULL;
}

char *get_infos_from_context(
    char *team_uuid,
    char *channel_uuid,
    char *thread_uuid
)
{
    char *dir = NULL;
    char *filename = NULL;
    char *infos = NULL;

    if (!team_uuid)
        return NULL;
    dir = get_dir_from_context(team_uuid, channel_uuid, thread_uuid);
    filename = msprintf("%s/%s", dir, "infos.csv");
    if (!(infos = read_file(filename)))
        return NULL;
    free(filename);
    if (infos[strlen(infos) - 1] == '\n')
        infos[strlen(infos) - 1] = '\0';
    return infos;
}

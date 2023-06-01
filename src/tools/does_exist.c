/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** does_exist
*/

#include "myteams.h"

bool does_team_exist(const char *team_uuid)
{
    DIR *dir = NULL;
    char *team_path = NULL;

    if (!team_uuid)
        return false;
    team_path = msprintf("data/teams/%s", team_uuid);
    if (!(dir = opendir(team_path)))
        return false;
    free(team_path);
    closedir(dir);
    return true;
}

bool does_channel_exist(const char *team_uuid, const char *channel_uuid)
{
    DIR *dir = NULL;
    char *channel_path = NULL;

    if (!team_uuid || !channel_uuid)
        return false;
    channel_path = msprintf("data/teams/%s/channels/%s",
        team_uuid, channel_uuid);
    if (!(dir = opendir(channel_path)))
        return false;
    free(channel_path);
    closedir(dir);
    return true;
}

bool does_thread_exist(
    const char *team_uuid,
    const char *channel_uuid,
    const char *thread_uuid
)
{
    DIR *dir = NULL;
    char *thread_path = NULL;

    if (!team_uuid || !channel_uuid || !thread_uuid)
        return false;
    thread_path = msprintf("data/teams/%s/channels/%s/threads/%s",
        team_uuid, channel_uuid, thread_uuid);
    if (!(dir = opendir(thread_path)))
        return false;
    free(thread_path);
    closedir(dir);
    return true;
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** infos_from_uuid
*/

#include "myteams.h"

char *get_team_infos_from_uuid(char *team_uuid)
{
    char *filename = NULL;
    char *file_content = NULL;
    char *team_infos = NULL;

    if (!team_uuid)
        return NULL;
    filename = msprintf("data/teams/%s/infos.csv", team_uuid);
    if (!(file_content = read_file(filename)))
        return NULL;
    free(filename);
    team_infos = msprintf("%s,%s", team_uuid, file_content);
    free(file_content);
    return team_infos;
}

char *get_user_infos_from_uuid(const char *user_uuid)
{
    char *file_content = NULL;
    char *user_infos = NULL;

    if (!user_uuid)
        return NULL;
    if (!(file_content = read_file("data/users.csv")))
        return NULL;
    user_infos = find_user_line(file_content, user_uuid);
    free(file_content);
    return user_infos;
}

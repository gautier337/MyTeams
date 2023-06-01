/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** channels
*/

#include "myteams.h"
#include <dirent.h>

bool is_channel_name_in_file(const char *channel_name, char *filename)
{
    char *file_content = NULL;
    char *channel_name_in_file = NULL;

    if (!channel_name || !filename)
        exit_error("is_channel_name_in_file()");
    if (!(file_content = read_file(filename)))
        return false;
    channel_name_in_file = strtok(file_content, ",");
    if (!channel_name_in_file)
        return false;
    if (!strcmp(channel_name, channel_name_in_file))
        return true;
    free(file_content);
    return false;
}

bool is_channel_in_team(const char *team_uuid, const char *channel_name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char *channels_folder = NULL;
    char *filename = NULL;

    channels_folder = msprintf("data/teams/%s/channels", team_uuid);
    if (!(dir = opendir(channels_folder)))
        return false;
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR)
            continue;
        filename = msprintf("%s/%s/infos.csv",
            channels_folder, entry->d_name);
        if (is_channel_name_in_file(channel_name, filename))
            return return_close_and_free(true, dir, filename);
        free(filename);
    }
    return return_close_and_free(false, dir, NULL);
}

void free_channels_data(
    char *team_folder,
    char *channel_folder,
    char *channel_file,
    char *channel_str
)
{
    if (team_folder)
        free(team_folder);
    if (channel_folder)
        free(channel_folder);
    if (channel_file)
        free(channel_file);
    if (channel_str)
        free(channel_str);
}

char *create_channel(
    const char *team_uuid,
    const char *channel_name,
    const char *channel_description
)
{
    DIR *dir = NULL;
    char *team_dir = NULL;
    char *channel_uuid = NULL;
    char *channel_dir = NULL;
    char *channel_file = NULL;
    char *channel_str = NULL;

    if (!team_uuid || !channel_name || !channel_description)
        exit_error("create_channel()");
    team_dir = msprintf("data/teams/%s/channels", team_uuid);
    if (!(dir = opendir(team_dir)))
        mkdir(team_dir, 0777);
    channel_uuid = generate_uuid();
    channel_dir = msprintf("%s/%s", team_dir, channel_uuid);
    mkdir(channel_dir, 0777);
    channel_file = msprintf("%s/infos.csv", channel_dir);
    channel_str = msprintf("%s,%s\n", channel_name, channel_description);
    write_file(channel_file, channel_str);
    free_channels_data(team_dir, channel_dir, channel_file, channel_str);
    return channel_uuid;
}

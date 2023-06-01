/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** teams
*/

#include "myteams.h"
#include <dirent.h>

bool check_if_user_is_subscribe_to_the_team(char *team_uuid, char *user_uuid)
{
    char *file_path = NULL;
    char *file_content = NULL;
    char *line = NULL;
    bool is_subscribe = false;
    char *saveptr = NULL;

    if (!team_uuid || !user_uuid)
        return false;
    file_path = msprintf("data/teams/%s/users.csv", team_uuid);
    if (!(file_content = read_file(file_path)))
        return false;
    line = strtok_r(file_content, "\n", &saveptr);
    while (line && !is_subscribe) {
        if (!strcmp(line, user_uuid))
            is_subscribe = true;
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(file_path);
    free(file_content);
    return is_subscribe;
}

bool is_team_name_in_file(const char *team_name, char *filename)
{
    char *file_content = NULL;
    char *team_name_in_file = NULL;

    if (!team_name || !filename)
        exit_error("is_team_name_in_file()");
    if (!(file_content = read_file(filename)))
        return false;
    team_name_in_file = strtok(file_content, ",");
    if (!team_name_in_file)
        return false;
    if (!strcmp(team_name, team_name_in_file))
        return true;
    free(file_content);
    return false;
}

bool return_close_and_free(bool ret, DIR *dir, char *filename)
{
    if (filename)
        free(filename);
    if (dir)
        closedir(dir);
    return ret;
}

bool is_team_in_db(const char *team_name)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char *filename = NULL;

    if (!(dir = opendir("data/teams")))
        return false;
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR)
            continue;
        filename = msprintf(
            "data/teams/%s/infos.csv", entry->d_name);
        if (is_team_name_in_file(team_name, filename))
            return return_close_and_free(true, dir, filename);
        free(filename);
    }
    return return_close_and_free(false, dir, NULL);
}

char *create_team(const char *team_name, const char *team_description)
{
    DIR *dir = NULL;
    char *team_uuid = NULL;
    char *team_folder = NULL;
    char *team_file = NULL;
    char *team_str = NULL;

    if (!(dir = opendir("data/teams")))
        mkdir("data/teams", 0777);
    team_uuid = generate_uuid();
    team_folder = msprintf("data/teams/%s", team_uuid);
    mkdir(team_folder, 0777);
    team_file = msprintf("%s/infos.csv", team_folder);
    team_str = msprintf("%s,%s\n", team_name, team_description);
    write_file(team_file, team_str);
    free(team_folder);
    free(team_file);
    free(team_str);
    return team_uuid;
}

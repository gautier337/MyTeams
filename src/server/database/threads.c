/*
** EPITECH PROJECT, 2023
** B-NWP-400-BDX-4-1-myteams-hugo.dubois
** File description:
** threads
*/

#include "myteams.h"
#include <dirent.h>

bool is_thread_name_in_file(const char *thread_name, char *filename)
{
    char *file_content = NULL;
    char *thread_name_in_file = NULL;

    if (!thread_name || !filename)
        exit_error("is_thread_name_in_file()");
    if (!(file_content = read_file(filename)))
        return false;
    thread_name_in_file = strtok(file_content, ",");
    if (!thread_name_in_file)
        return false;
    if (!strcmp(thread_name, thread_name_in_file))
        return true;
    free(file_content);
    return false;
}

bool is_thread_in_channel(
    const char *team_uuid,
    const char *channel_uuid,
    const char *thread_name
)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char *threads_folder = NULL;
    char *filename = NULL;

    threads_folder = msprintf("data/teams/%s/channels/%s/threads",
        team_uuid, channel_uuid);
    if (!(dir = opendir(threads_folder)))
        return false;
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR)
            continue;
        filename = msprintf("%s/%s/infos.csv",
            threads_folder, entry->d_name);
        if (is_thread_name_in_file(thread_name, filename))
            return return_close_and_free(true, dir, filename);
        free(filename);
    }
    return return_close_and_free(false, dir, NULL);
}

char **thread_data_to_array(char *thread_uuid, char *thread_timestamp)
{
    char **thread_data = NULL;

    if (!thread_uuid || !thread_timestamp)
        exit_error("thread_data_to_array()");
    if (!(thread_data = malloc(sizeof(char *) * 3)))
        exit_error("malloc()");
    thread_data[0] = thread_uuid;
    thread_data[1] = thread_timestamp;
    thread_data[2] = NULL;
    return thread_data;
}

char *create_thread_directory(context_t *c, const char *thread_uuid)
{
    DIR *dir = NULL;
    char *channel_dir = NULL;
    char *th_dir = NULL;

    channel_dir = msprintf("data/teams/%s/channels/%s/threads", c->team_uuid,
        c->channel_uuid);
    if (!(dir = opendir(channel_dir)))
        mkdir(channel_dir, 0777);
    th_dir = msprintf("%s/%s", channel_dir, thread_uuid);
    mkdir(th_dir, 0777);
    free(channel_dir);
    return th_dir;
}

char **create_thread(
    client_t *client,
    const char *thread_name,
    const char *thread_message
)
{
    context_t *c = NULL;
    char *th_dir = NULL;
    char *th_uuid = NULL;
    char *th_time = NULL;
    char *th_file = NULL;
    char *th_str = NULL;

    if (!client || !thread_name || !thread_message)
        exit_error("create_channel()");
    c = client->context;
    th_uuid = generate_uuid();
    th_dir = create_thread_directory(c, th_uuid);
    th_file = msprintf("%s/infos.csv", th_dir);
    th_time = timestamp_to_str(get_timestamp());
    th_str = msprintf("%s,%s,%s\n", thread_name, thread_message, th_time);
    write_file(th_file, th_str);
    free(th_dir);
    free(th_file);
    free(th_str);
    return thread_data_to_array(th_uuid, th_time);
}

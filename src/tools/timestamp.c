/*
** EPITECH PROJECT, 2023
** timestamp
** File description:
** timestamp
*/

#include "myteams.h"

time_t get_timestamp(void)
{
    time_t timestamp = time(NULL);
    return timestamp;
}

char *timestamp_to_str(time_t timestamp)
{
    char *str = malloc(sizeof(char) * 20);
    struct tm *time = localtime(&timestamp);

    if (!str)
        exit_error("timestamp_to_str()");
    strftime(str, 20, "%Y-%m-%d %H:%M:%S", time);
    return str;
}

time_t parse_timestamp(const char *timestamp_str)
{
    struct tm tm = {0};
    int year, month, day, hour, minute, second;

    if (sscanf(timestamp_str, "%d-%d-%d %d:%d:%d", &year, &month, &day,
        &hour, &minute, &second) != 6)
        return -1;

    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    return mktime(&tm);
}

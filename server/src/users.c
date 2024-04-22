/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** users
*/

#include "server.h"

void print_this_user(client_t *client, char **cmd)
{
    char path[PATH_MAX];
    char **file = NULL;

    if (!cmd)
        return;
    sprintf(path, "%s%s/user_info.txt", CLIENT_SAVE, cmd[0]);
    file = get_file(path);
    if (file)
        dprintf(client->clientfd, "/user \"%s\" \"%s\" \"%d\"",
            file[1], file[0], (atoi(file[2]) > 0) ? 1 : 0);
    else
        dprintf(client->clientfd, "/error \"user\" \"%s\"", cmd[0]);
    destroy_tab(file);
}

void print_each_user(client_t *client, DIR *d)
{
    struct dirent *dir;
    char **file;
    char path[PATH_MAX];

    dir = readdir(d);
    while (dir) {
        if (dir->d_name[0] == '.') {
            dir = readdir(d);
            continue;
        }
        sprintf(path, "%s%s/user_info.txt", CLIENT_SAVE, dir->d_name);
        file = get_file(path);
        if (file) {
            dprintf(client->clientfd, "/users \"%s\" \"%s\" \"%d\"",
                file[1], file[0], (atoi(file[2]) > 0) ? 1 : 0);
            usleep(100);
        }
        destroy_tab(file);
        dir = readdir(d);
    }
}

void print_users(client_t *client, char **cmd)
{
    DIR *d;
    struct dirent *dir;

    d = opendir(CLIENT_SAVE);
    if (d)
        print_each_user(client, d);
    closedir(d);
}

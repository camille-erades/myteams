/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** list
*/

#include "server.h"

void send_lisnt(client_t *client, char *name, char *path)
{
    char **file;
    int c = 0;
    char file_path[PATH_MAX];

    sprintf(file_path, "%s%s/info.txt", path, name);
    file = get_file(file_path);
    c = count_context(client->context);
    if (file) {
        dprintf(client->clientfd, "/list \"%d\" \"%s\" \"%s\" \"%s\"",
            c, name, file[0], file[1]);
        usleep(100);
    }
    destroy_tab(file);
}

void list(client_t *client, char **cmd)
{
    DIR *d;
    struct dirent *dir;
    char path[PATH_MAX];

    strcpy(path, TEAM_SAVE);
    strcat(path, client->context);
    d = opendir(path);
    if (!d)
        return;
    dir = readdir(d);
    while (dir) {
        if (dir->d_name[0] != '.' && strcmp(dir->d_name, "info.txt"))
            send_lisnt(client, dir->d_name, path);
        dir = readdir(d);
    }
    closedir(d);
}

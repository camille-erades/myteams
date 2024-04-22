/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** log
*/

#include "server.h"

void log_out(client_t *client, char **cmd)
{
    FILE *f;
    char path[PATH_MAX];
    char **file;

    sprintf(path, "%s%s/user_info.txt", CLIENT_SAVE, client->uuid);
    file = get_file(path);
    f = fopen(path, "w");
    if (f && file)
        fprintf(f, "%s\n%s\n%d", client->username, client->uuid,
            (atoi(file[2]) - 1));
    dprintf(client->clientfd, "/logout");
    server_event_user_logged_out(client->uuid);
    client->is_connected = false;
    if (client->uuid) {
        free(client->uuid);
        client->uuid = NULL;
    }
    destroy_tab(file);
    fclose(f);
}

static char *create_new_user_setup(const char *username, char *id)
{
    char path[PATH_MAX];
    FILE *f;

    sprintf(path, "%s%s", CLIENT_SAVE, id);
    mkdir(path, 0777);
    f = fopen(strcat(path, "/user_info.txt"), "w");
    if (f)
        fprintf(f, "%s\n%s\n1", username, id);
    fclose(f);
    server_event_user_created(id, username);
    return id;
}

static char *add_user_to_list(char *path, const char *username)
{
    uuid_t temp;
    FILE *f;
    char *id = malloc(37);

    uuid_generate_random(temp);
    uuid_unparse_upper(temp, id);
    f = fopen(path, "a+");
    if (f)
        fprintf(f, "%s\n%s\n", username, id);
    fclose(f);
    return id;
}

void update_status(const char *uuid, const char *username)
{
    char path[PATH_MAX];
    char **file;
    FILE *f;
    int status = 0;

    sprintf(path, "%s%s/user_info.txt", CLIENT_SAVE, uuid);
    file = get_file(path);
    f = fopen(path, "w");
    if (f && file) {
        status = atoi(file[2]) + 1;
        fprintf(f, "%s\n%s\n%d", username, uuid, status);
        fclose(f);
    }
}

char *is_existing(const char *username)
{
    char *id = NULL;
    char **file;
    char path[4096];

    sprintf(path, "%sclients_id_list.txt", CLIENT_SAVE);
    file = get_file(path);
    for (int i = 0; file && file[i]; i++)
        if (!strcmp(file[i], username)) {
            id = malloc(sizeof(char) * (strlen(file[i + 1]) + 1));
            strcpy(id, file[i + 1]);
            destroy_tab(file);
            update_status(id, username);
            return id;
        }
    id = create_new_user_setup(username, add_user_to_list(path, username));
    destroy_tab(file);
    return id;
}

void log_in(client_t *client, char **cmd)
{
    if (cmd && cmd[0] && strlen(cmd[0]) < MAX_NAME_LENGTH) {
        strcpy(client->username, cmd[0]);
        client->uuid = is_existing(cmd[0]);
        client->is_connected = true;
        dprintf(client->clientfd, "/login \"%s\" \"%s\"",
            client->username, client->uuid);
        server_event_user_logged_in(client->uuid);
    }
}

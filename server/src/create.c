/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** create
*/

#include "server.h"

void create_reply(void)
{
}

char *create_new_directory(client_t *client, char **cmd, int nb)
{
    char path[PATH_MAX];
    FILE *info_file = NULL;
    uuid_t temp;
    char *id = malloc(37);

    uuid_generate_random(temp);
    uuid_unparse_upper(temp, id);
    sprintf(path, "%s%s%s", TEAM_SAVE, client->context, id);
    if (mkdir(path, 0777) != -1) {
        strcat(path, "/info.txt");
        info_file = fopen(path, "w");
        if (info_file) {
            fprintf(info_file, "%s\n%s", cmd[0], cmd[1]);
            fclose(info_file);
        }
        dprintf(client->clientfd, "/create \"%d\" \"%s\" \"%s\" \"%s\"",
            nb, id, cmd[0], cmd[1]);
    }
    return id;
}

void create(client_t *client, char **cmd)
{
    int nb_context;
    char *id = NULL;
    int (*func[])(const char *, const char *, const char *) = {
        server_event_team_created,
        server_event_channel_created};

    nb_context = count_context(client->context);
    if (nb_context < 2 && (cmd || cmd[0] || cmd[1])) {
        id = create_new_directory(client, cmd, nb_context);
        func[nb_context](id, cmd[0], cmd[1]);
        free(id);
    } else if (nb_context == 3 && (cmd || cmd[1]))
        create_reply();
    else
        dprintf(client->clientfd, "/error \"%d\" \"%s\"",
            nb_context, client->context);
}

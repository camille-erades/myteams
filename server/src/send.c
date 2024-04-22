/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** send
*/

#include "server.h"

int open_discussion(client_t *client, char *uuid, char *message)
{
    FILE *f_sender;
    FILE *f_receiver;
    char path_sender[PATH_MAX];
    char path_receiver[PATH_MAX];

    sprintf(path_sender, "%s%s/%s.txt", CLIENT_SAVE, client->uuid, uuid);
    sprintf(path_receiver, "%s%s/%s.txt", CLIENT_SAVE, uuid, client->uuid);
    f_receiver = fopen(path_receiver, "a+");
    if (!f_receiver)
        return 1;
    f_sender = fopen(path_sender, "a+");
    if (f_receiver && f_sender) {
        if (strcmp(path_sender, path_receiver))
            fprintf(f_receiver, "%s\n%s\n", client->uuid, message);
        fprintf(f_sender, "%s\n%s\n", client->uuid, message);
        server_event_private_message_sended(client->uuid, uuid, message);
    }
    fclose(f_sender);
    fclose(f_receiver);
    return 0;
}

void send_msg(client_t *client, char **cmd)
{
    if (!cmd || !cmd[0] || !cmd[1])
        return;
    if (open_discussion(client, cmd[0], cmd[1])) {
        dprintf(client->clientfd, "/error \"user\" %s", cmd[0]);
        return;
    }
    server_event_private_message_sended(client->uuid, cmd[0], cmd[1]);
    for (client_t *p = client->next; p; p = p->next) {
        if (!strcmp(p->uuid, cmd[0]))
            dprintf(p->clientfd, "/send \"%s\"\"%s\"", client->uuid, cmd[1]);
        if (p == client)
            break;
    }
}

void list_message(client_t *client, char **cmd)
{
    char path[PATH_MAX];
    char **file = NULL;

    if (!cmd)
        return;
    sprintf(path, "%s%s/%s.txt", CLIENT_SAVE, client->uuid, cmd[0]);
    file = get_file(path);
    if (!file)
        dprintf(client->clientfd, "/error \"user\" %s", cmd[0]);
    destroy_tab(file);
}

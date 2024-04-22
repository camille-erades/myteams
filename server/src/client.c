/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-clement.monnoire
** File description:
** client
*/

#include "server.h"

client_t *initiate_user(my_ftp_t *ftp, int fd)
{
    client_t *client;

    client = (client_t *)malloc(sizeof(client_t));
    client->is_connected = false;
    client->clientfd = fd;
    client->next = client;
    client->uuid = NULL;
    client->context[0] = '\0';
    return client;
}

void create_new_client(my_ftp_t *ftp, int fd)
{
    client_t *new_client;
    client_t *p;

    if (fd < 0)
        return;
    new_client = initiate_user(ftp, fd);
    if (!ftp->head)
        ftp->head = new_client;
    else {
        p = ftp->head;
        while (p->next != ftp->head)
            p = p->next;
        p->next = new_client;
        new_client->next = ftp->head;
    }
}

void close_user(client_t *client, char **argv)
{
    dprintf(client->clientfd, "/logout");
    close(client->clientfd);
    client->clientfd = -1;
}

void init_clients(void)
{
    char path[PATH_MAX];
    char **file;

    strcpy(path, CLIENT_SAVE);
    strcat(path, "clients_id_list.txt");
    file = get_file(path);
    if (!file)
        return;
    for (int i = 0; file[i] && file[i + 1]; i += 2)
        server_event_user_loaded(file[i + 1], file[i]);
    destroy_tab(file);
}

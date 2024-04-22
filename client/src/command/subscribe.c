/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** subscribe.c
*/

#include "client.h"

void unsubscribe(client_t *client, char **command)
{
    client_print_unsubscribed(client->uuid, command[1]);
}

void subscribe(client_t *client, char **command)
{
    client_print_subscribed(client->uuid, command[1]);
}

void subscribed(client_t *client, char **command)
{
}

/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** error
*/

#include "client.h"

void error_event(client_t *client, char **command)
{
    if (!strcmp(command[0], "user"))
        client_error_unknown_user(command[1]);
}

/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** info_for_user.c
*/

#include "../include/client.h"

void print_users(client_t *client, char **command)
{
    int is_conected;

    is_conected = atoi(command[2]);
    client_print_users(command[0], command[1], is_conected);
}

void print_user(client_t *client, char **command)
{
    int is_conected;

    is_conected = atoi(command[2]);
    client_print_user(command[0], command[1], is_conected);
}

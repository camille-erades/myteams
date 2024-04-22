/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** get_input
*/

#include "../include/client.h"

char *get_input(FILE *fd)
{
    char *buffer;
    size_t line_buf_size = 0;

    getline(&buffer, &line_buf_size, fd);
    return buffer;
}

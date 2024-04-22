/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myteams-camille.erades
** File description:
** get_file
*/

#include "server.h"

char **get_file(char *path)
{
    struct stat file_stat;
    char *buffer = NULL;
    char **tab = NULL;
    int fd = 0;
    int size = 0;

    fd = open(path, O_RDONLY);
    if (fd != -1) {
        stat(path, &file_stat);
        size = file_stat.st_size;
        if (size) {
            buffer = malloc(sizeof(char) * (size + 1));
            read(fd, buffer, size);
            buffer[size] = '\0';
            tab = my_str_to_word_array(buffer, "\n");
            free(buffer);
        }
    }
    close(fd);
    return tab;
}

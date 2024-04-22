/*
** EPITECH PROJECT, 2023
** Stumper7
** File description:
** destroy_tab
*/

#include "server.h"

void destroy_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

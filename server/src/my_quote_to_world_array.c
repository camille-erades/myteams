/*
** EPITECH PROJECT, 2023
** Stumper7
** File description:
** my_quote_to_wold_array
*/

#include "server.h"

static int get_nb_string(char *str)
{
    int nb = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\"' && str[i + 1] == '\"')
            return 0;
        if (str[i] == '\"')
            nb++;
    }
    if ((nb % 2) != 0)
        return 0;
    return (nb / 2);
}

static char *malloc_string(char *str)
{
    char *new_str;
    int i = 0;

    while (str[i] && str[i] != '\"')
        i++;
    new_str = malloc(sizeof(char) * (i + 1));
    return new_str;
}

static void copy_string(char **array, char *str)
{
    int j = 0;
    int line = 0;
    int quote = 0;

    for (int i = 0; str[i]; i++) {
        if (!j && (quote % 2) != 0 && str[i] != '\"')
            array[line] = malloc_string(str + i);
        if ((quote % 2) != 0 && str[i] != '\"') {
            array[line][j] = str[i];
            j++;
        }
        if (str[i] == '\"')
            quote++;
        if (quote && (quote % 2) == 0 && str[i] == '\"') {
            array[line][j] = '\0';
            line++;
            j = 0;
        }
    }
}

char **my_quote_to_wolrd_array(char *str)
{
    char **array = NULL;
    int nb_string = 0;

    nb_string = get_nb_string(str);
    if (!nb_string)
        return NULL;
    array = malloc(sizeof(char *) * (nb_string + 1));
    copy_string(array, str);
    array[nb_string] = NULL;
    return array;
}

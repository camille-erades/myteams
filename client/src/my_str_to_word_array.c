/*
** EPITECH PROJECT, 2023
** Stumper7
** File description:
** my_str_to_wold_array
*/

#include "client.h"

static bool is_separator(const char c, const char *separators)
{
    for (int i = 0; separators[i]; i++)
        if (c == separators[i])
            return true;
    return false;
}

static int nb_string(char *str, char *sep)
{
    int nb_string = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], sep) &&
            (is_separator(str[i + 1], sep) || str[i + 1] == '\0'))
            continue;
        if (is_separator(str[i], sep))
            nb_string++;
    }
    return nb_string + 1;
}

static char *malloc_string(char *str, char *separator)
{
    int i = 0;
    char *new_str = NULL;

    for (i; str[i] != '\0' && !is_separator(str[i], separator); i++);
    new_str = malloc(sizeof(char) * (i + 1));
    return new_str;
}

static int copy_string(char *src, char *dest, char *separator)
{
    int i = 0;

    for (i; src[i] != '\0' && !is_separator(src[i], separator); i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return i - 1;
}

char **my_str_to_word_array(char *str, char *separator)
{
    char **array = NULL;
    int nstr = 0;

    if (!str)
        return NULL;
    while (is_separator(str[0], separator))
        str++;
    if (!*str)
        return NULL;
    array = malloc(sizeof(char *) * (nb_string(str, separator) + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], separator))
                continue;
        array[nstr] = malloc_string(str + i, separator);
        i += copy_string(str + i, array[nstr], separator);
        nstr++;
    }
    array[nstr] = NULL;
    return array;
}

/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** my_strdup.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *my_strdup(char *str)
{
    int i = 0;
    char *dup = NULL;

    if (!str)
        exit(84);
    dup = calloc(strlen(str) + 2, sizeof(char));
    while (str[i] != 0) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = 0;
    return (dup);
}
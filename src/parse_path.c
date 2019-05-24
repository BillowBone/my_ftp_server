/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** parse_path.c
*/

#include <string.h>
#include <stdlib.h>

char *parse_path(char *request, int opt)
{
    int i = 0;
    char *path = calloc(strlen(request) - (4 + opt), sizeof(char));

    for (int j = (3 + opt); request[j] != '\r'; j++) {
        path[i] = request[j];
        i++;
    }
    path[i] = 0;
    return (path);
}
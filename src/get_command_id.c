/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** get_command_id.c
*/

#include <string.h>
#include "commands.h"

int get_command_id(char *request)
{
    for (int i = 0; i < 14; i++) {
        int len = strlen(request);
        int len2 = strlen(commands[i]);
        if (len >= len2 && strncmp(request, commands[i], len2) == 0)
            return (i);
    }
    return (-1);
}
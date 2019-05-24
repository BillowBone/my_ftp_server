/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** verify_args.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void verify_args(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        display_help();
    if (argc != 3)
        exit(84);
    for (int i = 0; argv[1][i]; i++) {
        if (argv[1][i] < 48 || argv[1][i] > 57)
            exit(84);
    }
    if (chdir(argv[2]) == -1) {
        exit(84);
    }
}
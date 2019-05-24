/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** display_help.c
*/

#include <stdio.h>
#include <stdlib.h>

void display_help(void)
{
    printf("USAGE: ./myftp port path\n\t");
    printf("port is the port number on which the server socket listens\n\t");
    printf("path is the path to the home directory for the Anonymous user\n");
    exit(0);
}
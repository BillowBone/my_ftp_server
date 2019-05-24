/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** init_server.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int create_socket(void)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    return (server_socket);
}

void bind_server(int socket, char *port)
{
    struct sockaddr_in my_addr = { 0 };

    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(port));
    if (bind(socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("bind()");
        exit(84);
    }
}

void open_server(int server_socket)
{
    if (listen(server_socket, 128) == -1) {
        perror("listen()");
        exit(84);
    }
}
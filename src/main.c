/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - ftpserver
** File description:
** main.c
*/

#include <unistd.h>
#include "server.h"

int main(int argc, char *argv[])
{
    int server_socket = create_socket();
    list_t *my_clients = NULL;

    verify_args(argc, argv);
    bind_server(server_socket, argv[1]);
    open_server(server_socket);
    server(server_socket, my_clients, argv[2]);
    close_clients(my_clients);
    free_clients(my_clients);
    close(server_socket);
    return (0);
}
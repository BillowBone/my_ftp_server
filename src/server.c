/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** server.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>
#include "server.h"

void init_sets(fd_set *writes, fd_set *reads, list_t *clients, int srvr_sckt)
{
    client_t *current = NULL;

    FD_ZERO(writes);
    FD_ZERO(reads);
    FD_SET(srvr_sckt, reads);
    if (clients != NULL) {
        current = clients->first;
        while (current) {
            FD_SET(current->socket, writes);
            FD_SET(current->socket, reads);
            current = current->next;
        }
    }
}

list_t *process_clients(list_t *my_clients, fd_set reads, fd_set writes)
{
    client_t *current = NULL;

    current = my_clients->first;
    while (current != NULL) {
        read_requests(current, reads);
        write_responses(current, writes);
        current = current->next;
    }
    check_quitting_clients(my_clients);
    return (my_clients);
}

void server(int socket, list_t *clients, char *path)
{
    fd_set writes;
    fd_set reads;
    int bigger_socket = 0;

    while (1) {
        init_sets(&writes, &reads, clients, socket);
        bigger_socket = get_bigger_socket(clients, socket);
        int result = select(bigger_socket + 1, &reads, &writes, NULL, NULL);
        if (result == -1) {
            perror("select()");
            exit(84);
        } else if (result) {
            if (FD_ISSET(socket, &reads) == 1)
                clients = new_client(socket, clients, path);
            clients = process_clients(clients, reads, writes);
        }
    }
}
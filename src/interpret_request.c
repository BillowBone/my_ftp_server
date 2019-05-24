/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** interpret_request.c
*/

#include "server.h"

void interpret_request(client_t *current)
{
    int command = get_command_id(current->request);

    if (current->username != 1 || current->password != 1) {
        interpret_authentification(current, command);
    } else {
        interpret_directories(current, command);
        interpret_file_actions(current, command);
        interpret_others(current, command);
    }
    if (command == -1)
        current->response = my_strdup("500 Command not recognized!\r\n");
}
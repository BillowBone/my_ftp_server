/*
** EPITECH PROJECT, 2019
** PSU - Network Programming - myftp
** File description:
** interpret_commands.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

void wrong_authentification(client_t *crt, int cmd)
{
    if (cmd == 0 && strcmp(crt->request, "USER Anonymous\r\n") != 0)
        crt->username = 2;
    if (cmd == 1 && strcmp(crt->request, "PASS \r\n") != 0)
        crt->password = 2;
    if ((cmd == 0 && crt->password == 2) || (cmd == 1 && crt->username == 2)) {
        crt->response = my_strdup("530 You are not logged in yet!\r\n");
        crt->username = 0;
        crt->password = 0;
    }
}

void interpret_authentification(client_t *crt, int cmd)
{
    if (cmd == 0 && crt->password == 0) {
        crt->response = my_strdup("331 Username valid, please "
                                    "enter password\r\n\0");
        crt->username = 1;
    }
    if (cmd == 1 && crt->password == 0) {
        crt->response = my_strdup("332 Password valid, please "
                                    "enter username\r\n\0");
        crt->password = 1;
    }
    if ((cmd == 0 && crt->password == 1) || (cmd == 1 && crt->username == 1)) {
        crt->response = my_strdup("230 You are now logged in\r\n\0");
        crt->username = 1;
        crt->password = 1;
    }
    if (cmd > 1 || cmd < 0)
        crt->response = my_strdup("530 You are not logged in yet!\r\n");
    wrong_authentification(crt, cmd);
}

void interpret_others(client_t *current, int command)
{
    if (command == 4) {
        current->response = my_strdup("221 You logged out!\r\n");
        current->quitting = 1;
    }
    if (command == 9) {
        current->response = my_strdup("214\r\n");
    }
    if (command == 10) {
        current->response = my_strdup("200 Command OK\r\n");
    }
}

void interpret_directories(client_t *current, int command)
{
    if (command == 2) {
        current->response = my_strdup("250 CWD OK\r\n");
        change_working_directory(current);
    }
    if (command == 3) {
        current->response = my_strdup("200 CDUP OK\r\n");
        chdir(current->current_dir);
        if (chdir("..") == 0) {
            getcwd(current->current_dir, sizeof(current->current_dir));
        } else {
            free(current->response);
            current->response = my_strdup("550 Can't access this"
                                            "working directory!\r\n");
        }
    }
    if (command == 6) {
        construct_pwd(current);
    }
}

void interpret_file_actions(client_t *current, int command)
{
    if (command == 5) {
        char *path = parse_path(current->request, 2);
        if (remove(path) == 0) {
            current->response = my_strdup("250 Delete OK\r\n");
        } else {
            current->response = my_strdup("550 Can't remove this file!\r\n");
        }
        free(path);
    }
    if (command == 13) {
        listing(current);
    }
}
/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** clean_inhib
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"
#include "utils.h"

char *get_inhib_content(char *command)
{
    int i = 0;
    int j = 0;
    int inhib = 0;
    int nb_inhib = search_inhib(command);
    int len = get_inhib_len(command);
    char *clean_command = malloc(sizeof(char) * (len + 1));

    while (command[i] != '\0' && inhib != nb_inhib && j != len) {
        if (command[i] != INIBITHORS_CHAR) {
            clean_command[j] = command[i];
            j++;
        } else
            inhib++;
        i++;
    }
    clean_command[j] = '\0';
    return clean_command;
}

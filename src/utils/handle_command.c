/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_command
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_lib.h"
#include "commands.h"
#include "mysh.h"
#include "utils.h"

int search_inhib(char *command)
{
    int i = 0;
    int nb_inib = 0;

    while (command[i] != '\0') {
        if (command[i] == INIBITHORS_CHAR)
            nb_inib++;
        i++;
    }
    return nb_inib;
}

char **handle_command(char *command)
{
    int nb_inhib = search_inhib(command);

    if (nb_inhib == 0)
        return str_to_word_array(command, " \n\t");
    if (nb_inhib % 2 != 0) {
        write(STDERR_FILENO, "Unmatched '''.\n", 15);
        return NULL;
    }
    return my_str_to_word_array_inhib(command, " \n\t", nb_inhib);
}

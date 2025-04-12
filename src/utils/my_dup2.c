/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** my_dup2
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void my_dup2(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    return;
}

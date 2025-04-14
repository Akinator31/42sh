/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** check pipes
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void my_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe has failed");
        exit(EXIT_FAILURE);
    }
    return;
}

/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** retrieve_history
*/

#include "utils.h"
#include <stdlib.h>
#include <string.h>

char *retrieve_history_path(char ***envp)
{
    char *homepath = get_environ_variable_value(envp, "HOME");
    char *logpath = NULL;

    if (!homepath)
        homepath = "/tmp/";
    logpath = malloc(sizeof(char) * strlen(homepath) + 16);
    logpath = strcpy(logpath, homepath);
    free(homepath);
    logpath = strcat(logpath, "/.42sh_history");
    return logpath ? logpath : NULL;
}

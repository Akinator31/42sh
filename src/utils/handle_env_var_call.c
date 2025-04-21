/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_env_var_call
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

static int get_index_var_env(char **command, char **env)
{
    int index_env = env_var_already_exist(&env, command[0] + 1);
    char *command_dup = NULL;

    if (index_env >= 0)
        return index_env;
    command_dup = my_strdup(command[0]);
    my_strlowcase(command_dup + 1);
    index_env = env_var_already_exist(&env, command_dup + 1);
    if (index_env >= 0) {
        free(command_dup);
        return index_env;
    }
    my_strupcase(command_dup + 1);
    index_env = env_var_already_exist(&env, command_dup + 1);
    free(command_dup);
    return index_env;
}

static void handle_if_is_var_env(char **command, char **env)
{
    int index_env = get_index_var_env(command, env);
    char *env_value = NULL;
    int i = 0;
    int len = 0;

    if (index_env == -1)
        return;
    while (env[index_env][i] != '\0' && env[index_env][i] != '=')
        i++;
    len = strlen(env[index_env] + i + 1);
    env_value = realloc(command[0], sizeof(char) * (len + 1));
    if (!env_value) {
        free(command[0]);
        return;
    }
    command[0] = env_value;
    strcpy(command[0], env[index_env] + i + 1);
    command[0][len] = '\0';
}

void handle_env_var_call(char **command_array, char **env)
{
    for (int i = 0; command_array[i] != NULL; i++) {
        if (command_array[i][0] == '$')
            handle_if_is_var_env(&command_array[i], env);
    }
}

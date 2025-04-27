/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** load_rc
*/

#include "mysh.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const config_element_t config_element[] = {
    {"alias", &add_alias},
    {NULL, NULL}
};

static void set_comment(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '#')
            str[i] = '\0';
        i++;
    }
}

static void handle_config_element(config_rc_t *config, char *line)
{
    int i = 0;
    int len = 0;

    while (config_element[i].key_word != NULL) {
        len = strlen(config_element[i].key_word);
        if (strncmp(line, config_element[i].key_word, len) == 0)
            config_element[i].f(config, line + len + 1);
        i++;
    }
}

static void load_existing_rc(FILE *file, config_rc_t *config)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        set_comment(line);
        handle_config_element(config, line);
    }
    free(line);
}

config_rc_t *load_rc(char **env)
{
    FILE *file = NULL;
    int home_index = env_var_already_exist(&env, HOME_VAR);
    char *path_part_one = NULL;
    char *complete_path = NULL;
    config_rc_t *config = NULL;

    if (home_index < 0)
        return NULL;
    path_part_one = my_strcat_malloc(env[home_index], "/");
    complete_path = my_strcat_malloc(path_part_one, RC_FILE_NAME);
    file = fopen(complete_path + LEN_HOME_VAR, "r");
    free(path_part_one);
    free(complete_path);
    if (!file)
        return NULL;
    config = calloc(1, sizeof(config_rc_t));
    config->alias = NULL;
    if (!config)
        return NULL;
    load_existing_rc(file, config);
    return config;
}

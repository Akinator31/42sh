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

static char *my_strcat_malloc(char *str1, char *str2)
{
    char *str = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    int i = 0;
    int i2 = 0;

    while (str1[i2] != '\0') {
        str[i] = str1[i2];
        i2++;
        i++;
    }
    i2 = 0;
    while (str2[i2] != '\0') {
        str[i] = str2[i2];
        i2++;
        i++;
    }
    str[i] = '\0';
    return str;
}

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
            config_element[i].f(config, line);
        i++;
    }
}

static void load_existing_rc(FILE **file, config_rc_t *config)
{
    char *line = NULL;
    size_t *len = 0;

    while (getline(&line, len, *file) != -1) {
        set_comment(line);
        handle_config_element(config, line);
    }
    free(line);
}

config_rc_t *load_rc(char **env)
{
    FILE *file = NULL;
    int home_index = env_var_already_exist(&env, HOME_VAR);
    char *path = NULL;
    config_rc_t *config = NULL;

    if (home_index < 0)
        return NULL;
    path = my_strcat_malloc(env[home_index], RC_FILE_NAME);
    file = fopen(path, "r");
    if (!file)
        return NULL;
    config = calloc(1, sizeof(config_rc_t));
    if (!config)
        return NULL;
    load_existing_rc(&file, config);
    return config;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** add_alias
*/

#include "my_lib.h"
#include "mysh.h"
#include <stdlib.h>
#include <unistd.h>

static void first_alias(config_rc_t *config, char **content)
{
    config->alias = malloc(sizeof(alias_t));
    if (!config->alias)
        return;
    config->alias[0].alias_name = my_strdup(content[0]);
    config->alias[0].command = my_strdup(content[1]);
    config->alias->nb_alias = 1;
    free_2d_array_of_char(content);
}

void add_alias(config_rc_t *config, char *args)
{
    char **content = str_to_word_array(args, "=");

    if (!content)
        return;
    if (get_2d_arr_len(content) != 2) {
        free_2d_array_of_char(content);
        return;
    }
    if (config->alias == NULL) {
        first_alias(config, content);
        return;
    }
    config->alias = realloc(config->alias,
        sizeof(alias_t) * (config->alias->nb_alias + 1));
    if (!config->alias)
        return;
    config->alias[config->alias->nb_alias].alias_name = my_strdup(content[0]);
    config->alias[config->alias->nb_alias].command = my_strdup(content[1]);
    free_2d_array_of_char(content);
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_config_st
*/

#include "mysh.h"
#include <stdlib.h>

void free_config_st(config_rc_t *config)
{
    uint i = 0;

    if (!config)
        return;
    if (config->alias->nb_alias >= 1) {
        for (; i < config->alias->nb_alias; i++) {
            free(config->alias[i].alias_name);
            free(config->alias[i].command);
        }
    }
    if (config->alias)
        free(config->alias);
    free(config);
}

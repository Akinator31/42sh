/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_core
*/

#include "history.h"
#include "commands.h"
#include <stdlib.h>

void history_free(history_t *history)
{
    for (size_t i = 0; i < history->count; i++) {
        free(history->lines[i]);
    }
    free(history->lines);
    history->lines = NULL;
}

void history_add(history_t *history, const char *line, char ***envp)
{
    size_t i = 0;

    my_write_history((char *)line, envp);
    for (i = 0; i < history->count; i++)
        free(history->lines[i]);
    history->count = 0;
    history_load(history, envp);
}

void history_init(history_t *history, char ***envp)
{
    history->lines = calloc(HISTORY_MAX, sizeof(char *));
    history->count = 0;
    history->capacity = HISTORY_MAX;
    history->current_index = 0;
    history_load(history, envp);
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_core
*/

#include "history.h"
#include "commands.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

void history_free(history_t *history)
{
    if (history == NULL || history->lines == NULL)
        return;
    for (size_t i = 0; i < history->count; i++) {
        if (history->lines[i] != NULL)
            free(history->lines[i]);
    }
    if (history->lines != NULL)
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
    char *filepath = retrieve_history_path(envp);
    size_t total_lines = 0;

    if (!filepath)
        total_lines = HISTORY_MAX;
    else
        total_lines = count_lines(filepath);
    history->lines = calloc(total_lines, sizeof(char *));
    history->count = 0;
    history->capacity = total_lines;
    history->current_index = 0;
    history_load(history, envp);
}

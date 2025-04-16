/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_io
*/

#include "history.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void process_history_line(history_t *history, char *line)
{
    char *command = NULL;
    size_t cmd_len = 0;

    command = strchr(line, '\t');
    if (!command)
        return;
    command = strchr(command + 1, '\t');
    if (!command)
        return;
    command = strchr(command + 1, '\t');
    if (!command)
        return;
    command++;
    cmd_len = strlen(command);
    if (cmd_len > 0 && command[cmd_len - 1] == '\n')
        command[cmd_len - 1] = '\0';
    if (history->count < history->capacity) {
        history->lines[history->count] = strdup(command);
        history->count++;
    }
}

void free_resources(char *history_path, char *line, FILE *file)
{
    if (line)
        free(line);
    if (file)
        fclose(file);
    if (history_path)
        free(history_path);
}

static FILE *open_history_file(char *history_path)
{
    FILE *file = fopen(history_path, "r");

    return file;
}

static void read_history_content(history_t *history, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    do {
        read = getline(&line, &len, file);
        if (read != -1)
            process_history_line(history, line);
    } while (read != -1);
    if (line)
        free(line);
}

void history_load(history_t *history, char ***envp)
{
    char *history_path = retrieve_history_path(envp);
    FILE *file = NULL;

    if (!history_path)
        return;
    file = open_history_file(history_path);
    if (!file) {
        free(history_path);
        return;
    }
    read_history_content(history, file);
    fclose(file);
    free(history_path);
    history->current_index = history->count;
}

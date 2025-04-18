/*
** EPITECH PROJECT, 2025
** B-PSU-200 : 42sh
** File description:
** line_buffer
*/

#ifndef HISTORY_H_
    #define HISTORY_H_
    #define HISTORY_MAX 100
    #include "line_buffer.h"

typedef struct {
    char **lines;
    size_t count;
    size_t capacity;
    int current_index;
} history_t;

void history_init(history_t *history, char ***envp);
void history_free(history_t *history);
void history_load(history_t *history, char ***envp);
void history_add(history_t *history, const char *line, char ***envp);
void history_previous(history_t *history, line_buffer_t *line);
void history_next(history_t *history, line_buffer_t *line);

#endif /* !HISTORY_H_ */

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_navigation
*/

#include "history.h"

void history_previous(history_t *history, line_buffer_t *line)
{
    if (history->count > 0 && history->current_index > 0) {
        history->current_index--;
        line_set_content(line, history->lines[history->current_index]);
    }
}

void history_next(history_t *history, line_buffer_t *line)
{
    if (history->current_index < history->count) {
        history->current_index++;
        if (history->current_index == history->count) {
            line->buffer[0] = '\0';
            line->length = 0;
            line->position = 0;
            line_clear(line);
            line_display(line);
        } else {
            line_set_content(line, history->lines[history->current_index]);
        }
    }
}

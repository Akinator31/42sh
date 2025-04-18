/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_buffer_cursor
*/

#include "line_buffer.h"
#include <stdio.h>

void line_display(line_buffer_t *line)
{
    if (line->position < line->length) {
        printf("\033[%dD", line->length - line->position);
    }
}

void line_cursor_left(line_buffer_t *line)
{
    if (line->position > 0) {
        line->position--;
        printf("\033[1D");
    }
}

void line_cursor_right(line_buffer_t *line)
{
    if (line->position < line->length) {
        line->position++;
        printf("\033[1C");
    }
}

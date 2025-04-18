/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_buffer_core
*/

#include "line_buffer.h"
#include <stdio.h>
#include <stdlib.h>

void line_buffer_init(line_buffer_t *line)
{
    line->buffer = calloc(LINE_BUF_SIZE, sizeof(char));
    line->position = 0;
    line->length = 0;
}

void line_buffer_free(line_buffer_t *line)
{
    free(line->buffer);
    line->buffer = NULL;
}

void line_clear(line_buffer_t *line)
{
    printf("\r");
    for (int i = 0; i < line->length + 3; i++)
        printf(" ");
    printf("\r");
}

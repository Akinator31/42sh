/*
** EPITECH PROJECT, 2023
** B-PSU-200 : 42sh
** File description:
** Terminal canonical mode management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "line_buffer.h"

void line_set_content(line_buffer_t *line, const char *content)
{
    strncpy(line->buffer, content, LINE_BUF_SIZE - 1);
    line->length = strlen(line->buffer);
    line->position = line->length;
    line_clear(line);
    line_display(line);
}

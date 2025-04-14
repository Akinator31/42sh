/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** input_display
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/termios.h>
#include "history.h"
#include "line_buffer.h"
#include "utils.h"

void redraw_line(line_buffer_t *line, char **envp)
{
    int i = 0;

    printf("\r\033[K");
    print_prompt(envp);
    for (i = 0; i < line->length; i++)
        putchar(line->buffer[i]);
    if (line->position < line->length) {
        printf("\r");
        print_prompt(envp);
        for (i = 0; i < line->position; i++)
            putchar(line->buffer[i]);
    }
    fflush(stdout);
}

void handle_arrow_keys(char seq[2], line_buffer_t *line,
    history_t *history, char **envp)
{
    switch (seq[1]) {
        case 'A':
            history_previous(history, line);
            redraw_line(line, envp);
            break;
        case 'B':
            history_next(history, line);
            redraw_line(line, envp);
            break;
        case 'C':
            line_cursor_right(line);
            redraw_line(line, envp);
            break;
        case 'D':
            line_cursor_left(line);
            redraw_line(line, envp);
            break;
    }
}

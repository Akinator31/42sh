/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_buffer_editing
*/

#include "commands.h"
#include "history.h"
#include "line_buffer.h"
#include "mysh.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void line_insert_char(line_buffer_t *line, char c)
{
    if (line->length >= LINE_BUF_SIZE - 1)
        return;
    memmove(line->buffer + line->position + 1,
            line->buffer + line->position,
            line->length - line->position + 1);
    line->buffer[line->position] = c;
    line->position++;
    line->length++;
    line->buffer[line->length] = '\0';
    line_clear(line);
    line_display(line);
}

void line_process_backspace(line_buffer_t *line)
{
    if (line->position <= 0)
        return;
    memmove(line->buffer + line->position - 1,
        line->buffer + line->position,
        line->length - line->position + 1);
    line->position--;
    line->length--;
    line_clear(line);
    line_display(line);
}

void line_process_enter(line_buffer_t *line, void *hist, char ***envp)
{
    history_t *history = (history_t *)hist;
    int stdin_cpy = duplicate_file_descriptor(STDIN_FILENO);
    int stdout_cpy = duplicate_file_descriptor(STDOUT_FILENO);
    int error_code = 0;
    int result_command = 0;

    if (line->length > 0) {
        history_add(history, line->buffer, envp);
        result_command = analyse_command(envp, line->buffer, &error_code);
        restore_stdin_stdout_fd(stdin_cpy, stdout_cpy);
        if (handle_output_command(result_command, line->buffer, envp)) {
            close_fds(2, stdin_cpy, stdout_cpy);
        }
        line->buffer[0] = '\0';
        line->position = 0;
        line->length = 0;
    }
}

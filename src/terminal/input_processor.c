/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** input_processor
*/

#include "history.h"
#include "utils.h"
#include "canonical_mod.h"
#include <stdio.h>
#include <unistd.h>

/**
  * Handle arrow keys for navigation in the line buffer
  * @param seq Escape sequence for arrow keys
  * @param line Line buffer structure
  * @param history History structure
  * @param envp Environment variables
*/
static void process_special_key(char c, line_buffer_t *line,
    history_t *history, char ***envp)
{
    if (c == '\n') {
        printf("\n");
        line_process_enter(line, history, envp);
        print_prompt(*envp);
        fflush(stdout);
        return;
    }
    if (c == 127 || c == 8) {
        line_process_backspace(line);
        redraw_line(line, *envp);
    }
}

int handle_escape_sequence(line_buffer_t *line, history_t *history,
    char **envp)
{
    char seq[3] = {0};

    if (read(STDIN_FILENO, &seq[0], 1) <= 0)
        return -1;
    if (read(STDIN_FILENO, &seq[1], 1) <= 0)
        return -1;
    if (seq[0] == '[')
        handle_arrow_keys(seq, line, history, envp);
    return 0;
}

int process_input_char(char c, line_buffer_t *line,
    history_t *history, char ***envp)
{
    if (c == 27) {
        if (handle_escape_sequence(line, history, *envp) == -1)
            return 1;
        return 0;
    }
    process_special_key(c, line, history, envp);
    if (c == 4 && line->length == 0) {
        printf("\n");
        return 1;
    }
    process_normal_char(c, line, envp);
    return 0;
}

void process_ctrl_keys(char c, line_buffer_t *line, int *should_exit)
{
    if (c == 4 && line->length == 0) {
        printf("\n");
        *should_exit = 1;
    }
}

void process_normal_char(char c, line_buffer_t *line, char ***envp)
{
    if (c != 4 && c != 27 && c != 127 && c != 8 && c != '\n') {
        line_insert_char(line, c);
        redraw_line(line, *envp);
    }
}

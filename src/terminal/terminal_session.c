/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal_session
*/

#include "history.h"
#include "line_buffer.h"
#include "utils.h"
#include "canonique_mod.h"
#include <stdio.h>
#include <sys/termios.h>

void initialize_session(line_buffer_t *line, history_t *history,
    char ***envp)
{
    line_buffer_init(line);
    history_init(history, envp);
}

void cleanup_session(line_buffer_t *line, history_t *history,
    struct termios *original)
{
    disable_raw_mode(original);
    line_buffer_free(line);
    history_free(history);
}

int setup_terminal(struct termios *original, line_buffer_t *line,
    history_t *history, char **envp)
{
    if (enable_raw_mode(original) == -1)
        return -1;
    print_prompt(envp);
    fflush(stdout);
    return 0;
}

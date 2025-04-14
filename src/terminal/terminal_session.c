/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal_session
*/

#include "history.h"
#include "line_buffer.h"
#include "utils.h"
#include "canonical_mod.h"
#include <stdio.h>
#include <sys/termios.h>

/**
 * Initialize the terminal session
 * @param line Line buffer structure
 * @param history History structure
 * @param envp Environment variables
 */
void initialize_session(line_buffer_t *line, history_t *history,
    char ***envp)
{
    line_buffer_init(line);
    history_init(history, envp);
}

/**
 * Cleanup the terminal session
 * @param line Line buffer structure
 * @param history History structure
 * @param original Original terminal settings
 */
void cleanup_session(line_buffer_t *line, history_t *history,
    struct termios *original)
{
    disable_raw_mode(original);
    line_buffer_free(line);
    history_free(history);
}

/**
 * Setup the terminal for raw mode
 * @param original Original terminal settings
 * @param line Line buffer structure
 * @param history History structure
 * @param envp Environment variables
 * @return 0 on success, -1 on failure
 */
int setup_terminal(struct termios *original, line_buffer_t *line,
    history_t *history, char **envp)
{
    if (enable_raw_mode(original) == -1)
        return -1;
    print_prompt(envp);
    fflush(stdout);
    return 0;
}

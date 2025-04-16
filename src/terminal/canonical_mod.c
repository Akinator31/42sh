/*
** EPITECH PROJECT, 2023
** B-PSU-200 : 42sh
** File description:
** Terminal canonical mode management
*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "line_buffer.h"
#include "history.h"
#include "utils.h"
#include "canonical_mod.h"

/**
  * Initialize the terminal session
  * @param line Line buffer structure
  * @param history History structure
  * @param envp Environment variables
  * @param original Original terminal settings
  * @return 0 on success, -1 on failure
*/
static int init_canonical(
    line_buffer_t *line,
    history_t *history,
    char ***envp,
    struct termios *original
)
{
    initialize_session(line, history, envp);
    if (setup_terminal(original, line, history, *envp) == -1) {
        cleanup_session(line, history, original);
        return -1;
    }
    return 0;
}

/**
  * Process input character
  * @param c Input character
  * @param line Line buffer structure
  * @param history History structure
  * @param envp Environment variables
  * @return 1 if exit condition met, 0 otherwise
*/
void input_loop(line_buffer_t *line, history_t *history, char ***envp)
{
    char c = 0;
    int should_exit = 0;

    while (!should_exit) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            should_exit = process_input_char(c, line, history, envp);
    }
}

/**
  * Handle input in canonical mode
  * @param envp Environment variables
*/
void handle_input(char ***envp)
{
    line_buffer_t line = {0};
    history_t history = {0};
    struct termios original = {0};

    initialize_session(&line, &history, envp);
    if (setup_terminal(&original, &line, &history, *envp) == -1) {
        cleanup_session(&line, &history, &original);
        return;
    }
    input_loop(&line, &history, envp);
    cleanup_session(&line, &history, &original);
}

/**
  * Handle newline character
  * @param line Line buffer structure
  * @param history History structure
  * @param original Original terminal settings
  * @param envp Environment variables
  * @return Input string on success, NULL on failure
*/
static char *handle_newline(line_buffer_t *line, history_t *history,
    struct termios *original, char ***envp)
{
    char *input = NULL;

    printf("\n");
    if (line->length > 0) {
        input = strdup(line->buffer);
        cleanup_session(line, history, original);
        return input;
    }
    print_prompt(*envp);
    fflush(stdout);
    return NULL;
}

/**
  * Handle escape sequence
  * @param line Line buffer structure
  * @param history History structure
  * @param envp Environment variables
  * @return 0 on success, -1 on failure
*/
static void handle_backspace(line_buffer_t *line, char ***envp)
{
    line_process_backspace(line);
    redraw_line(line, *envp);
}

/**
  * Process normal character input
  * @param c Input character
  * @param line Line buffer structure
  * @param envp Environment variables
*/
static int process_canonical_char(
    char c,
    terminal_context_t *ctx,
    char **input
)
{
    if (c == 27)
        return handle_escape_sequence(ctx->line, ctx->history, *(ctx->envp));
    if (c == '\n') {
        *input = handle_newline(ctx->line, ctx->history, ctx->original,
            ctx->envp);
        if (*input != NULL)
            return 1;
    }
    if (c == 4 && ctx->line->length == 0) {
        printf("\n");
        cleanup_session(ctx->line, ctx->history, ctx->original);
        return 1;
    }
    if (c == 127 || c == 8)
        handle_backspace(ctx->line, ctx->envp);
    else
        process_normal_char(c, ctx->line, ctx->envp);
    return 0;
}

/**
  * Process input character in canonical mode
  * @param c Input character
  * @param ctx Terminal context structure
  * @param input Pointer to store the input string
  * @return 1 if exit condition met, 0 otherwise
*/
char *canonical_input(char ***envp)
{
    line_buffer_t line = {0};
    history_t history = {0};
    struct termios original = {0};
    terminal_context_t context = {.line = &line, .history = &history,
        .original = &original, .envp = envp};
    char *input = NULL;
    char c = 0;
    int should_exit = 0;

    if (init_canonical(&line, &history, envp, &original) == -1)
        return NULL;
    while (!should_exit) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            should_exit = process_canonical_char(c, &context, &input);
        if (should_exit && input != NULL)
            return input;
    }
    cleanup_session(&line, &history, &original);
    return NULL;
}

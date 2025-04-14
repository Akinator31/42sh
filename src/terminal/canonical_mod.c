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
#include "canonique_mod.h"

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

void input_loop(line_buffer_t *line, history_t *history, char ***envp)
{
    char c = 0;
    int should_exit = 0;

    while (!should_exit) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            should_exit = process_input_char(c, line, history, envp);
    }
}

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

static void handle_backspace(line_buffer_t *line, char ***envp)
{
    line_process_backspace(line);
    redraw_line(line, *envp);
}

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

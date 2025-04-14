/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** main
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include "commands.h"
#include "canonical_mod.h"

/**
 * Process a command line input
 * @param buffer The command to process
 * @param ctx Shell context containing environment and file descriptors
 * @return EXIT if command is exit, 0 otherwise
 */
static int process_command(char *buffer, shell_context_t *ctx)
{
    int result_command;

    if (!buffer)
        return EXIT;
    my_write_history(buffer, ctx->envp);
    result_command = analyse_command(ctx->envp, buffer, ctx->error_code);
    restore_stdin_stdout_fd(ctx->stdin_cpy, ctx->stdout_cpy);
    if (result_command == EXIT) {
        free(buffer);
        return EXIT;
    }
    return 0;
}

/**
 * Read input in canonical mode with advanced features
 * @param ctx Shell context
 * @return The error code
 */
static int handle_canonical_sh(shell_context_t *ctx)
{
    char *buffer = NULL;

    buffer = canonical_input(ctx->envp);
    while (buffer != NULL) {
        if (process_command(buffer, ctx) == EXIT) {
            close_fds(2, ctx->stdin_cpy, ctx->stdout_cpy);
            return EXIT;
        }
        free(buffer);
        buffer = canonical_input(ctx->envp);
    }
    return *(ctx->error_code);
}

/**
 * Read input in non-canonical mode (pipes or redirections)
 * @param ctx Shell context
 * @return The error code
 */
static int handle_tty_sh(shell_context_t *ctx)
{
    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, stdin) != -1) {
        if (process_command(buffer, ctx) == EXIT) {
            close_fds(2, ctx->stdin_cpy, ctx->stdout_cpy);
            return EXIT;
        }
        free(buffer);
        buffer = NULL;
    }
    free(buffer);
    return *(ctx->error_code);
}

/**
 * Initialize shell context with environment and backup file descriptors
 * @param ctx Pointer to shell context structure
 * @param envp Pointer to environment variables
 * @param error_code Pointer to store error code
 * @return 0 on success, -1 on failure
 */
static int init_shell_context(
    shell_context_t *ctx,
    char ***envp,
    int *error_code
)
{
    ctx->envp = envp;
    ctx->error_code = error_code;
    ctx->stdin_cpy = duplicate_file_descriptor(STDIN_FILENO);
    ctx->stdout_cpy = duplicate_file_descriptor(STDOUT_FILENO);
    if (ctx->stdin_cpy == -1 || ctx->stdout_cpy == -1)
        return -1;
    return 0;
}

/**
 * Main shell function
 * @param envp Pointer to environment variables
 * @param error_code Pointer to store error code
 * @return EXIT_EOF when shell exits
 */
int mysh(char ***envp, int *error_code)
{
    shell_context_t ctx = {0};
    int result = 0;

    if (init_shell_context(&ctx, envp, error_code) == -1) {
        *error_code = 84;
        return EXIT_EOF;
    }
    if (isatty(STDIN_FILENO))
        result = handle_canonical_sh(&ctx);
    else
        result = handle_tty_sh(&ctx);
    close_fds(2, ctx.stdin_cpy, ctx.stdout_cpy);
    return EXIT_EOF;
}

/**
 * Program entry point
 * @param ac Argument count
 * @param av Argument vector
 * @param envp Environment variables
 * @return Error code
 */
int main(int ac, char **av, char **envp)
{
    char **env = NULL;
    int error_code = 0;
    int mysh_exit_status = 0;

    if (ac > 1)
        return 84;
    env = duplicate_2d_char_array(envp, get_2d_arr_len(envp) + 1);
    if (!env)
        return 84;
    mysh_exit_status = mysh(&env, &error_code);
    if (mysh_exit_status == EXIT_EOF && isatty(STDIN_FILENO))
        write(1, "exit\n", 5);
    free_2d_array_of_char(env);
    return error_code;
}

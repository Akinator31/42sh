/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Backtick command substitution header
*/

#ifndef BACKTICK_H_
    #define BACKTICK_H_
    #include "mysh.h"
    #include <sys/types.h>
    #define READ_END 0
    #define WRITE_END 1

typedef struct {
    char *processed_cmd;
    char *backtick_cmd;
    char *backtick_pos;
    int full_length;
} backtick_params_t;

/* Main functions */
char *process_backticks(sh_t *sh_c);
char *find_backsticks(char *processed_cmd, char *backtick_pos,
    sh_t *sh_c);
char *find_next_backtick(char *command);
char *extract_backtick_command(char *backtick_start, int *cmd_length,
    int *full_length);
char *substitute_backtick(char *original, char *start, int full_length,
    char *replacement);

/* Utility functions */
int setup_child_process(int pipefd[2]);
void cleanup_pipe_resources(int pipefd[2], int original_stdout);
char *execute_and_capture_output(char *cmd, sh_t *sh_c);
int setup_capture_pipes(int pipefd[2], int *original_stdout);
void execute_child_command(int pipefd[2], char *cmd, char ***envp,
    config_rc_t *config);
char *handle_parent_process(int pipefd[2], pid_t pid, int original_stdout);

/* Reading functions */
char *read_pipe_output(int pipe_fd, ssize_t bytes_read, char *buffer,
    size_t *total_size);

#endif /* BACKTICK_H_ */

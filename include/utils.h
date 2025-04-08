/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** utils
*/

#ifndef INCLUDED_UTILS_H
    #define INCLUDED_UTILS_H
    #include <stdbool.h>

bool is_good_cmd(char *cmd, char *prompt);
char *get_environ_var(const char *name, const char *value);
char *get_environ_variable_value(char ***envp, char *variable);
void env(char **envp);
char *get_binary_name(char *command);
int get_index_of_environment_variable(char **envp, char *environment_variable);
void print_prompt(char **envp);
void *my_memset(void *pointer, int value, size_t size);
int my_setenv(char ***envp, const char *name, const char *value,
    int overwrite);
void my_free(void *ptr, ...);
char *get_binary(char ***envp, char *command);
int change_dir(char *path_to_directory, char *current_directory,
    char *old_directory, int *error_code);
int change_directory_to_env(char *variable);
int is_too_much_args(int nb_args, char **command_element, int *error_code);
void errno_manager(int exec_return, char **command_element);
void handle_simple_left_redirection(char *command);
void handle_simple_right_redirection(char *command);
void handle_double_right_redirection(char *command);
int handle_pipes(char *command, char ***envp, int *error_code);
int handle_semicolons(char *command, char ***envp, int *error_code);
int duplicate_file_descriptor(int fd);
void restore_stdin_stdout_fd(int stdin_cpy, int stdout_cpy);
void close_fds(int nb_elements, ...);
void my_dup2(int oldfd, int newfd);

#endif

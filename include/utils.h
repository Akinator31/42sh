/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** utils
*/

#ifndef INCLUDED_UTILS_H
    #define INCLUDED_UTILS_H
    #include <stdbool.h>
    #include <stddef.h>
    #include "mysh.h"
    #define FAILURE -1
    #define SUCCESS 1

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
char *get_binary(char ***envp, char **command);
int change_dir(char *path_to_directory, char *current_directory,
    char *old_directory, int *error_code);
int change_directory_to_env(char *variable);
int is_too_much_args(int nb_args, char **command_element, int *error_code);
void errno_manager(int exec_return, char **command_element);
int handle_simple_left_redirection(char *command, int *status);
int handle_simple_right_redirection(char *command, int *status);
int handle_double_right_redirection(char *command, int *status);
int handle_pipes(char *command, char ***envp, int *error_code,
    config_rc_t *config);
int handle_semicolons(char *command, char ***envp, int *error_code,
    config_rc_t *config);
int duplicate_file_descriptor(int fd);
int restore_stdin_stdout_fd(int stdin_cpy, int stdout_cpy);
void close_fds(int nb_elements, ...);
int my_dup2(int oldfd, int newfd);
struct tm *my_gettime(void);
size_t count_lines(char *path);
char **handle_command(sh_t *sh_st);
int skip_inhib(char *str);
int get_inhib_len(char *str);
char **my_str_to_word_array_inhib(char *str, char *delim_list,
    int nb_inhib);
char *get_inhib_content(char *command);
int search_inhib(char *command);
int my_pipe(int pipefd[2]);
char *retrieve_history_path(char ***envp);
int check_meta_format(char *command, char *meta);
int env_var_already_exist(char ***envp, const char *variable);
void handle_env_var_call(char **command_array, char **env);
bool my_strislowercase(char *str);
bool my_strisuppercase(char *str);
void add_alias(config_rc_t *config, char *args);
config_rc_t *load_rc(char **env);
char *my_strcat_malloc(char *str1, char *str2);
void free_config_st(config_rc_t *config);
bool is_alias_command(sh_t *sh_st, exit_status_t *status);

#endif

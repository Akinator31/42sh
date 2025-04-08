/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** mysh
*/

#ifndef INCLUDED_MYSH_H
    #define INCLUDED_MYSH_H
    #include <stdbool.h>
    #define IS_A_TTY_OFFSET -10
    #define IS_NOT_A_TTY_OFFSET 0

typedef enum {
    NORMAL,
    EXIT,
    EXIT_EOF,
    NOTHING,
} exit_status_t;

typedef struct {
    char flag;
    void (*f)(char ***, char *, int *, int);
    char *variable;
} my_cd_t;

typedef struct {
    char *builtins_name;
    bool (*f)(char ***, char *, exit_status_t *, int *);
} my_builtins_t;


exit_status_t analyse_command(char ***evnp, char *command,
    int *error_code);
void cd_to_directory(char ***envp,
    char *path_to_directory, int *error_code, int is_variable);

#endif

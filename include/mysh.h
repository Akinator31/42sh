/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** mysh
*/

#ifndef INCLUDED_MYSH_H
    #define INCLUDED_MYSH_H
    #include <stdbool.h>
    #include <sys/types.h>
    #define IS_A_TTY_OFFSET -10
    #define IS_NOT_A_TTY_OFFSET 0
    #define INIBITHORS_CHAR 39
    #define HOME_VAR "HOME"
    #define RC_FILE_NAME ".42shrc"
    #define LEN_HOME_VAR 5

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


typedef struct shell_context_s {
    char ***envp;
    int *error_code;
    int stdin_cpy;
    int stdout_cpy;
} shell_context_t;

typedef struct {
    char *alias_name;
    char *command;
    uint nb_alias;
} alias_t;

typedef struct {
    alias_t *alias;
} config_rc_t;

typedef struct {
    char *key_word;
    void (*f)(config_rc_t *, char *);
} config_element_t;

typedef struct {
    char ***envp;
    char *command;
    int *error_code;
    config_rc_t *config;
} sh_t;

typedef struct {
    char *builtins_name;
    bool (*f)(sh_t *, exit_status_t *);
} my_builtins_t;

exit_status_t analyse_command(char ***evnp, char *command,
    int *error_code, config_rc_t *config);
void cd_to_directory(char ***envp,
    char *path_to_directory, int *error_code, int is_variable);

#endif

/*
** EPITECH PROJECT, 2025
** B-PSU-200 : 42sh
** File description:
** canonique_mod
*/

#ifndef CANONIQUE_MOD_H_
    #define CANONIQUE_MOD_H_
    #include "history.h"
    #include "line_buffer.h"
    #include <termios.h>

typedef struct {
    line_buffer_t *line;
    history_t *history;
    struct termios *original;
    char ***envp;
} terminal_context_t;

int enable_raw_mode(struct termios *original);
int disable_raw_mode(struct termios *original);
void handle_input(char ***envp);
void redraw_line(line_buffer_t *line, char **envp);
void handle_arrow_keys(char seq[2], line_buffer_t *line,
    history_t *history, char **envp);
void process_ctrl_keys(char c, line_buffer_t *line, int *should_exit);
void initialize_session(line_buffer_t *line, history_t *history,
    char ***envp);
void cleanup_session(line_buffer_t *line, history_t *history,
    struct termios *original);
int setup_terminal(struct termios *original, line_buffer_t *line,
    history_t *history, char **envp);
void process_normal_char(char c, line_buffer_t *line, char ***envp);
int process_input_char(char c, line_buffer_t *line,
    history_t *history, char ***envp);
char *canonical_input(char ***envp);
int handle_escape_sequence(line_buffer_t *line, history_t *history,
    char **envp);
#endif /* !CANONIQUE_MOD_H_ */

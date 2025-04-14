/*
** EPITECH PROJECT, 2025
** B-PSU-200 : 42sh
** File description:
** line_buffer
*/

#ifndef LINE_BUFFER_H_
    #define LINE_BUFFER_H_
    #define LINE_BUF_SIZE 1024
    #include <stddef.h>

typedef struct {
    char *buffer;
    int position;
    int length;
} line_buffer_t;

void line_buffer_init(line_buffer_t *line);
void line_buffer_free(line_buffer_t *line);
void line_clear(line_buffer_t *line);
void line_display(line_buffer_t *line);
void line_insert_char(line_buffer_t *line, char c);
void line_process_backspace(line_buffer_t *line);
void line_process_enter(line_buffer_t *line, void *history, char ***envp);
void line_cursor_left(line_buffer_t *line);
void line_cursor_right(line_buffer_t *line);
void line_set_content(line_buffer_t *line, const char *content);

#endif /* !LINE_BUFFER_H_ */

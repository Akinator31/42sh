/*
** EPITECH PROJECT, 2025
** B-PSU-200 : 42sh
** File description:
** my_history
*/

#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

static bool check_first_char(char c)
{
    if (!c)
        return false;
    if (my_isspace(c) || my_isnewline(c))
        return false;
    return true;
}

static void write_history(char *logpath, struct stat *sb)
{
    size_t bytes = (size_t)sb->st_size;
    char *buffer = malloc(bytes + 1);
    int fd = 0;
    ssize_t read_bytes = 0;

    fd = open(logpath, O_RDONLY);
    if (fd == -1) {
        free(buffer);
        return;
    }
    read_bytes = read(fd, buffer, bytes);
    if (read_bytes == -1) {
        free(buffer);
        close(fd);
        return;
    }
    buffer[read_bytes] = '\0';
    write(STDOUT_FILENO, buffer, (size_t)read_bytes);
    free(buffer);
    close(fd);
}

static FILE *get_history_file(char *history_file_path)
{
    FILE *stream = fopen(history_file_path, "a");

    if (stream == NULL) {
        perror("Error opening history file");
        return NULL;
    }
    return stream;
}

bool is_history_command(sh_t *sh_st, exit_status_t *status)
{
    char *logpath = NULL;
    struct stat sb = {0};

    if (!is_good_cmd("history", sh_st->command))
        return false;
    logpath = retrieve_history_path(sh_st->envp);
    if (!logpath)
        return false;
    stat(logpath, &sb);
    if (sb.st_size <= 0) {
        free(logpath);
        return 0;
    }
    write_history(logpath, &sb);
    free(logpath);
    return true;
}

void my_write_history(char *line, char ***envp)
{
    char *history_file_path = retrieve_history_path(envp);
    FILE *stream = NULL;
    size_t len = 0;
    struct tm *time = my_gettime();

    if (!history_file_path)
        return;
    stream = get_history_file(history_file_path);
    if (stream == NULL)
        return free(history_file_path);
    if (!check_first_char(line[0]))
        return;
    len = count_lines(history_file_path);
    if (fprintf(stream, "\t%ld\t%d:%d\t%s\n",
        len, time->tm_hour, time->tm_min, line) < 0)
        perror("Can't write into history file");
    fclose(stream);
    free(history_file_path);
}

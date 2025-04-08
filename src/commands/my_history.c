/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-kevin.salanier
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

static bool check_first_char(char c)
{
    if (!c)
        return false;
    if (c == ' ' || c == '\t' || c == '\v' || c == '\n')
        return false;
    return true;
}

static char *retrive_history_path(char ***envp)
{
    char *homepath = get_environ_variable_value(envp, "HOME");
    char *logpath = NULL;

    if (!homepath)
        homepath = "/tmp/";
    logpath = malloc(sizeof(char) * my_strlen(homepath) + 16);
    logpath = my_strcpy(logpath, homepath);
    logpath = my_strcat(logpath, "/.42sh_history");
    return logpath ? logpath : NULL;
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

bool is_history_command(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    char *logpath = NULL;
    struct stat sb = {0};

    if (!is_good_cmd("history", command))
        return false;
    logpath = retrive_history_path(envp);
    if (!logpath)
        return false;
    stat(logpath, &sb);
    if (sb.st_size <= 0)
        return 0;
    write_history(logpath, &sb);
    free(logpath);
    return true;
}

void my_write_history(char *line, char ***envp)
{
    char *history_file_path = retrive_history_path(envp);
    FILE *stream = NULL;
    size_t len = 0;

    if (!history_file_path)
        return;
    stream = get_history_file(history_file_path);
    if (stream == NULL) {
        free(history_file_path);
        return;
    }
    if (!check_first_char(line[0]))
        return;
    if (fprintf(stream, "\t%s", line) < 0)
        perror("Can't write into history file");
    fclose(stream);
    free(history_file_path);
}

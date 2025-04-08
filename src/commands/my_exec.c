/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_exec
*/

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

void exit_manager(int status, pid_t pid, int *error_code)
{
    if (!WIFEXITED(status)) {
        *error_code = 128 + WTERMSIG(status);
        my_putstr(strsignal(WTERMSIG(status)), 2);
        write(2, "\n", 1);
        return;
    }
    *error_code = WEXITSTATUS(status);
    kill(pid, 0);
}

void launch_binary(char ***envp, char *binary_path,
    char **command_element, int *error_code)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(binary_path, command_element, *envp);
        if (exec_return != 0) {
            perror(binary_path);
            free_2d_array_of_char(command_element);
            exit(exec_return);
        }
        free_2d_array_of_char(command_element);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
        exit_manager(status, pid, error_code);
    }
    return;
}

void launch_file(char ***envp, char **command_element, int *error_code)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(command_element[0], command_element, *envp);
        errno_manager(exec_return, command_element);
        free_2d_array_of_char(command_element);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
        exit_manager(status, pid, error_code);
    }
    return;
}

int check_binary(char *path)
{
    int fd = open(path, O_RDONLY, 0);
    char *buffer = malloc(sizeof(char) * 5);
    struct stat info;

    stat(path, &info);
    if (fd == -1 || !S_ISREG(info.st_mode)) {
        free(buffer);
        return 1;
    }
    my_memset(buffer, 0, 5);
    read(fd, buffer, 4);
    close(fd);
    if (my_strcmp("ELF", buffer + 1) == 0) {
        free(buffer);
        return 1;
    }
    write(2, path, my_strlen(path));
    write(2, ": Exec format error. Binary file not executable.\n", 49);
    free(buffer);
    return 0;
}

void my_exec(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    char **command_element = str_to_word_array(command, " \n\t");
    char *binary_path = get_binary(envp, command);

    if (!binary_path || command[0] == '.') {
        if (!check_binary(command_element[0])) {
            *error_code = 84;
            return;
        }
        launch_file(envp, command_element, error_code);
    } else {
        if (!check_binary(binary_path)) {
            *error_code = 84;
            return;
        }
        launch_binary(envp, binary_path, command_element, error_code);
    }
    if (binary_path)
        free(binary_path);
}

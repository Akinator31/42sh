/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Utility functions for backtick command substitution
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char *allocate_initial_output(void)
{
    char *output;

    output = malloc(1);
    if (output != NULL)
        output[0] = '\0';
    return output;
}

static ssize_t read_from_pipe(int pipe_fd, char *buffer, size_t size)
{
    ssize_t bytes_read;

    bytes_read = read(pipe_fd, buffer, size - 1);
    return bytes_read;
}

static char *grow_output_buffer(char *output, size_t new_size)
{
    char *new_output;

    new_output = realloc(output, new_size);
    return new_output;
}

static void copy_to_output(
    char *dest,
    const char *src,
    size_t offset,
    size_t length
)
{
    memcpy(dest + offset, src, length);
    dest[offset + length] = '\0';
}

static char *handle_read_failure(char *output, int pipe_fd)
{
    free(output);
    close(pipe_fd);
    return NULL;
}

char *read_pipe_output(int pipe_fd, ssize_t bytes_read, char *buffer,
    size_t *total_size)
{
    char *output = NULL;
    char *new_output = NULL;

    output = allocate_initial_output();
    if (output == NULL)
        return NULL;
    bytes_read = read_from_pipe(pipe_fd, buffer, sizeof(char[1024]));
    while (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        new_output = grow_output_buffer(output, *total_size + bytes_read + 1);
        if (new_output == NULL)
            return handle_read_failure(output, pipe_fd);
        output = new_output;
        copy_to_output(output, buffer, *total_size, bytes_read);
        *total_size += bytes_read;
        bytes_read = read_from_pipe(pipe_fd, buffer, sizeof(char[1024]));
    }
    close(pipe_fd);
    return output;
}

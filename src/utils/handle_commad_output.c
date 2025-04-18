/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_commad_output
*/

#include "mysh.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * Handle the output of a command
 * @param result_command The result of the command execution
 * @param buffer The command buffer
 * @param envp Pointer to environment variables
 * @return 0 on success, EXIT on exit command
 */
int handle_output_command(int result_command, char *buffer, char ***envp)
{
    if (result_command == EXIT) {
        free(buffer);
        return EXIT;
    }
    if (result_command == NORMAL && isatty(STDIN_FILENO))
        print_prompt(*envp);
    if (result_command == NOTHING)
        return 0;
    return 0;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Backtick command substitution
*/

#include "backtick.h"
#include "mysh.h"
#include <string.h>

char *process_backticks(sh_t *sh_c)
{
    char *processed_cmd = NULL;
    char *backtick_pos = NULL;

    if (!sh_c->command)
        return NULL;
    processed_cmd = strdup(sh_c->command);
    if (!processed_cmd)
        return NULL;
    do {
        backtick_pos = find_next_backtick(processed_cmd);
        if (!backtick_pos)
            break;
        processed_cmd = find_backsticks(processed_cmd, backtick_pos, sh_c);
        if (!processed_cmd)
            return NULL;
    } while (backtick_pos);
    return processed_cmd;
}

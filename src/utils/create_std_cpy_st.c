/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_std_cpy_st
*/

#include "mysh.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

std_cpy_t *set_std_cpy_st(void)
{
    std_cpy_t *std_cpy_st = malloc(sizeof(std_cpy_t));

    std_cpy_st->stdin_cpy = duplicate_file_descriptor(STDIN_FILENO);
    std_cpy_st->stdout_cpy = duplicate_file_descriptor(STDOUT_FILENO);
    return std_cpy_st;
}

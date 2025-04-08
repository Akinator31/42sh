/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** is_good_command
*/

#include <stdbool.h>
#include "mysh.h"
#include "my_lib.h"

bool is_good_cmd(char *cmd, char *prompt)
{
    char **prompt_elt = str_to_word_array(prompt, " \n\t");
    int is_correct_cmd = 0;

    if (get_2d_arr_len(prompt_elt) == 0) {
        free_2d_array_of_char(prompt_elt);
        return false;
    }
    is_correct_cmd = my_strcmp(cmd, prompt_elt[0]);
    if (is_correct_cmd == 0) {
        free_2d_array_of_char(prompt_elt);
        return true;
    }
    free_2d_array_of_char(prompt_elt);
    return false;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_command
*/

#include "my_lib.h"
#include "mysh.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void print_long_alias_name(char *alias, char *command,
    bool *print_parenthese)
{
    if (*print_parenthese == true) {
        *print_parenthese = false;
        printf("%s (%s)\n", alias, command);
        return;
    }
    printf("%s %s\n", alias, command);
}

static void print_alias_list(alias_t *alias)
{
    char **word_array = NULL;
    bool print_parenthese = false;

    for (uint i = 0; i < alias->nb_alias; i++) {
        word_array = str_to_word_array(alias[i].command, " \t");
        if (get_2d_arr_len(word_array) > 1)
            print_parenthese = true;
        if (strlen(alias[i].alias_name) > 7) {
            print_long_alias_name(alias[i].alias_name, alias[i].command,
                &print_parenthese);
            continue;
        }
        if (print_parenthese) {
            printf("%-8s(%s)\n", alias[i].alias_name, alias[i].command);
            print_parenthese = false;
            continue;
        }
        printf("%-8s%s\n", alias[i].alias_name, alias[i].command);
        free_2d_array_of_char(word_array);
    }
}

static void alias_cmd(char **word_array, sh_t *sh_st)
{
    int len = get_2d_arr_len(word_array);

    if (len == 1) {
        print_alias_list(sh_st->config->alias);
        return;
    }
}

bool is_alias_command(sh_t *sh_st, exit_status_t *status)
{
    char **word_array = str_to_word_array(sh_st->command, " \n\t");

    if (!word_array || my_strcmp(word_array[0], "alias") != 0)
        return false;
    alias_cmd(word_array, sh_st);
    return true;
}

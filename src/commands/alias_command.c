/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_command
*/

#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
            free_2d_array_of_char(word_array);
            continue;
        }
        if (print_parenthese) {
            printf("%-8s(%s)\n", alias[i].alias_name, alias[i].command);
            print_parenthese = false;
        } else
            printf("%-8s%s\n", alias[i].alias_name, alias[i].command);
        free_2d_array_of_char(word_array);
    }
}

static void show_this_alias_command(char *alias_name, alias_t *alias)
{
    for (uint i = 0; i < alias->nb_alias; i++) {
        if (strcmp(alias_name, alias[i].alias_name) == 0) {
            printf("%s\n", alias[i].command);
            return;
        }
    }
}

static void first_alias(config_rc_t *config, char *alias_name, char *content)
{
    config->alias = malloc(sizeof(alias_t));
    if (!config->alias)
        return;
    config->alias[0].alias_name = my_strdup(alias_name);
    config->alias[0].command = my_strdup(content);
    config->alias->nb_alias = 1;
}

static void add_alias_by_built_in(char *alias_name, char *content,
    config_rc_t *config)
{
    if (!content)
        return;
    if (config->alias == NULL) {
        first_alias(config, alias_name, content);
        return;
    }
    config->alias = realloc(config->alias,
        sizeof(alias_t) * (config->alias->nb_alias + 1));
    if (!config->alias)
        return;
    config->alias[config->alias->nb_alias].alias_name = my_strdup(alias_name);
    config->alias[config->alias->nb_alias].command = my_strdup(content);
    config->alias->nb_alias = config->alias->nb_alias + 1;
}

static void alias_cmd(char **word_array, sh_t *sh_st)
{
    int len = get_2d_arr_len(word_array);
    char **content = NULL;

    if (len == 1) {
        print_alias_list(sh_st->config->alias);
        return;
    }
    if (len == 2) {
        show_this_alias_command(word_array[1], sh_st->config->alias);
        return;
    }
    if (len >= 3) {
        content = str_to_word_array(strstr(sh_st->command,
            "alias") + LEN_ALIAS, " \t");
        add_alias_by_built_in(content[0], strstr(sh_st->command,
            content[0]) + strlen(content[0]) + 1, sh_st->config);
        free_2d_array_of_char(content);
    }
}

bool is_alias_command(sh_t *sh_st, exit_status_t *status)
{
    char **word_array = str_to_word_array(sh_st->command, " \n\t");

    if (!word_array)
        return false;
    if (my_strcmp(word_array[0], "alias") != 0) {
        free_2d_array_of_char(word_array);
        return false;
    }
    if (!sh_st->config || !sh_st->config->alias ||
        sh_st->config->alias->nb_alias < 1) {
        free_2d_array_of_char(word_array);
        return true;
    }
    alias_cmd(word_array, sh_st);
    free_2d_array_of_char(word_array);
    return true;
}

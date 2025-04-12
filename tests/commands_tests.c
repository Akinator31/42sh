/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** commands_tests
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"
#include "utils.h"
#include "commands.h"
#include "my_lib.h"

extern char **environ;

Test(analyse_command, basic_analyse_command)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;

    cr_assert_eq(analyse_command(&env, "/bin/ls", &error_code), NORMAL);
}

Test(analyse_command_, basic_analyse_command_pipe)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;

    cr_assert_eq(analyse_command(&env, "ls | cat -e", &error_code), NORMAL);
}

Test(is_cd_command, is_cd_command_false)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;
    exit_status_t *status = malloc(sizeof(exit_status_t));
    if (status == NULL)
        cr_assert_fail("Memory allocation for status failed");

    cr_assert_eq(is_cd_command(&env, "ls", status, &error_code), false);
    free(status);
}

Test(is_cd_command, is_cd_command_true)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;
    exit_status_t *status = malloc(sizeof(exit_status_t));
    if (status == NULL)
        cr_assert_fail("Memory allocation for status failed");;

    cr_assert_eq(is_cd_command(&env, "cd", status, &error_code), true);
    free(status);
}

Test(is_env_command, is_env_command_false)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;
    exit_status_t *status = malloc(sizeof(exit_status_t));
    if (status == NULL)
        cr_assert_fail("Memory allocation for status failed");

    cr_assert_eq(is_env_command(&env, "ls", status, &error_code), false);
    free(status);
}

Test(is_env_command, is_env_command_true)
{
    char **env = duplicate_2d_char_array(environ, get_2d_arr_len(environ));
    int error_code = 1;
    exit_status_t *status = malloc(sizeof(exit_status_t));
    if (status == NULL)
        cr_assert_fail("Memory allocation for status failed");

    cr_assert_eq(is_env_command(&env, "env", status, &error_code), true);
    free(status);
}

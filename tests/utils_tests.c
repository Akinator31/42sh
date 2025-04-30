/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** utils_tests
*/

#include <criterion/criterion.h>
#include "utils.h"

extern char **environ;

Test(handle_semicolons, basic_handle_semicolons)
{
    int error_code = 0;
    int return_value = handle_semicolons("ls ; echo abc", &environ, &error_code, NULL);

    cr_assert_eq(return_value, 1);
}

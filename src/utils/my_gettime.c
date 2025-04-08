/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_gettime
*/

#include "utils.h"
#include <time.h>

struct tm *my_gettime(void)
{
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    return tm_struct;
}

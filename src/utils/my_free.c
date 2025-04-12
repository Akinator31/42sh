/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_free
*/


#include <stdlib.h>
#include <stdarg.h>

void my_free(void *ptr, ...)
{
    int i = 0;
    void *temp_data = ptr;
    va_list data_list;

    va_start(data_list, ptr);
    while (temp_data) {
        free(temp_data);
        temp_data = va_arg(data_list, void *);
    }
    va_end(data_list);
}

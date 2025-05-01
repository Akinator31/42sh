/*
** EPITECH PROJECT, 2024
** function of my lib Gomes Noah
** File description:
** my_str_to_word_array
*/

#include "mysh.h"
#include "utils.h"
#include "my_lib.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int is_a_delim(const char c, const char *delim_list)
{
    int i = 0;

    while (delim_list[i] != '\0') {
        if (delim_list[i] == c)
            return 1;
        i++;
    }
    return 0;
}

static int skip_delim(char *str, int i, char *delim_list)
{
    while (str[i] != '\0' && is_a_delim(str[i], delim_list) == 1)
        i++;
    return i;
}

static int count_slot_up_or_no(char *str, int i, int count_slot)
{
    if (count_slot > 1 && str[i] == 39)
        return count_slot;
    if (str[i] != '\0')
        return count_slot + 1;
    return count_slot;
}

static int count_slot(char *str, char *delim_list, int nb_inhib)
{
    int i = 0;
    int count_slot = 0;

    if (is_a_delim(str[i], delim_list) == 1 && str[i + 1] != '\0')
        i = skip_delim(str, i, delim_list);
    while (str[i] != '\0') {
        if (str[i] == INIBITHORS_CHAR) {
            i += skip_inhib(str + i);
            count_slot = count_slot_up_or_no(str, i, count_slot);
            continue;
        }
        if (is_a_delim(str[i], delim_list) == 1 && str[i + 1] != '\0') {
            i = skip_delim(str, i, delim_list);
            count_slot = count_slot_up_or_no(str, i, count_slot);
            continue;
        }
        i++;
    }
    return count_slot;
}

static int count_size(char *str, char *delim_list)
{
    int i = 0;

    while (str[i] != '\0' && is_a_delim(str[i], delim_list) != 1)
        i++;
    return i;
}

static char *fill_str(int *j, char *str, char *delim_list)
{
    int i = 0;
    int len = count_size(str + *j, delim_list);
    char *new_str = malloc(sizeof(char) * len + 1);

    while (str[*j] != '\0' && i != len) {
        new_str[i] = str[*j];
        i++;
        *j = *j + 1;
    }
    new_str[i] = '\0';
    return new_str;
}

static int check_empty_word_array(char *str, char *delim_list)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] != 0 && is_a_delim(str[i], delim_list) == 0)
            return 0;
        i++;
    }
    return 1;
}

static char **handle_empty_word_array(char **word_array, char *delim_list)
{
    if (check_empty_word_array(word_array[0], delim_list) == 1) {
        free_2d_array_of_char(word_array);
        return NULL;
    }
    return word_array;
}

char **my_str_to_word_array_inhib(char *str, char *delim_list,
    int nb_inhib)
{
    int nb_slots = count_slot(str, delim_list, nb_inhib);
    int i = 0;
    int j = 0;
    char **word_array = malloc(sizeof(char *) * (nb_slots + 1));

    if (is_a_delim(str[0], delim_list) == 1)
        j = skip_delim(str, j, delim_list);
    while (i != nb_slots) {
        if (str[j] == INIBITHORS_CHAR) {
            word_array[i] = get_inhib_content(str + j);
            j += skip_inhib(str + j);
        } else
            word_array[i] = fill_str(&j, str, delim_list);
        j = skip_delim(str, j, delim_list);
        i++;
    }
    free(str);
    word_array[i] = NULL;
    return handle_empty_word_array(word_array, delim_list);
}

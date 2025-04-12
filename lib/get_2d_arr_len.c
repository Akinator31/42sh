/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** get_2d_arr_len
*/

int get_2d_arr_len(char **arr)
{
    int i = 0;
    int size = 0;

    while (arr[i]) {
        size++;
        i++;
    }
    return size;
}

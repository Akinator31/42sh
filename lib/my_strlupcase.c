/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strlupcase
*/

int my_strupcase(char *str)
{
    int i;
    int len = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z'))
            str[i] = str[i] - 32;
        len += 1;
    }
    return len;
}

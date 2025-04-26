/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strlowcase
*/

int my_strlowcase(char *str)
{
    int i;
    int len = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
            str[i] = str[i] + 32;
        len += 1;
    }
    return len;
}

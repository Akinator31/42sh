/*
** EPITECH PROJECT, 2025
** my_strcat.c
** File description:
** lib
*/

char *my_strcat(char *dest, char const *src)
{
    int i = 0;

    while (dest[i] != '\0')
        i++;
    if (!src)
        return dest;
    for (int e = 0; src[e] != '\0'; e++) {
        dest[i] = src[e];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

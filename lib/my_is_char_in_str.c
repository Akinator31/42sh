/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_is_char_in_str
*/

int my_is_char_in_str(char *string, char character)
{
    int i = 0;

    while (string[i] != '\0') {
        if (character == string[i])
            return 1;
        i++;
    }
    return 0;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal_mode
*/

#include <unistd.h>
#include <sys/termios.h>

int enable_raw_mode(struct termios *original)
{
    struct termios raw = {0};

    if (tcgetattr(STDIN_FILENO, original) == -1)
        return -1;
    raw = *original;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

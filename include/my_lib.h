/*
** EPITECH PROJECT, 2025
** my_printf.h
** File description:
** task02
*/

#ifndef MY_LIB_H
    #define MY_LIB_H
    #include <sys/types.h>
    #define STR sizeof(char *)

int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char **my_str_to_word_array(char const *str, char *separator);
int get_2d_arr_len(char **arr);
void free_2d_array_of_char(char **arr);
char *my_strdup(char const *src);
char *my_strcat(char *dest, char const *src);
char **duplicate_2d_char_array(char **array, int new_size);
int my_is_char_in_str(char *string, char character);
char *my_strstr(char *str, char const *to_find);
char *my_strcpy(char *dest, char const *src);
void my_putstr(char const *str, int output);
int my_str_isalpha(char const *str);
int my_isalpha(char c);
void my_write_min(char *str, int output);
char **str_to_word_array(const char *string, const char *separators);
void *my_memcpy(void *dest, const void *src, size_t size);
void *my_realloc(void *pointer, size_t memory_size, size_t original_size);
void *my_memset(void *pointer, int value, size_t size);

#endif

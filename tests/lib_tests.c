/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** lib_tests
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_lib.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_strcmp, basic_my_strcmpt_test)
{
    cr_assert_eq(my_strcmp("super_string", "super_string"), 0);
}

Test(test_free_2d, test_basic)
{
    char **word_array = str_to_word_array("ceci est un test", " ");
    free_2d_array_of_char(word_array);
    word_array = NULL;
    cr_assert_null(word_array);
}

Test(get_2d_arr_len, basic_test_get_2d_arr_len)
{
    char *string = "bonjour";
    char **string_element = str_to_word_array(string, " ");

    cr_assert_eq(get_2d_arr_len(string_element), 1);
    free_2d_array_of_char(string_element);
}

Test(my_isalpha, basic_test_myisalpha)
{
    char test = 'A';
    char test2 = 'a';
    char test3 = '1';
    char test4 = '\\';

    cr_assert_eq(my_isalpha(test), 1);
    cr_assert_eq(my_isalpha(test2), 1);
    cr_assert_eq(my_isalpha(test3), 1);
    cr_assert_eq(my_isalpha(test4), 0);
}

Test(my_memset, basic_test_my_memset)
{
    char *string = malloc(sizeof(char) * 20);

    my_memset(string, 0, 20);
    string[20] = '\0';
    for (int i = 0; string[i] != '\0'; i++)
        cr_assert_eq(string[i], 0);
    free(string);
}

Test(my_str_isalpha, basic_test_my_str_is_alpha)
{
    char *string = "BONJOUR";
    char *string2 = "";
    char *string3 = "122344566";
    char *string4 = "bonjour";

    cr_assert_eq(my_str_isalpha(string), 1);
    cr_assert_eq(my_str_isalpha(string2), 1);
    cr_assert_eq(my_str_isalpha(string3), 0);
    cr_assert_eq(my_str_isalpha(string4), 1);
}

Test(my_is_char_in_str, basic_test_my_is_char_in_str)
{

    char *string = "Ceci est une string";
    char test = 'z';
    char test1 = 'u';

    cr_assert_eq(my_is_char_in_str(string, test), 0);
    cr_assert_eq(my_is_char_in_str(string, test1), 1);
}

Test(my_putstr, basic_test_my_putstr, .init=redirect_all_std)
{
    my_putstr("Ceci est un test enorme !", STDOUT_FILENO);
    cr_assert_stdout_eq_str("Ceci est un test enorme !");
}

Test(my_realloc, basic_test_my_realloc)
{
    int *pointer = NULL;
    
    pointer = my_realloc(pointer, sizeof(int), sizeof(int));
    cr_assert_not_null(pointer);
}

Test(free_2d_array_of_char, basic_test_free_2d_array_of_char)
{
    char **arr = NULL;

    free_2d_array_of_char(arr);
    cr_assert_null(arr);
}

Test(my_strcmp, basic_my_strcmpt_test_2)
{
    cr_assert_eq(my_strcmp("super_string", "super_string"), 0);
    cr_assert_eq(my_strcmp(NULL, NULL), -1);
    cr_assert_eq(my_strcmp("A", "B"), -1);
}

Test(test_free_2d, test_basic_2)
{
    char **word_array = my_str_to_word_array("ceci est un test", " ");
    free_2d_array_of_char(word_array);
    word_array = NULL;
    cr_assert_null(word_array);
}

Test(get_2d_arr_len, basic_test_get_2d_arr_len_2)
{
    char *string = "bonjour";
    char **string_element = my_str_to_word_array(string, " ");

    cr_assert_eq(get_2d_arr_len(string_element), 1);
    free_2d_array_of_char(string_element);
}

Test(my_memset, basic_test_my_memset_2)
{
    char *string = malloc(sizeof(char) * 20);

    my_memset(string, 0, 20);
    string[20] = '\0';
    for (int i = 0; string[i] != '\0'; i++)
        cr_assert_eq(string[i], 0);
    free(string);
}

Test(my_str_to_word_array, my_str_to_word_array_with_null_string)
{
    char **string = my_str_to_word_array(NULL, NULL);

    cr_assert_null(string);
}

Test(my_strcat, basic_test_my_strcat)
{
    char *string1 = malloc(sizeof(char) * 8);
    char *string2 = "ça va ?";

    string1[0] = 'H';
    my_strcat(string1, string2);
    cr_assert_str_eq(string1, "Hça va ?");
}

Test(my_strcat, null_test_my_strcat)
{
    char *string = "Salut";

    my_strcat(string, NULL);
    cr_assert_str_eq(string, "Salut");
}

Test(my_strcpy, basic_test_my_strcpy)
{
    char *string = "Salut";
    char *result = malloc(sizeof(char) * 6);

    my_strcpy(result, string);
    cr_assert_str_eq(string, result);
}

Test(my_strlen, null_test_my_strlen)
{
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(my_strstr, basic_test_my_strstr)
{
    char *string = "String de mega test Noah";

    cr_assert_str_eq(my_strstr(string, "String"), string);
    cr_assert_str_eq(my_strstr(string, ""), string);
    cr_assert_null(my_strstr(string, "egzrg"));
}

Test(my_write_min, basic_test_my_write_min, .init=redirect_all_std)
{
    char *string = "BONJOUR";

    my_write_min(string, STDOUT_FILENO);
    cr_assert_stdout_eq_str("bonjour");
}

Test(str_to_word_array, null_test_str_to_word_array)
{
    char **string = str_to_word_array(NULL, NULL);
    char **string2 = str_to_word_array("salut", NULL);

    cr_assert_null(string);
    cr_assert_null(string2);
}

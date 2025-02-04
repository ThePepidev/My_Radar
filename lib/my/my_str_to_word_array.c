/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** my_str_to_word_array.c
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static void increment_count(char str, char separator, int *count)
{
    if (str == separator)
        (*count)++;
}

static int count_separators(char *str, char *separator)
{
    int separator_count = 1;

    for (int i = 0; str[i]; i++) {
        for (int j = 0; separator[j]; j++) {
            increment_count(str[i], separator[j], &separator_count);
        }
    }
    return separator_count;
}

static int verify_skip(char str, char *separator)
{
    int skip = 0;

    for (int x = 0; separator[x]; x++) {
        if (separator[x] == str) {
            skip = 1;
            return skip;
        }
    }
    return skip;
}

static int write_array(char *array, char str, int *n, int skip)
{
    if (skip != 1) {
        array[*n] = str;
        (*n)++;
        return 0;
    }
    return 1;
}

static int len_word(char *str, int k, char *separator)
{
    int len = k;
    int end = 0;

    for (; str[len]; len++) {
        end = verify_skip(str[len], separator);
        if (end == 1)
            break;
    }
    return (len + 1);
}

static void skip_separator(char *separator, char *str, int *k)
{
    while (str[*k] && verify_skip(str[*k], separator) == 1) {
        (*k)++;
    }
}

static void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

static char *allocate_word(char *str, int *k, char *separator)
{
    int len = len_word(str, *k, separator);
    char *word = malloc(sizeof(char) * len);
    int n = 0;

    if (!word)
        return NULL;
    for (; str[*k] && verify_skip(str[*k], separator) != 1; (*k)++) {
        word[n] = str[*k];
        n++;
    }
    word[n] = '\0';
    skip_separator(separator, str, k);
    return word;
}

char **my_str_to_word_array(char *str, char *separator)
{
    int separator_count = count_separators(str, separator);
    char **array = malloc(sizeof(char *) * (separator_count + 1));
    int k = 0;

    if (!array)
        return NULL;
    for (int l = 0; l < separator_count; l++) {
        array[l] = allocate_word(str, &k, separator);
        if (!array[l]) {
            free_array(array);
            return NULL;
        }
    }
    array[separator_count] = NULL;
    return array;
}

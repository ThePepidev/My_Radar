/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** check_file.c
*/

#include "my.h"
#include "my_radar.h"

void my_free_word_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static int check_line_content(char *line)
{
    char **tokens = my_str_to_word_array(line, " ");
    int token_count = 0;

    for (int i = 0; tokens[i]; i++)
        token_count++;
    if (line[0] == 'A' && token_count != 7) {
        my_free_word_array(tokens);
        return 84;
    }
    if (line[0] == 'T' && token_count != 4) {
        my_free_word_array(tokens);
        return 84;
    }
    my_free_word_array(tokens);
    return 0;
}

static int check_line(char *line)
{
    if (!line)
        return 84;
    if (line[0] != 'A' && line[0] != 'T')
        return 84;
    for (int i = 1; line[i]; i++) {
        if (line[i] == ' ')
            continue;
        if (line[i] == '\n')
            continue;
        if ((line[i] < '0' || line[i] > '9') && line[i] != '.')
            return 84;
    }
    return check_line_content(line);
}

int check_file(char **av)
{
    FILE *fd = fopen(av[1], "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (!fd)
        return 84;
    nread = getline(&line, &len, fd);
    while (nread != -1) {
        if (check_line(line) == 84) {
            free(line);
            fclose(fd);
            return 84;
        }
        nread = getline(&line, &len, fd);
    }
    fclose(fd);
    free(line);
    return 0;
}

/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** plane_info.c
*/

#include "my_radar.h"
#include "my.h"

static void attribut_info(char *line, plane_t **new_node)
{
    char **array = my_str_to_word_array(line, " ");
    float temp_1 = my_getfloat(array[1]);
    float temp_2 = my_getfloat(array[2]);

    (*new_node)->spawn = (sfVector2f){temp_1, temp_2};
    (*new_node)->current = (*new_node)->spawn;
    temp_1 = my_getfloat(array[3]);
    temp_2 = my_getfloat(array[4]);
    (*new_node)->final = (sfVector2f){temp_1, temp_2};
    (*new_node)->speed = my_getfloat(array[5]);
    (*new_node)->delay = my_getfloat(array[6]);
    (*new_node)->end = false;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void getplane_info(plane_t **new_node, int count, char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    int current = 1;
    size_t len = 0;
    ssize_t nread;

    if (!file)
        return;
    nread = getline(&line, &len, file);
    for (; nread != -1; nread = getline(&line, &len, file)) {
        if (line[0] != 'A')
            continue;
        if (current == count)
            break;
        current++;
    }
    attribut_info(line, new_node);
    free(line);
    fclose(file);
}

int getplane_nb(char *filepath)
{
    FILE *file = fopen(filepath, "r");
    static int count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = getline(&line, &len, file);

    if (count != 0) {
        free(line);
        return count;
    }
    while (nread != -1) {
        if (line[0] == 'A')
            count++;
        nread = getline(&line, &len, file);
    }
    free(line);
    return count;
}

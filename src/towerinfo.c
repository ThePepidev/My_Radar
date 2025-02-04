/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** getinfo.c
*/

#include "my_radar.h"
#include "my.h"

static char *getradiusfrom_line(char *line)
{
    int number_space = 0;
    int i = 0;
    int j = 0;
    char *temp = malloc(sizeof(char) * my_strlen(line));

    if (!temp)
        return NULL;
    for (; number_space != 3 && line[i]; i++) {
        if (line[i] == ' ')
            number_space++;
    }
    if (number_space != 3)
        return NULL;
    for (; line[i]; i++) {
        temp[j] = line[i];
        j++;
    }
    temp[j] = '\0';
    free(line);
    return temp;
}

static char *getradius_loop(int count, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = getline(&line, &len, file);
    int current = 1;

    while (nread != -1) {
        if (line[0] != 'T') {
            nread = getline(&line, &len, file);
            continue;
        }
        if (current == count)
            break;
        current++;
        nread = getline(&line, &len, file);
    }
    return line;
}

float getradius_fromfile(char *filepath, int count)
{
    char *line = NULL;
    FILE *file = fopen(filepath, "r");
    char *number;
    float radius = 0;

    line = getradius_loop(count, file);
    fclose(file);
    number = getradiusfrom_line(line);
    radius = my_getfloat(number);
    free(number);
    return radius;
}

static sfVector2f getposfrom_line(char *line)
{
    int i = 0;
    int j = 0;
    int space_number = 0;
    int x = my_getnbr(line);
    char *temp = malloc(sizeof(char) * my_strlen(line));
    int y = 0;

    for (; space_number != 2 && line[i]; i++) {
        if (line[i] == ' ')
            space_number++;
    }
    for (; line[i]; i++) {
        temp[j] = line[i];
        j++;
    }
    temp[j] = '\0';
    y = my_getnbr(temp);
    free(temp);
    return (sfVector2f){x, y};
}

static char *getpos_loop(FILE *file, int count)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = getline(&line, &len, file);
    int current = 1;

    while (nread != -1) {
        if (line[0] != 'T') {
            nread = getline(&line, &len, file);
            continue;
        }
        if (current == count)
            break;
        current++;
        nread = getline(&line, &len, file);
    }
    return line;
}

sfVector2f getpos_fromfile(char *filepath, int count)
{
    char *line = NULL;
    FILE *file = fopen(filepath, "r");
    sfVector2f position;

    line = getpos_loop(file, count);
    fclose(file);
    position = getposfrom_line(line);
    free(line);
    return position;
}

int get_towers_nb(char *filepath)
{
    static int count = 0;
    char *line = NULL;
    FILE *file = fopen(filepath, "r");
    size_t len = 0;
    ssize_t nread = getline(&line, &len, file);

    if (count != 0) {
        free(line);
        return count;
    }
    while (nread != -1) {
        if (line[0] == 'T') {
            count++;
        }
        nread = getline(&line, &len, file);
    }
    free(line);
    return count;
}

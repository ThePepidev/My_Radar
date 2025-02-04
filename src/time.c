/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** time.c
*/

#include "my_radar.h"
#include "my.h"

static int len_nbr(float *nb_copy)
{
    int len_nb = 0;

    while (*nb_copy >= 1.0) {
        (*nb_copy) /= 10.0;
        len_nb++;
    }
    return len_nb;
}

static char *str_cat(char *str1, char *str2)
{
    int len_all = my_strlen(str1) + my_strlen(str2);
    char *result = malloc(len_all + 1);

    my_strcpy(result, str1);
    my_strcat(result, str2);
    free(str2);
    return result;
}

static void copy_nbr(char *str, float nb_copy, int len_nb)
{
    int temp;
    int i = 0;

    for (; i < len_nb; i++) {
        temp = (int)nb_copy;
        nb_copy = (nb_copy - temp) * 10;
        str[i] = (nb_copy + 48);
    }
    str[i] = '\0';
}

static char *cast_to_str(int nb)
{
    float nb_copy = (float)nb;
    char *str;
    int len_nb = len_nbr(&nb_copy);

    if (nb == 0)
        return "00";
    if (nb == 33)
        return "33";
    str = malloc(sizeof(char) * (len_nb + 1));
    if (!str)
        return NULL;
    copy_nbr(str, nb_copy, len_nb);
    if (nb < 10)
        return str_cat("0", str);
    return str;
}

static void free_strings(char *str, char *hours, char *min, char *sec)
{
    if (my_strcmp(hours, "00") != 0 && my_strcmp(hours, "33") != 0)
        free(hours);
    if (my_strcmp(min, "00") != 0 && my_strcmp(min, "33") != 0)
        free(min);
    if (my_strcmp(sec, "00") != 0 && my_strcmp(sec, "33") != 0)
        free(sec);
    free(str);
}

static void display_clock(int secondes,
    int minutes, int heures, radar_t *radar)
{
    char *sec = cast_to_str(secondes);
    char *min = cast_to_str(minutes);
    char *hours = cast_to_str(heures);
    char *str = malloc(sizeof(char) * 9);

    if (!str || !hours || !sec || !min)
        return;
    my_strcpy(str, hours);
    my_strcat(str, ":");
    my_strcat(str, min);
    my_strcat(str, ":");
    my_strcat(str, sec);
    if (!radar->time_clock)
        return;
    sfText_setString(radar->time_clock, str);
    sfText_setFont(radar->time_clock, radar->pixel_font);
    sfText_setColor(radar->time_clock, sfBlack);
    sfText_setCharacterSize(radar->time_clock, 95);
    sfText_setPosition(radar->time_clock, (sfVector2f){1320, 50});
    free_strings(str, hours, min, sec);
}

void clock_draw(radar_t *radar)
{
    int total_secondes = radar->elapsed;
    int secondes = 0;
    int minutes = 0;
    int heures = 0;

    minutes = (total_secondes / 60) % 60;
    secondes = total_secondes % 60;
    heures = total_secondes / 3600;
    display_clock(secondes, minutes, heures, radar);
}

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
    return result;
}

static char *cast_to_str(int nb)
{
    int temp;
    float nb_copy = (float)nb;
    char *str;
    int i = 0;
    int len_nb = len_nbr(&nb_copy);

    if (nb == 0)
        return "00";
    if (nb == 33)
        return "33";
    str = malloc(len_nb + 1);
    for (; i < len_nb; i++) {
        temp = (int)nb_copy;
        nb_copy = (nb_copy - temp) * 10;
        str[i] = (nb_copy + 48);
    }
    str[i] = '\0';
    if (nb < 10)
        return str_cat("0", str);
    return str;
}

static void display_clock(int secondes,
    int minutes, int heures, radar_t *radar)
{
    char *sec = cast_to_str(secondes);
    char *min = cast_to_str(minutes);
    char *hours = cast_to_str(heures);
    char *str = str_cat(hours, ":");

    str = str_cat(str, min);
    str = str_cat(str, ":");
    str = str_cat(str, sec);
    if (!radar->time_clock)
        return;
    sfText_setString(radar->time_clock, str);
    sfText_setFont(radar->time_clock, radar->pixel_font);
    sfText_setColor(radar->time_clock, sfBlack);
    sfText_setCharacterSize(radar->time_clock, 95);
    sfText_setPosition(radar->time_clock, (sfVector2f){1320, 50});
}

void clock_draw(radar_t *radar)
{
    int total_secondes =
    sfTime_asSeconds(sfClock_getElapsedTime(radar->clock));
    int secondes = 0;
    int minutes = 0;
    int heures = 0;

    minutes = (total_secondes / 60) % 60;
    secondes = total_secondes % 60;
    heures = total_secondes / 3600;
    display_clock(secondes, minutes, heures, radar);
}

/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** init.c
*/

#include "my_radar.h"

sfSprite *create_sprite_from_file(sfTexture **temp, char *filepath)
{
    sfSprite *sprite = sfSprite_create();

    *temp = sfTexture_createFromFile(filepath, NULL);
    if (!filepath || !*temp)
        return NULL;
    sfSprite_setTexture(sprite, *temp, sfTrue);
    return sprite;
}

void update_timer(radar_t *radar, sfTime *pausedTime)
{
    static int first = 0;

    if (!radar->pause) {
            radar->elapsed =
            sfTime_asSeconds(sfClock_getElapsedTime(radar->clock))
            + sfTime_asSeconds(*pausedTime);
            first = 0;
        } else {
            if (first == 0)
                (*pausedTime).microseconds +=
                sfClock_getElapsedTime(radar->clock).microseconds;
            sfClock_restart(radar->clock);
            first++;
        }
}

radar_t *init_radar_struct(void)
{
    radar_t *temp = malloc(sizeof(radar_t));

    if (!temp)
        return NULL;
    temp->disp_hitbox = true;
    temp->disp_sprite = true;
    temp->background = create_sprite_from_file(&temp->back_text,
    "templates/map.jpg");
    temp->clock = sfClock_create();
    temp->P_clock = sfClock_create();
    temp->time_clock = sfText_create();
    temp->pixel_font =
    sfFont_createFromFile("templates/enter-the-gungeon-small.ttf");
    temp->pausedTime = sfTime_Zero;
    temp->pause = false;
    if (!temp->clock || !temp->back_text ||
    !temp->background || !temp->P_clock)
        return NULL;
    return temp;
}

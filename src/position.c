/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** position.c
*/

#include "my_radar.h"
#include "my.h"
#include <math.h>

int check_ending(plane_t *planes)
{
    plane_t *current = planes;

    while (current) {
        if ((current->current.x - current->final.x) <= 1.0f &&
        (current->current.y - current->final.y) <= 1.0f)
            current->end = true;
        current = current->next;
    }
    return 0;
}

static void update_length(sfVector2f *direction, float *length)
{
    *length = sqrt(direction->x
    * direction->x + direction->y * direction->y);
    if (*length != 0) {
        direction->x /= *length;
        direction->y /= *length;
    }
}

void update_position(radar_t radar, plane_t *current, float delta_time)
{
    sfVector2f direction;
    float length;
    sfVector2f move;
    float elapsed_time = radar.elapsed;

    if (elapsed_time >= current->delay) {
        direction = (sfVector2f){current->final.x -
        current->spawn.x, current->final.y - current->spawn.y};
        update_length(&direction, &length);
        move = (sfVector2f){direction.x * current->speed * delta_time,
        direction.y * current->speed * delta_time};
        sfSprite_move(current->Psprite, move);
        current->current.x += move.x;
        current->current.y += move.y;
        sfRectangleShape_setPosition(current->hitbox,
        (sfVector2f){current->current.x - 1, current->current.y - 4});
    }
}

/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** angle.c
*/

#include "my_radar.h"
#include "my.h"
#include <math.h>

void rotate_plane(plane_t *planes)
{
    plane_t *current = planes;
    float dx;
    float dy;
    float angle;

    for (; current; current = current->next) {
        if (current->end)
            continue;
        dx = current->final.x - current->current.x;
        dy = current->final.y - current->current.y;
        angle = atan2(dy, dx) * 180 / M_PI;
        sfSprite_setOrigin(current->Psprite, (sfVector2f){9.5, 5.5});
        sfSprite_setPosition(current->Psprite, current->current);
        sfSprite_setRotation(current->Psprite, angle);
        sfRectangleShape_setOrigin(current->hitbox, (sfVector2f){10, 10});
        sfRectangleShape_setPosition(current->hitbox, current->current);
        sfRectangleShape_setRotation(current->hitbox, angle);
    }
}

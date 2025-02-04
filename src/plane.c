/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** plane.c
*/

#include "my.h"
#include "my_radar.h"
#include <math.h>

void draw_planes(radar_t radar, plane_t *planes, sfRenderWindow *window)
{
    if (radar.disp_sprite && !planes->end)
        sfRenderWindow_drawSprite(window, planes->Psprite, NULL);
    if (radar.disp_hitbox && !planes->end)
        sfRenderWindow_drawRectangleShape(window, planes->hitbox, NULL);
}

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

void update_planes(radar_t radar, plane_t *planes)
{
    sfVector2f direction;
    float length;
    float delta_time = sfTime_asSeconds(sfClock_restart(radar.P_clock));
    sfVector2f move;
    float elapsed_time = sfTime_asSeconds(sfClock_getElapsedTime(radar.clock));

    for (plane_t *current = planes; current; current = current->next) {
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
}

static sfRectangleShape *create_hitbox(sfVector2f pos)
{
    sfRectangleShape *hitbox = sfRectangleShape_create();

    sfRectangleShape_setSize(hitbox, (sfVector2f){20.0f, 20.0f});
    sfRectangleShape_setPosition(hitbox, (sfVector2f){pos.x - 1, pos.y - 4});
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(hitbox, sfBlack);
    sfRectangleShape_setOutlineThickness(hitbox, 2.0f);
    return hitbox;
}

static sfTexture *rand_texture(void)
{
    int random = rand() % 2;
    sfTexture *temp;

    if (random > 0)
        temp = sfTexture_createFromFile("templates/latios.png", NULL);
    else
        temp = sfTexture_createFromFile("templates/latias.png", NULL);
    return temp;
}

static int add_node(plane_t **planes, int count, char **args)
{
    plane_t *new_node = malloc(sizeof(plane_t));
    plane_t *current = *planes;

    if (!new_node)
        return 84;
    new_node->next = NULL;
    getplane_info(&new_node, count, args[1]);
    new_node->hitbox = create_hitbox(new_node->spawn);
    new_node->Ptexture = rand_texture();
    new_node->Psprite = sfSprite_create();
    sfSprite_setTexture(new_node->Psprite, new_node->Ptexture, sfTrue);
    sfSprite_setPosition(new_node->Psprite, new_node->spawn);
    if (!current)
        *planes = new_node;
    else {
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    return 0;
}

plane_t *create_all_planes(char **args)
{
    plane_t *planes = NULL;
    static int plane_nb = 0;
    int count = 0;
    int check = 0;

    srand(time(NULL));
    plane_nb = getplane_nb(args[1]);
    for (int i = 0; i < plane_nb; i++) {
        count++;
        check = add_node(&planes, count, args);
        if (check == 84)
            return NULL;
    }
    return planes;
}

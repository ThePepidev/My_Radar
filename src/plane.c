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

void kill_plane(plane_t **planes)
{
    plane_t *current = *planes;
    plane_t *temp;

    // Free planes at the beginning of the list
    while (current && current->end) {
        temp = current;
        current = current->next;
        sfSprite_destroy(temp->Psprite);
        sfTexture_destroy(temp->Ptexture);
        sfRectangleShape_destroy(temp->hitbox);
        free(temp);
    }

    *planes = current; // Update the head of the list

    // Free planes in the middle or end of the list
    while (current && current->next) {
        if (current->next->end) {
            temp = current->next;
            current->next = current->next->next;
            sfSprite_destroy(temp->Psprite);
            sfTexture_destroy(temp->Ptexture);
            sfRectangleShape_destroy(temp->hitbox);
            free(temp);
        } else {
            current = current->next;
        }
    }
}

void update_planes(radar_t *radar, tower_t *towers, plane_t *planes)
{
    plane_t *current = planes;
    float delta_time = sfTime_asSeconds(sfClock_restart(radar->P_clock));

    for (; current; current = current->next) {
        if (current->end)
            continue;
        update_position(*radar, current, delta_time);
        rotate_plane(current);
        collision(towers, radar, current);
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

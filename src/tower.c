/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** circle.c
*/

#include "my_radar.h"

static sfCircleShape *create_circle(float width,
    float height, float radius, sfVector2f pos)
{
    sfCircleShape *temp = sfCircleShape_create();

    sfCircleShape_setFillColor(temp, sfColor_fromRGBA(255, 255, 255, 0));
    sfCircleShape_setOutlineThickness(temp, 3.0);
    sfCircleShape_setOutlineColor(temp, sfBlack);
    sfCircleShape_setRadius(temp, radius);
    sfCircleShape_setPosition(temp,
    (sfVector2f){pos.x + (width / 2) - radius, pos.y + (height / 2) - radius});
    return temp;
}

static void init_sprite(tower_t **new_node, sfVector2f pos)
{
    (*new_node)->Ttexture =
    sfTexture_createFromFile("templates/tower.png", NULL);
    (*new_node)->Tsprite = sfSprite_create();
    sfSprite_setTexture((*new_node)->Tsprite, (*new_node)->Ttexture, sfTrue);
    sfSprite_setPosition((*new_node)->Tsprite, pos);
}

static void add_node(tower_t **towers, int count, char **av)
{
    tower_t *new_node = malloc(sizeof(tower_t));
    tower_t *current = *towers;
    float radius = getradius_fromfile(av[1], count);
    sfVector2f pos = getpos_fromfile(av[1], count);

    if (!new_node)
        return;
    new_node->pos = pos;
    new_node->radius = radius;
    init_sprite(&new_node, pos);
    new_node->circle = create_circle(22.0f, 30.0f, radius, pos);
    new_node->next = NULL;
    if (current == NULL) {
        *towers = new_node;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

tower_t *create_all_towers(char **av)
{
    tower_t *towers = NULL;
    static int towers_count = 0;
    int count = 0;

    towers_count = get_towers_nb(av[1]);
    for (int i = 0; i < towers_count; i++) {
        count++;
        add_node(&towers, count, av);
        if (!towers)
            return NULL;
    }
    return towers;
}

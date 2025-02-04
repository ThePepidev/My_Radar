/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** collision.c
*/

#include "my_radar.h"
#include <math.h>

static int in_tower(plane_t *current, tower_t *curr_tower)
{
    float distance_1 = sqrt((current->current.x - curr_tower->pos.x) *
    (current->current.x - curr_tower->pos.x) +
    (current->current.y - curr_tower->pos.y) *
    (current->current.y - curr_tower->pos.y));

    if (distance_1 <= curr_tower->radius)
        return 1;
    return 0;
}

static int check_towers(plane_t *current, tower_t *towers)
{
    tower_t *curr_tower = towers;

    for (; curr_tower; curr_tower = curr_tower->next) {
        if (in_tower(current, curr_tower)) {
            return 1;
        }
    }
    return 0;
}

static hitbox_t getbound(plane_t *plane)
{
    hitbox_t bound;

    bound.left = plane->current.x - 10.0f;
    bound.top = plane->current.y - 10.0f;
    bound.right = plane->current.x + 10.0f;
    bound.bot = plane->current.y + 10.0f;
    return bound;
}

static int is_collision(plane_t *current, plane_t *other)
{
    hitbox_t hit_current = getbound(current);
    hitbox_t hit_other = getbound(other);

    if ((current->current.x - other->current.x) > sqrt(200) ||
        (current->current.y - other->current.y) > sqrt(200))
        return 0;
    if (hit_current.right >= hit_other.left &&
        hit_current.left <= hit_other.right &&
        hit_current.bot >= hit_other.top &&
        hit_current.top <= hit_other.bot) {
        return 1;
    }
    return 0;
}

static int check_collision(plane_t *current, tower_t *towers, float elapsed)
{
    for (plane_t *other = current->next; other; other = other->next) {
        if (other->end)
            continue;
        if (elapsed < other->delay)
            continue;
        if (check_towers(other, towers))
            continue;
        if (is_collision(current, other)) {
            other->end = true;
            return 1;
        }
    }
    return 0;
}

void collision(tower_t *towers, radar_t *radar, plane_t *current)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(radar->clock));

    if (elapsed < current->delay)
        return;
    if (check_towers(current, towers))
        return;
    if (check_collision(current, towers, elapsed))
        current->end = true;
}

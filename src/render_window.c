/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** render_window.c
*/

#include "my_radar.h"
#include "my.h"

static void handle_events(sfRenderWindow *window, radar_t *radar)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed ||
        (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            radar->disp_hitbox = !radar->disp_hitbox;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            radar->disp_sprite = !radar->disp_sprite;
    }
}

static void draw_all(sfRenderWindow *window,
    tower_t *towers, radar_t radar, plane_t *planes)
{
    plane_t *current_plane = planes;

    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, radar.background, NULL);
    sfRenderWindow_drawText(window, radar.time_clock, NULL);
    while (towers) {
        if (radar.disp_sprite)
            sfRenderWindow_drawSprite(window, towers->Tsprite, NULL);
        if (radar.disp_hitbox)
            sfRenderWindow_drawCircleShape(window, towers->circle, NULL);
        towers = towers->next;
    }
    while (current_plane) {
        if (sfTime_asSeconds(sfClock_getElapsedTime(radar.clock)) >=
        current_plane->delay) {
            draw_planes(radar, current_plane, window);
        }
        current_plane = current_plane->next;
    }
    sfRenderWindow_display(window);
}

static void free_lists(tower_t *towers, plane_t *planes)
{
    void *temp;

    while (towers) {
        sfSprite_destroy(towers->Tsprite);
        sfTexture_destroy(towers->Ttexture);
        sfCircleShape_destroy(towers->circle);
        temp = towers;
        towers = towers->next;
        free(temp);
    }
    while (planes) {
        sfSprite_destroy(planes->Psprite);
        sfTexture_destroy(planes->Ptexture);
        sfRectangleShape_destroy(planes->hitbox);
        temp = planes;
        planes = planes->next;
        free(temp);
    }
}

static void free_all(plane_t *planes,
    tower_t *towers, radar_t *radar, sfRenderWindow *window)
{
    free_lists(towers, planes);
    sfText_destroy(radar->time_clock);
    sfFont_destroy(radar->pixel_font);
    sfClock_destroy(radar->clock);
    sfClock_destroy(radar->P_clock);
    sfSprite_destroy(radar->background);
    sfTexture_destroy(radar->back_text);
    free(radar);
    sfRenderWindow_destroy(window);
}

int render_window(char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window =
        sfRenderWindow_create(mode, "My_Radar", sfClose, NULL);
    tower_t *towers = create_all_towers(av);
    plane_t *planes = create_all_planes(av);
    radar_t *radar = init_radar_struct();

    if (!window || !towers || !planes || !radar)
        return 84;
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        handle_events(window, radar);
        update_planes(radar, towers, planes);
        clock_draw(radar);
        check_ending(planes);
        draw_all(window, towers, *radar, planes);
    }
    free_all(planes, towers, radar, window);
    return 0;
}

/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** my_radar.h
*/

#ifndef MY_RADAR_H
    #define MY_RADAR_H

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <stdbool.h>
    #include <time.h>

typedef struct plane_s {
    sfRectangleShape *hitbox;
    int delay;
    float speed;
    sfVector2f current;
    sfVector2f spawn;
    sfVector2f final;
    sfSprite *Psprite;
    bool end;
    sfTexture *Ptexture;
    struct plane_s *next;
} plane_t;

typedef struct tower_s {
    float radius;
    sfTexture *Ttexture;
    sfSprite *Tsprite;
    sfVector2f pos;
    sfCircleShape *circle;
    struct tower_s *next;
} tower_t;

typedef struct radar_s {
    bool disp_hitbox;
    bool disp_sprite;
    sfSprite *background;
    sfTexture *back_text;
    sfClock *clock;
    sfClock *P_clock;
} radar_t;

int render_window(char **av);
tower_t *create_all_towers(char **av);
sfSprite *create_sprite_from_file(sfTexture **temp, char *filepath);
float getradius_fromfile(char *filepath, int count);
sfVector2f getpos_fromfile(char *filepath, int count);
int get_towers_nb(char *filepath);
int getplane_nb(char *filepath);
void getplane_info(plane_t **new_node, int count, char *filepath);
plane_t *create_all_planes(char **args);
radar_t *init_radar_struct(void);
void draw_planes(radar_t radar, plane_t *planes, sfRenderWindow *window);
void update_planes(radar_t radar, plane_t *planes);
int check_ending(plane_t *planes);

#endif /* !MY_RADAR_H */

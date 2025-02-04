/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** main.c
*/

#include "my_radar.h"
#include "my.h"

static void print_help(void)
{
    my_putstr("Air traffic simulation panel\n\n");
    my_putstr("USAGE\n");
    my_putstr("    ./my_radar [OPTIONS]\n\n");
    my_putstr("OPTIONS\n");
    my_putstr("    -h    print the usage and quit.\n\n");
    my_putstr("USER INTERACTIONS\n");
    my_putstr("    LEFT_ARROW    switch to the previous tower.\n");
    my_putstr("    RIGHT_ARROW    switch to the next tower.\n");
    my_putstr("    UP_ARROW    increase the radar range.\n");
    my_putstr("    DOWN_ARROW    decrease the radar range.\n");
    my_putstr("    R    reset the radar range.\n");
    my_putstr("    SPACE    pause the simulation.\n");
    my_putstr("    ESCAPE    close the window.\n");
}

int main(int ac, char **av, char **env)
{
    if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0) {
            print_help();
            return 0;
        }
        if (is_tty(env))
            return 84;
        if (verif_assets() == 84)
            return 84;
        if (check_file(av) == 84)
            return 84;
        if (render_window(av) == 84)
            return 84;
    } else {
        my_putstr("Error: Wrong number of arguments\n");
        return (84);
    }
    return (0);
}

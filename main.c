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
    my_putstr("    ./my_radar [OPTIONS]\n");
    my_putstr("    path_to_script The path to the script file.\n\n");
    my_putstr("OPTIONS\n");
    my_putstr("    -h    print the usage and quit.\n\n");
    my_putstr("USER INTERACTIONS\n");
    my_putstr("    `L' key enable/disable hitboxes and areas.\n");
    my_putstr("    `S' key enable/disable sprites\n");
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

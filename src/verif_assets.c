/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** verif_asset.c
*/

#include "my.h"
#include <fcntl.h>
#include "my_radar.h"

static int verif_file(char *filepath)
{
    FILE *fd = fopen(filepath, "r");

    if (!fd)
        return 84;
    fclose(fd);
    return 0;
}

int verif_assets(void)
{
    if (verif_file("templates/latias.png") == 84)
        return 84;
    if (verif_file("templates/latios.png") == 84)
        return 84;
    if (verif_file("templates/map.jpg") == 84)
        return 84;
    if (verif_file("templates/tower.png") == 84)
        return 84;
    if (verif_file("templates/enter-the-gungeon-small.ttf") == 84)
        return 84;
    return 0;
}

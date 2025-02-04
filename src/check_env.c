/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-mathys1.dupont
** File description:
** check_env.c
*/

#include "my_radar.h"
#include "my.h"

int is_tty(char **env)
{
    int i = 0;

    if (!env)
        return 1;
    while (env[i]) {
        if (my_strncmp(env[i], "DISPLAY=", 8) == 0)
            return 0;
        i++;
    }
    return 1;
}

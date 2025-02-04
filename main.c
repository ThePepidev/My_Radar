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

static long getfilesize(char *filepath)
{
    struct stat file_stat;

    if (stat(filepath, &file_stat) != -1) {
        return file_stat.st_size;
    }
    return -1;
}

static int check_file(char **av)
{
    int fd;
    int fo;
    long size = getfilesize(av[1]);
    char *buffer;

    if (size == -1 || !av[1])
        return 84;
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return 84;
    buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer)
        return 84;
    fo = read(fd, buffer, size);
    buffer[size] = '\0';
    if (fo == -1 || my_strlen(buffer) == 0)
        return 84;
    free(buffer);
    close(fd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0) {
            print_help();
            return 0;
        }
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

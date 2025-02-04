/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** get nbr
*/

#include <math.h>
#include <stdio.h>

static int decimal_number(char const *str, int *i, double *nb)
{
    double decimal = 0.0;

    if (str[*i - 1] < 48 || str[*i - 1] > 57)
        return 0;
    else if (str[*i] == '.' && str[*i + 1] >= 48 && str[*i + 1] <= 57)
            decimal++;
    while (decimal > 0 && str[*i + 1] >= 48 && str[*i + 1] <= 57) {
        *nb += (str[*i + 1] - 48) * pow(0.1, decimal);
        (*i)++;
        decimal++;
    }
    return 0;
}

double my_getfloat(char const *str)
{
    double nb = 0.0;
    int neg = 0;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-')
            neg++;
        while (str[i] >= 48 && str[i] <= 57) {
            nb *= 10;
            nb += str[i] - 48;
            i++;
        }
        decimal_number(str, &i, &nb);
        if (neg != 0)
            nb *= (-1);
        if (nb != 0)
            return nb;
    }
    return 0;
}

//
// Created by tom billard on 13/12/2016.
//

#include <life.h>

void    print_map(t_env *env)
{
    int x = 0;
    int y = 0;

    while (y < env->line)
    {
        while (x < env->mod)
        {
            ft_putnbr(env->tab[y][x]);
            ft_putchar(' ');
            x++;
        }
        ft_putendl("");
        x = 0;
        y++;
    }
}
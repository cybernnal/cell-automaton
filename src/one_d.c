//
// Created by tom billard on 18/12/2016.
//

#include <life.h>

void    pars_oned(char *rule, char *start, t_env *env)
{
    int i = 0;
    int j = 7;
    while (j >= 0)
    {
        env->drule[j][0] = rule[i] - 48;
        j--;
        i++;
    }
    env->is_one = 1;
    i = 0;
    env->tab = (int**)ft_memalloc((sizeof(int*) * 11));
    while (i < 11)
    {
        env->tab[i] = (int*)ft_memalloc((sizeof(int) * 11));
        i++;
    }
    i = 1;
    while (i < 10)
    {
        env->tab[0][i] = start[i - 1] - 48;
        i++;
    }
    env->line = 11;
    env->mod = 11;
}
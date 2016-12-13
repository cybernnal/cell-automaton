//
// Created by tom billard on 13/12/2016.
//


#include "life.h"

static void     get_usage(void)
{
    printf("Usage:\n\tlife_of_game map [-s sleep in ms] [-n neighbours numbers] [-m iteration min] [-e iteration max]\n\tMap must be a square, the first line contain only rules: format: birth/stay\n");
    printf("\t-n n: number of neighbours cell to check (1 default)\n\t-m n: first iteration to print\n\t-e n: last iteration to print\n\tof course m must be < than e\n");
    exit (1);
}

static void     get_neib(char *str, t_env *env)
{
    int i = 0;

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return;
        i++;
    }
    env->n_m = ft_atoi(str);
}

static void     get_sleep(char *str, t_env *env)
{
    int i = 0;

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return;
        i++;
    }
    env->sleep = ft_atoi(str) * 1000;
}

static void     get_min(char *str, t_env *env)
{
    int i = 0;

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return;
        i++;
    }
    env->i_min = ft_atoi(str);
}


static void     get_stop(char *str, t_env *env)
{
    int i = 0;

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return;
        i++;
    }
    env->i_stop = ft_atoi(str);
}

void     get_arg(t_env *env, char **argv)
{
    int i = 2;

    while (argv[i])
    {
        if (!ft_strcmp("-s", argv[i]))
            get_sleep(argv[++i], env);
        else if (!ft_strcmp("-h", argv[i]))
            get_usage();
        else if (!ft_strcmp("-n", argv[i]))
            get_neib(argv[++i], env);
        else if (!ft_strcmp("-m", argv[i]))
            get_min(argv[++i], env);
        else if (!ft_strcmp("-e", argv[i]))
            get_stop(argv[++i], env);
        i++;
    }
}
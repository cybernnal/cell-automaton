//
// Created by tom billard on 13/12/2016.
//


#include <fcntl.h>
#include "life.h"

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

static int map_size(int fd)
{
    int size;
    char *line;

    size = 0;
    while (get_next_line(fd, &line))
    {
        if (!line)
            break ;
        if (size < line[0] - 48)
            size = line[0] - 48;
        free(line);
    }
    if (size == 0 || !line)
        ft_error("read error");

    free(line);
    return (size);
}

static void     get_tab(char *str, t_env *env)
{
    int fd;
    char *line;
    int i;

    i = 0;
    if ((fd = open(str, O_RDONLY)) < 0)
        ft_error("open error");
    env->state_max = map_size(fd) + 1;
    if ((close(fd)) != 0)
        ft_error("close fd error");
    if ((fd = open(str, O_RDONLY)) < 0)
        ft_error("open error");
    env->lst = (t_tab**)ft_memalloc((sizeof(t_tab*) *  env->state_max));
    env->f = (t_tab**)ft_memalloc((sizeof(t_tab*) *  env->state_max));
    env->i_max = (int*)ft_memalloc((sizeof(int) *  env->state_max));
    while (get_next_line(fd, &line))
    {
        if (!line || !line[0])
            ft_error("read error");
        if (!(env->lst[line[0] - 48]))
        {
            env->i_max[line[0] - 48] = 1;
            env->lst[line[0] - 48] = (t_tab *) ft_memalloc((sizeof(t_tab)));
            env->lst[line[0] - 48]->next = NULL;
            env->f[line[0] - 48] = env->lst[line[0] - 48];
        }
        else
        {
            env->lst[line[0] - 48]->next = (t_tab *) ft_memalloc((sizeof(t_tab)));
            env->lst[line[0] - 48] = env->lst[line[0] - 48]->next;
            env->lst[line[0] - 48]->next = NULL;
            env->i_max[line[0] - 48]++;
        }
        env->lst[line[0] - 48]->tab[0] = line[1] - 48;
        env->lst[line[0] - 48]->tab[1] = line[2] - 48;
        env->lst[line[0] - 48]->tab[2] = line[3] - 48;
        env->lst[line[0] - 48]->tab[3] = line[4] - 48;
        env->lst[line[0] - 48]->intput = line[0] - 48;
        env->lst[line[0] - 48]->output = line[5] - 48;
        free(line);
        i++;
    }
    i = 0;
    if ((close(fd)) != 0)
        ft_error("close fd error");
    int tmp[8];
    while (i < env->state_max)
    {
        tmp[i] = 0;
        env->lst[i] = env->f[i];
        i++;
    }
    env->is_t = 1;
}

void     get_arg(t_env *env, char **argv, int i)
{
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
        else if (!ft_strcmp("-t", argv[i]))
            get_tab(argv[++i], env);
        else if (!ft_strcmp("-p", argv[i]))
            env->print = 1;
        else if (!ft_strcmp("-w", argv[i]))
            env->wire = 1;
        else if (!ft_strcmp("-q", argv[i]))
            env->quit = 1;
        else if (!ft_strcmp("-z", argv[i]))
            env->is_dz = 1;
        else if (!ft_strcmp("-x", argv[i]))
            env->map_size = ft_atoi(argv[++i]);
        else if (!ft_strcmp("-ww", argv[i]))
            env->ww = 1;
        i++;
    }
}
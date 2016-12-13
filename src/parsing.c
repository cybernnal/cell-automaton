//
// Created by tom billard on 15/11/2016.
//

#include <life.h>
#include <fcntl.h>

static void map_size(t_env *env, int fd)
{
    int size;
    char *line;

    size = 0;
    while (get_next_line(fd, &line))
    {
        if (!line)
            break ;
        size++;
        free(line);
    }
    if (size == 0 || !line)
        ft_error("read error");
    free(line);
    env->line = size - 1;
}

static void get_rules(int fd, t_env *env)
{
    char *line;

    get_next_line(fd, &line);
    env->b = ft_strrevchr(line, '/');
    env->s = ft_strdup(ft_strchr(line, '/') + 1);
    free (line);
}

void        pars_map(t_env *env, char *arg)
{
    int fd;
    int i;

    i = 0;
    if ((fd = open(arg, O_RDONLY)) < 0)
        ft_error("open error");
    map_size(env, fd);
    if ((close(fd)) != 0)
        ft_error("close fd error");
    env->map = (char**)ft_memalloc((sizeof(char*) * env->line + 1));
    if ((fd = open(arg, O_RDONLY)) < 0)
        ft_error("open error");
    get_rules(fd, env);
    while (get_next_line(fd, &env->map[i]))
    {
        if (!env->map[i])
            ft_error("read error");
        i++;
    }
    env->map[i] = NULL;
    if ((close(fd)) != 0)
        ft_error("close fd error");
    c_to_d(env);
}
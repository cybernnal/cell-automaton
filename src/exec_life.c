//
// Created by tom billard on 13/12/2016.
//

#include "life.h"

static int     get_stat(t_env *env, int x, int y)
{
    if (y < env->line && y >= 0 && x >= 0 && x < env->mod)
        return (env->tab[y][x]);
    return (0);

}

static bool     is_true(int hit, char*str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == (char)(hit + 48))
            return (true);
        i++;
    }
    return (false);
}

static int      get_med(int med[10])
{
    int ret = 0;
    int j = 0;
    int i = 1;

    ret = med[i];
    j = i;
    while (i < 10)
    {
        if (med[i] > ret)
        {
            j = i;
            ret = med[i];
        }
        i++;
    }
    return (j);
}

static int  is_n_hit(t_env *env, int x, int y, int n)
{
    int x1 = -env->n_m;
    int y1 = -env->n_m;
    int hit = 0;

    while (y1 <= env->n_m)
    {
        while (x1 <= env->n_m)
        {
            if (x1 == 0 && y1 == 0)
            {
                x1++;
                continue ;
            }
            if (env->tab[y + y1][x + x1] == n)
                hit++;
            x1++;
        }
        x1 = -env->n_m;
        y1++;
    }
    return (hit);
}

static int      is_ok(t_env *env, int i, int x, int y)
{
    if (get_stat(env, x, y - 1) == env->lst[i]->tab[0] && get_stat(env, x + 1 , y) == env->lst[i]->tab[1] && get_stat(env, x, y + 1) == env->lst[i]->tab[2] && get_stat(env, x - 1, y) == env->lst[i]->tab[3])
        return (1);
    if (get_stat(env, x, y - 1) == env->lst[i]->tab[1] && get_stat(env, x + 1 , y) == env->lst[i]->tab[2] && get_stat(env, x, y + 1) == env->lst[i]->tab[3] && get_stat(env, x - 1, y) == env->lst[i]->tab[0])
        return (1);
    if (get_stat(env, x, y - 1) == env->lst[i]->tab[2] && get_stat(env, x + 1 , y) == env->lst[i]->tab[3] && get_stat(env, x, y + 1) == env->lst[i]->tab[0] && get_stat(env, x - 1, y) == env->lst[i]->tab[1])
        return (1);
    if (get_stat(env, x, y - 1) == env->lst[i]->tab[3] && get_stat(env, x + 1 , y) == env->lst[i]->tab[0] && get_stat(env, x, y + 1) == env->lst[i]->tab[1] && get_stat(env, x - 1, y) == env->lst[i]->tab[2])
        return (1);
    return (0);
}

static int      tab_life(t_env *env, int x, int y)
{
    int i = 0;

    while (i < env->state_max)
    {
        env->lst[i] = env->f[i];
        i++;
    }
    i = 0;
    while (i < env->i_max[env->tab[y][x]])
    {
        if (is_ok(env, env->tab[y][x], x, y))
            return (env->lst[env->tab[y][x]]->output);
        env->lst[env->tab[y][x]] = env->lst[env->tab[y][x]]->next;
        i++;
    }
    return (0);
}

  static int     is_life(t_env *env, int x, int y)
  {
      int         hit = 0;
      int         x1;
      int         y1;
      int         med[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      int         ret;
      int         tmp;

      x1 = -env->n_m;
      y1 = -env->n_m;
      if (env->is_t)
          return (tab_life(env, x, y));
      while (y1 <= env->n_m)
      {
          while (x1 <= env->n_m)
          {
              if (x1 == 0 && y1 == 0)
              {
                  x1++;
                  continue ;
              }
              tmp = get_stat(env, x + x1, y + y1);
              med[tmp]++;
              if (tmp > 0)
                  hit++;
              x1++;
          }
          x1 = -env->n_m;
          y1++;
      }
      if (env->wire == 1)
      {
          if (env->tab[y][x] == 0)
              return (0);
          if (env->tab[y][x] == 1 && (is_n_hit(env, x, y, 2) == 1 || is_n_hit(env, x, y, 2) == 2))
              return (2);
          else if (env->tab[y][x] == 1)
              return (1);
          if (env->tab[y][x] == 2)
              return (3);
          if (env->tab[y][x] == 3)
              return (1);
      }
      else if ((is_true(hit, env->s) == true && env->tab[y][x] > 0) || (is_true(hit, env->b) == true && env->tab[y][x] == 0))
      {
          ret = get_med(med);
          if (ret == 0)
              ret++;
          return (ret);
      }
      return (0);
}

static void     cp_tab(int tmp[WIN][WIN], t_env *env)
{
    int x = 0;
    int y = 0;

    while (y < env->line)
    {
        while (x < env->mod)
        {
            env->tab[y][x] = tmp[y][x];
            x++;
        }
        x = 0;
        y++;
    }
}

static void     creat_life(t_env *env)
{
    int x = 0;
    int y = 0;
    int tmp[WIN][WIN];

    while (y < env->line)
    {
        while (x < env->mod)
        {
            tmp[y][x] = is_life(env, x, y);
            x++;
        }
        x = 0;
        y++;
    }
    cp_tab(tmp, env);
}

void        exec_life(t_env *env)
{
    int i = 0;

    if (env->i_min > env->i_stop)
    {
        ft_putendl("arguments error");
        env->i_min = 0;
        env->i_stop = 0;
    }
    while (env->tab)
    {
        if (env->i_min == 0 || i >= env->i_min)
        {
            render(env);
            ft_putstr("iteration: ");
            ft_putnbr(i);
            ft_putendl("");
            if (env->print)
            {
                print_map(env);
                ft_putendl("");
            }
            usleep((useconds_t)env->sleep);
        }
        if (env->i_stop == 0 || i <= env->i_stop)
        {
            creat_life(env);
            i++;
        }
    }
}
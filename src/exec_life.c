//
// Created by tom billard on 13/12/2016.
//

#include <pthread.h>
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
            if (y + y1 >= 0 && y + y1 < env->mod && x + x1 >= 0 && x + x1 <= env->mod && env->tab[y + y1][x + x1] == n)
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

static int      tab_life(t_env env, int x, int y)
{
    int i = 0;

    while (i < env.state_max)
    {
        env.lst[i] = env.f[i];
        i++;
    }
    i = 0;
    while (i < env.i_max[env.tab[y][x]])
    {
        if (is_ok(&env, env.tab[y][x], x, y))
            return (env.lst[env.tab[y][x]]->output);
        env.lst[env.tab[y][x]] = env.lst[env.tab[y][x]]->next;
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
          return (tab_life(*env, x, y));
      if (env->wire == 1 || env->ww == 1)
      {
          if (env->ww == 1 && env->tab[y][x] == 0 && (is_n_hit(env, x, y, 2) == 1) && (is_n_hit(env, x, y, 0) == 7))
              return (1);
          if (env->tab[y][x] == 0)
              return (0);
          else if (env->tab[y][x] == 1 && (is_n_hit(env, x, y, 2) == 1 || is_n_hit(env, x, y, 2) == 2))
              return (2);
          else if (env->tab[y][x] == 1)
              return (1);
          else if (env->tab[y][x] == 2)
              return (3);
          else if (env->tab[y][x] == 3)
              return (1);
          return (0);
      }
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
      if ((env->tab[y][x] > 0 && !ft_strchr(env->s, 'x') && is_true(hit, env->s) == true) || ( env->tab[y][x] == 0 && !ft_strchr(env->b, 'x') && is_true(hit, env->b) == true))
      {
          ret = get_med(med);
          if (ret == 0)
              ret++;
          return (ret);
      }
      return (0);
}
#define FUCK 1500

static void     cp_tab(t_env *env, char tmp[env->mod][env->mod], int y_max)
{
    int x = 0;
    int y = 0;

    while (y < env->line && (y_max == 0 || y < y_max))
    {
        while (x < env->mod)
        {
            env->tab[y][x] = (int)tmp[y][x];
            x++;
        }
        x = 0;
        y++;
    }
}

static void     do_dz(t_env *env)
{
    int x = 0;
    int y = 0;
    int **tmp;

    if (env->mod_1 == 0)
        env->mod_1 = env->mod;
    int size = env->mod + (env->mod_1 / 2);// + (env->mod / 10);

    tmp = (int**)ft_memalloc(sizeof(int*) * size);
    while (y < size)
    {
        tmp[y] = (int*)ft_memalloc(sizeof(int) * size);
        while (x < size)
        {
            if (x - (env->mod_1 / 4) >= 0 && x < env->mod + (env->mod_1 / 4) - 1 && y - (env->mod_1 / 4) >= 0 && y < env->mod + (env->mod_1 / 4) - 1)
                tmp[y][x] = env->tab[y - (env->mod_1 / 4)][x - (env->mod_1 / 4)];
            else
                tmp[y][x] = 0;
            x++;
        }
        x = 0;
        y++;
    }
    y = 0;
    while (y < env->mod)
    {
        free(env->tab[y]);
        y++;
    }
    free(env->tab);
    env->tab = tmp;
    env->mod = size;
    env->line = size;
    env->is_bzero = 1;
}

static void     do_dzod(t_env *env)
{
    int x = 0;
    int y = 0;
    int **tmp;

    if (env->mod_1 == 0)
        env->mod_1 = env->mod;
    int size = env->mod + (env->mod_1 / 2);// + (env->mod / 10);

    tmp = (int**)ft_memalloc(sizeof(int*) * size);
    while (y < size)
    {
        tmp[y] = (int*)ft_memalloc(sizeof(int) * size);
        while (x < size)
        {
            if (x - (env->mod_1 / 4) >= 0 && x < env->mod + (env->mod_1 / 4) - 1 && y < env->mod + (env->mod_1 / 8) - 1)
                tmp[y][x] = env->tab[y][x - (env->mod_1 / 4)];
            else
                tmp[y][x] = 0;
            x++;
        }
        x = 0;
        y++;
    }
    y = 0;
    while (y < env->mod)
    {
        free(env->tab[y]);
        y++;
    }
    free(env->tab);
    env->tab = tmp;
    env->mod = size;
    env->line = size;
    env->is_bzero = 1;
}

static int      one_d(t_env *env, int x, int y)
{
    int result = 0;
    int offset = 0;

    if (x <= 1 || x >= env->mod - 2)
        return (0);
    result = (env->tab[y - 1][x + 1] == 1 ? 1 : 0);
    result = result | (env->tab[y - 1][x] == 1 ? 1 : 0) << 1;
    result = result | (env->tab[y - 1][x - 1] == 1 ? 1 : 0) << 2;
 //   if (result > 0)
        result = result;
    return (env->drule[result][0]);
}

static void     creat_life(t_env *env)
{
    int x = 0;
    int y = 0;
   // static int lx = 0;
    //int         tlx = 0;
    int         tly = 0;
    char        tp;


    char tmp[env->mod][env->mod];

    if (env->is_one == 1)
    {
        static int yo = 1;

        x = 0;
        while (y < env->mod)
        {
            if (y < yo)
                while (x < env->mod)
                {
                    tmp[y][x] = (char)env->tab[y][x];
                    x++;
                }
            else
                ft_bzero(tmp[y], sizeof(char) * env->mod);
            x = 0;
            y++;
        }
        x = 1;
        y = yo;
        while (x < env->mod - 1)
        {
            if ((tmp[y][x] = (char)one_d(env, x, y)) == 1 && (x <= 2 || x == env->mod - 3 || y == env->line - 3))
                env->dz = 1;
                x++;
        }
        yo++;
        cp_tab(env, tmp, env->ly);
        if (env->dz != 0 && env->is_dz == 1)
         do_dzod(env);
        env->dz = 0;
        return;
    }
    else
        while (y < env->line && (env->ly == 0 || y < env->ly))
        {
            while (x < env->mod)
            {
                /* if ((tp = (char)is_life(env, x, y)) > 0)
                 {
                     if ((tlx = x) && (tly = y) && (x <= 2 || y <= 2 || x == env->mod - 3 || y == env->line - 3))
                         env->dz = 1;
                     if (tlx)
                 }*/
                //
                if ((tmp[y][x] = (char) is_life(env, x, y)) > 0 && (tly = y) && (x <= 2 || y <= 2 || x == env->mod - 3 || y == env->line - 3))
                    env->dz = 1;
                x++;
            }
            x = 0;
            y++;
        }
    cp_tab(env, tmp, env->ly);
    if (env->dz != 0 && env->is_dz == 1)
    {
        env->ly = 0;
        do_dz(env);
    }
   else
        env->ly = tly + 2;
    env->dz = 0;
}

void        exec_life(t_env *env)
{
    int i = 0;

    if (env->i_min > env->i_stop && env->i_stop > 0)
    {
        ft_putendl("arguments error");
        env->i_min = 0;
        env->i_stop = -42;
    }
    while (env->tab)
    {
        if (env->i_min == 0 || env->i >= env->i_min)
        {
            render(env);
            ft_putstr("iteration: ");
            ft_putnbr(env->i);
            write(1, "\n", 1);
            if (env->print)
            {
                print_map(env);
                ft_putendl("");
            }
            usleep((useconds_t)env->sleep);
        }
        if (env->i >= env->i_stop && env->quit == 1)
            return ;
        if (env->i_stop == -42 || env->i < env->i_stop)
        {
            creat_life(env);
            env->i++;
        }
    }
}
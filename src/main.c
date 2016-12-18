/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:46:15 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:28:40 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"
#include <stdio.h>

static  t_env        *sig(void)
{
    static t_env env;

    return (&env);
}

static void                at_exit(void)
{
    t_env   *env;
    int i = 0;
    int j = 0;
    int k = 0;

    env = sig();
    while (j < env->mod)
    {
        while (i < env->mod)
        {
            if (env->tab[j][i] == 1)
                k++;
            i++;
        }
        i = 0;
        j++;
    }
    printf("number of live cell: %d, map length: %d, total: %d, iteration: %d\n", k, env->mod, env->mod * env->mod, env->i);
}

static void     init_env(t_env *env)
{
    env->n_m = 1;
    env->i_stop = -42;
    env->sleep = 5000;
}

int		main(int argc, char  **argv)
{
	t_env	*env;
    int  i = 2;

	if (argc < 1)
		ft_error("too few args");
    atexit(at_exit);
    env = sig();
    ft_bzero(env, sizeof(t_env));
    if (ft_strcmp(argv[1], "-1d"))
        pars_map(env, argv[1]);
    else
    {
        pars_oned(argv[2], argv[3], env);
        i += 2;
    }
    init_env(env);
    get_arg(env, argv, i);
    exec_life(env);
	return (0);
}

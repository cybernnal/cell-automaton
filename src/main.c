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

void     get_usage(void)
{
    printf("Usage:\n\tlife map_path [-z (!!!useful!!!)] [-s sleep in ms] [-n neighbours numbers] [-m iteration min] [-e iteration max]\n\tMap must be a square, the first line contain only rules: format: birth/stay\n");
    printf("\t* -n n: number of neighbours cell to check (1 default)\n\t* -m n: first iteration to print\n\t* -e n: last iteration to print\n\t\tof course m must be < than e\n");
    printf("\t* -s s: m sleep in ms between generation (use '+' and '-' to modify on run-time).\n\t");
    printf("* -t t: path of table of rule for von Neumann's neighborhood (like langton's loops)\n\t* -p p: print map on each iteration in ascii\n\t");
    printf("* -w w: for wireworld's maps (can't be used with -t)\n\t* -ww ww: for personal rules of wireworld (one additional rule).\n\t* -q q: quit at the end (work only with -e)\n\t");
    printf("* -x x: map size (deprecated)\n\t* -z z: !!Useful!! adapt zoom");
    printf("\n\t* -1d 1d: one dimension Usage: life -1d rules starting_position\n\t\trules on 8 bits, please see http://mathworld.wolfram.com/ElementaryCellularAutomaton.html\n\t\tstarting_position with 0 or 1 (something like: 00010101000 or 00000100000)\n");
    exit (1);
}

int		main(int argc, char  **argv)
{
	t_env	*env;
    int  i = 1;

	if (argc <= 1)
		get_usage();
    atexit(at_exit);
    env = sig();
    ft_bzero(env, sizeof(t_env));
    get_arg(env, argv, i);
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

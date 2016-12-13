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

static void     init_env(t_env *env)
{
    env->n_m = 1;
}

int		main(int argc, char  **argv)
{
	t_env	env;

	if (argc < 1)
		ft_error("too few args");
    ft_bzero(&env, sizeof(t_env));
    pars_map(&env, argv[1]);
    init_env(&env);
    get_arg(&env, argv);
    exec_life(&env);
	return (0);
}

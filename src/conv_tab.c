/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 19:48:27 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:15:21 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <life.h>

static int nb_nb(char *str)
{
    int i;
    int nb;

    nb = 0;
    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] != '\n' && str[i] != ' ')
        {
            i++;
        }
        if (i != 0)
            nb++;
        while (str[i] && (str[i] == '\n' || str[i] == ' '))
        {
            i++;
        }
    }
    return (nb);
}

int			c_to_d(t_env *env)
{
	int		i;
	int		j;
    int     m;

    i = 0;
    j = 0;
    m = 0;
	env->mod = nb_nb(env->map[0]);
	env->tab = (int**)ft_memalloc(sizeof(int*) * (env->line));
	while (env->map[i])
	{
        env->tab[i] = (int*)ft_memalloc(sizeof(int) * (env->mod));
        while (env->map[i][j])
        {
            if (!ft_isdigit(env->map[i][j]))
            {
                j++;
                continue ;
            }
            env->tab[i][m] = env->map[i][j] - 48;
            j++;
            m++;
        }
        i++;
        m = 0;
        j = 0;
    }
    return (1);
}

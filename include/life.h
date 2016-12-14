/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:40:53 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:13:54 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "../libft/libft.h"
#include <errno.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#define WIN_X   1700
#define WIN_Y   1075
#define WIN         200

# define L_C(X, x1, x2, y1, y2) ((int)(((X - x1) * (y2 - y1)) / (x2 - x1)) + y1)
# define L_CF(X, x1, x2, y1, y2) ((float)(((float)((X - x1) * (y2 - y1))) / (float)(x2 - x1)) + y1)
#define WHITE   (Uint32) ((255 << 16) + (255 << 8) + 255)
#define RED     (Uint32) ((255 << 16) + (0 << 8) + 0)
#define GREEN   (Uint32) ((0 << 16) + (255 << 8) + 0)
#define BLEU    (Uint32) ((0 << 16) + (0 << 8) + 255)
#define PURPUL  (Uint32) ((108 << 16) + (2 << 8) + 119)
#define ORANGE  (Uint32) ((250 << 16) + (164 << 8) + 1)
typedef struct                  s_window
{
    SDL_Window              *window;
    SDL_Event               event;
    SDL_Renderer            *renderer;
    SDL_Texture             *image;
    Uint32                  *img_ptr;
    int                     is_init;
}                           t_window;

typedef struct      s_tab
{
    int            tab[4];
    int            intput;
    int            output;
    struct s_tab   *next;
}                   t_tab;

typedef struct		s_env
{
	char			**map;
    char            *s;
    char            *b;
	int				line;
	int				mod;
	int 			mod_1;
	int 			sleep;
	int 			n_m;
    int             i_min;
    int             i_stop;
    int             print;
	int 			wire;
	int 			quit;
    int             is_t;
    int             state_max;
    int             *i_max;
    int 		    **tab;
	int 			dz;
	int 			is_dz;
	int 			is_bzero;
    t_tab            **lst;
    t_tab            **f;
}					t_env;

void    			get_arg(t_env *env, char **argv);
void   				print_map(t_env *env);
void        		exec_life(t_env *env);
void                init_window(t_window *window);
int                 render(t_env *env);
void                pars_map(t_env *env, char *arg);
int					ft_error(char *str);
int					c_to_d(t_env *env);
#endif

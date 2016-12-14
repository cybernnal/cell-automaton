#include <time.h>
#include "life.h"

static void key_handler(SDL_Event event, t_env *env)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			exit(EXIT_SUCCESS);
    }
}

static void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
    if (y > WIN_Y || x > WIN_X || x < 0 || y < 0)
    {
       ft_putendl("pixel over/under flow");
//        return ;
    }
        w->img_ptr[WIN_X * y + x] = color;
   // SDL_UpdateTexture(w->image, NULL, w->img_ptr, WIN_X * sizeof(Uint32));
   // SDL_RenderCopy(w->renderer, w->image, NULL, NULL);
   // SDL_RenderPresent(w->renderer);
}

static void		draw_pix(t_window *w, int off, int x, int y, Uint32 color)
{
	int x1 = -(off / 2);
	int y1 = -(off / 2);

	while (y1 < off)
	{
		while (x1 < off)
		{
			draw_pixel(x + x1, y + y1, color, w);
			x1++;
		}
		x1 = -(off/2);
		y1++;
	}
}

static void		render_map(t_window *w, t_env *env)
{
	int 	off = (int)L_CF(1, 0, env->line, 0, WIN_Y);
	int 	x = off / 2;
	int 	y = off / 2;
//	int 	x = (int)L_CF(0.5, 0, WIN_Y, 0, env->mod);
//	int 	y = (int)L_CF(0.5, 0, WIN_Y, 0, env->line);
	int 	x1 = 0;
	int		y1 = 0;

	while (y1 < env->line)
	{
		while (x1 < env->mod)
		{
            if (env->tab[y1][x1] == 0)
                draw_pix(w, off, x, y, 0);
			else if (env->tab[y1][x1] == 1)
				draw_pix(w, off, x, y, PURPUL);
            else if (env->tab[y1][x1] == 2)
                draw_pix(w, off, x, y, RED);
            else if (env->tab[y1][x1] == 3)
                draw_pix(w, off, x, y, BLEU);
            else if (env->tab[y1][x1] == 4)
                draw_pix(w, off, x, y, GREEN);
            else if (env->tab[y1][x1] == 5)
                draw_pix(w, off, x, y, ORANGE);
            else if (env->tab[y1][x1] > 5)
                draw_pix(w, off, x, y, RED);
			else
				draw_pix(w, off, x, y, 0);
			x +=off;
			x1++;
		}
		y += off;
		x = off /2;
		x1 = 0;
		y1++;
	}
}

int        render(t_env * env)
{
	static t_window w;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
    if (env->is_bzero == 1)
    {
        env->is_bzero = 0;
        bzero(w.img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
    }
 	while (SDL_PollEvent(&w.event))
		key_handler(w.event, env);
	render_map(&w, env);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_X * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
    return (1);
}

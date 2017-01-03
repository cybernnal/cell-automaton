#include <time.h>
#include "life.h"


static void key_handler(SDL_Event event, t_env *env, t_window *w)
{
	if (event.type == SDL_KEYDOWN)
	{
      	if (event.key.keysym.sym == SDLK_ESCAPE)
			exit(EXIT_SUCCESS);
        if (event.key.keysym.sym == SDLK_0)
            edit_menu(env, w);
        if (event.key.keysym.sym == '=')
            env->sleep += 10000 + env->sleep/4;
        if (event.key.keysym.sym == '-')
        {
            if (env->sleep >= 10000 + env->sleep/4)
                env->sleep -= 10000 + env->sleep/4;
            else
                env->sleep = 0;
        }
//		if (event.key.keysym.sym == SDLK_z)
//			env->zoom += 10;
	}
}

typedef float offf_t;

static void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
    if (y > WIN_Y || x > WIN_X || x < 0 || y < 0)
    {
        ft_putstr("x: ");
        ft_putnbr(x);
        ft_putstr(", y:");
        ft_putnbr(y);
        ft_putendl(" pixel over/under flow!!!!!");
        return ;
    }
        w->img_ptr[WIN_X * y + x] = color;
   // SDL_UpdateTexture(w->image, NULL, w->img_ptr, WIN_X * sizeof(Uint32));
   // SDL_RenderCopy(w->renderer, w->image, NULL, NULL);
   // SDL_RenderPresent(w->renderer);
}

static void		draw_pix(t_window *w, offf_t off, offf_t x, offf_t y, Uint32 color)
{
    offf_t x1 = -(off / 2);
    offf_t y1 = -(off / 2);

	while (y1 < off  / 2 + 1)
	{
		while (x1 < off / 2 + 1)
		{
			draw_pixel((int)(x + x1), (int)(y + y1), color, w);
			x1++;
		}
		x1 = -(off/2);
		y1++;
	}
}


static void		render_map(t_window *w, t_env *env)
{
	float 	tmp = L_CF(1, 0, env->mod, 0, WIN_Y - 10);
    offf_t     off;
    offf_t 	x;
    offf_t 	y;
    offf_t 	x1 = 0;
    offf_t		y1 = 0;
    offf_t     fact = 0;
    offf_t      x0;
  //    while (tmp < 1)
//    {
//        fact++;
//        tmp *= 2;
//    }
/*	if (fact)
		tmp = L_CF(1, 0, env->mod / pow(2, fact), 0, WIN_Y - 10);
	fact = 0;
	while (tmp < 1)
	{
		fact++;
		tmp *= 2;
	}*/
    off = (offf_t)tmp;
    x0 = (off / 2) + ((WIN_X - (off * env->mod)) / 2);
    y = (off / 2) + ((WIN_Y - (off * env->mod)) / 2);
    x = x0;//off / 2;
    //y = off / 2;
//    static int c = 0;
//
//    if (c >= 3)
//        c = 0;
//    static Uint32 color2[3] = {(Uint32) ((255 << 16) + (0 << 8) + 0), (Uint32) ((250 << 16) + (164 << 8) + 1), (Uint32) ((0 << 16) + (0 << 8) + 255)};
    while (y1 < env->line)
	{
		while (x1 < env->mod)
		{
//			if (x1 == env->mod - 1 || y1 == env->mod - 1)
//				draw_pixel(x + (off * 2) - 10, y + (off * 2) - 10, WHITE, w);
            if (env->tab[(int)y1][(int)x1] == 0)
                draw_pix(w, off, x, y, STATE_0);
			else if (env->tab[(int)y1][(int)x1] == 1)
				draw_pix(w, off, x, y, STATE_1);
            else if (env->tab[(int)y1][(int)x1] == 2)
                draw_pix(w, off, x, y, STATE_2);
            else if (env->tab[(int)y1][(int)x1] == 3)
                draw_pix(w, off, x, y, STATE_3);
            else if (env->tab[(int)y1][(int)x1] == 4)
                draw_pix(w, off, x, y, STATE_4);
            else if (env->tab[(int)y1][(int)x1] == 5)
                draw_pix(w, off, x, y, STATE_5);
            else if (env->tab[(int)y1][(int)x1] == 6)
                draw_pix(w, off, x, y, STATE_6);
            else if (env->tab[(int)y1][(int)x1] == 7)
                draw_pix(w, off, x, y, STATE_7);
            else if (env->tab[(int)y1][(int)x1] == 8)
                draw_pix(w, off, x, y, STATE_8);
            else if (env->tab[(int)y1][(int)x1] >= 9)
                draw_pix(w, off, x, y, STATE_9);
            else
				draw_pix(w, off, x, y, 0);
			x +=off;
			x1++;
			if (fact != 0)
				x1 += pow(2, fact);
		}
		y += off;
		x = x0;//off /2;
		x1 = 0;
		y1++;
        if (fact != 0)
            y1 += pow(2, fact);
	}
   // c++;
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
		key_handler(w.event, env, &w);
	render_map(&w, env);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_X * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
    return (1);
}

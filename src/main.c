/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:43:10 by avishnev          #+#    #+#             */
/*   Updated: 2018/04/14 15:39:31 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		lsync(void)
{
	int					delay;
	static unsigned int	time;
	static char			vsync = 1;

	vsync == 1 ? SDL_GL_SetSwapInterval(1) : 0;
	if (vsync)
	{
		delay = 16 - (SDL_GetTicks() - time);
		if (delay < 0)
			SDL_Delay(0);
		else
			SDL_Delay(delay);
		time = SDL_GetTicks();
	}
}

static void	color_fps(t_src *m, unsigned int fps, TTF_Font *ttf, char *fps_str)
{
	int r;
	int g;
	int b;

	if (fps >= 40)
	{
		r = 0;
		g = 255;
		b = 0;
	}
	else if (fps >= 20 && fps < 40)
	{
		r = 255;
		g = 156;
		b = 127;
	}
	else if (fps < 20)
	{
		r = 255;
		g = 0;
		b = 0;
	}
	m->fps = TTF_RenderText_Solid(m->ttf, fps_str,
					(SDL_Color){r, g, b, 255});
}

void		display_fps(t_src *m)
{
	static unsigned	int	fps;
	static unsigned	int	time_current;
	static unsigned	int	time_past;
	static unsigned	int	ticks;
	static char			*fps_str;

	time_current = time(NULL);
	if (time_current - time_past && (time_past = time_current))
	{
		fps = 1000 / (SDL_GetTicks() - ticks);
		ft_memdel((void**)&fps_str);
		fps_str = ft_itoa(fps);
	}
	ticks = SDL_GetTicks();
	if (!(m->ttf = TTF_OpenFont("src/fonts/arcadeclassic.regular.ttf", 50)))
		ft_putstr(IMG_GetError());
	color_fps(m, fps, m->ttf, fps_str);
	SDL_BlitSurface(m->fps, NULL, m->surf,
		&(SDL_Rect){ 10, 0, m->fps->w, m->fps->h});
	TTF_CloseFont(m->ttf);
	SDL_FreeSurface(m->fps);
}

void		exit_work(t_src *src)
{
	SDL_FreeCursor(src->curs);
	SDL_DestroyWindow(src->wind);
	IMG_Quit();
	SDL_Quit();
	free(src->params.light);
	free(src->objects);
	free(src->params.object);
	free(src->buffer);
}

int			main(int ac, char **av)
{
	t_src	src;

	if (ac != 2)
		error_manadge(MSG, 0, NULL);
	read_from_file(av[1], &src);
	init_host(&src);
	init_parametrs(&src);
	create_videohost(&src);
	while (DICK)
	{
		if (!expose_hook(&src))
			break ;
		opencl_kernel_run(&src);
		display_fps(&src);
		lsync();
		SDL_UpdateWindowSurface(src.wind);
	}
	exit_work(&src);
	return (0);
}

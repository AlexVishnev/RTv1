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

void		time_delay(void)
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

static void	fps_color(t_src *src, unsigned int fps, TTF_Font *ttf, char *fps_str)
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
	src->fps = TTF_RenderText_Solid(src->ttf, fps_str,
					(SDL_Color){r, g, b, 255});
}

void		init_fps(t_src *src)
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
	if (!(src->ttf = TTF_OpenFont("/Library/Fonts/Arial.ttf", 50)))
		ft_putstr(IMG_GetError());
	fps_color(src, fps, src->ttf, fps_str);
	SDL_BlitSurface(src->fps, NULL, src->surf,
		&(SDL_Rect){ 10, 0, src->fps->w, src->fps->h});
	TTF_CloseFont(src->ttf);
	SDL_FreeSurface(src->fps);
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
		init_fps(&src);
		time_delay();
		SDL_UpdateWindowSurface(src.wind);
	}
	exit_work(&src);
	return (0);
}

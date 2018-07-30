/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:43:10 by avishnev          #+#    #+#             */
/*   Updated: 2018/07/15 16:20:04 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		time_delay(void)
{
	int					delay;
	static unsigned int	time;

	SDL_GL_SetSwapInterval(1);
	delay = 16 - (SDL_GetTicks() - time);
	if (delay < 0)
		delay = 0;
	SDL_Delay(delay);
	time = SDL_GetTicks();
}

static void	fps_color(t_src *src, unsigned int fps, TTF_Font *ttf,
	char *fps_str)
{
	(void)ttf;
	if (fps >= 40)
		src->fps = TTF_RenderText_Solid(src->ttf, fps_str,
			(SDL_Color){0, 255, 0, 255});
	else if (fps >= 20 && fps < 40)
		src->fps = TTF_RenderText_Solid(src->ttf, fps_str,
			(SDL_Color){255, 156, 127, 255});
	else
		src->fps = TTF_RenderText_Solid(src->ttf, fps_str,
			(SDL_Color){255, 0, 0, 255});
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
	system("leaks -q RT");
}

int			main(int ac, char **av)
{
	t_src	src;

	if (ac != 2)
		error_manadge(MSG, 0, NULL);
		// TODO: UNFUCK YOURSELF, uncomment this line and all will work fine
	// read_from_file(av[1], &src);
	// And uncomment this line
	parser_main(av[1], &src);
	printf("\n\n\n\nsrc.params.o.x = [%f]\nsrc.params.o.y = [%f]\nsrc.params.o.z = [%f]\n", src.params.o.x,src.params.o.y , src.params.o.z );
	printf("\n\n\n\nsrc.params.d.x = [%f]\nsrc.params.d.y = [%f]\nsrc.params.d.z = [%f]\n", src.params.d.x,src.params.d.y , src.params.d.z );
	printf("\n\nsrc.params.light->type = [%d]\n", src.params.light->type);

	printf("src.params.object->type) [%d]\n", src.params.object->type);
	printf("src.params.object->radius [%f]\n", src.params.object->radius);
	printf("src.params.object->specular [%f]\n", src.params.object->specular);
	printf("src.params.object->angle [%f]\n", src.params.object->angle);
	printf("src.params.object->reflection [%f]\n", src.params.object->reflection);

	printf("src.params.object->type) [%d]\n", src.params.light->type);
	printf("src.params.light->intensive [%f]\n", src.params.light->intensive);
	printf("src.params.light->direction [x = [%f]; y = [%f]; z = [%f]]\n", src.params.light->direction.x, src.params.light->direction.y, src.params.light->direction.z );
	printf("src.params.light->position [x = [%f]; y = [%f]; z = [%f]]\n", src.params.light->position.x, src.params.light->position.y, src.params.light->position.z );
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

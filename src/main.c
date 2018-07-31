/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:43:10 by avishnev          #+#    #+#             */
/*   Updated: 2018/07/31 21:42:33 by vchaus           ###   ########.fr       */
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
	parser_main(av[1], &src);
	init_host(&src);
	init_parametrs(&src);



	printf("BEFORE WHILE___\n\n\n\nCAMERA:\n");
	printf("BEFORE WHILE___positon:\n");
	printf("BEFORE WHILE___[%f, %f, %f]\n", src.params.o.x,src.params.o.y , src.params.o.z );
	printf("BEFORE WHILE___rotation:\n");
	printf("BEFORE WHILE___[%f, %f, %f]\n\n", src.params.d.x,src.params.d.y , src.params.d.z );

	printf("BEFORE WHILE___num_lights : %d\n", src.lights_cnt);
	printf("BEFORE WHILE___num_objects: %d\n\n", src.objects_cnt);

	int i;
	printf("BEFORE WHILE___LIGHTS:\n");
	for (i = 0; i < src.lights_cnt; i++)
	{
		printf("BEFORE WHILE___type      = %d\n", src.params.light[i].type);
		printf("BEFORE WHILE___intensive = %f\n", src.params.light[i].intensive);
		printf("BEFORE WHILE___position  = [%f, %f, %f]\n", src.params.light[i].position.x, 
					src.params.light[i].position.y , src.params.light[i].position.z );
		printf("BEFORE WHILE___direction = [%f, %f, %f]\n\n", src.params.light[i].direction.x, 
					src.params.light[i].direction.y , src.params.light[i].direction.z );
	}
	printf("BEFORE WHILE___OBJECTS:\n");
	for (i = 0; i < src.objects_cnt; i++)
	{
		printf("BEFORE WHILE___type      = %d\n", src.params.object[i].type);
		printf("BEFORE WHILE___size      = %f\n", src.params.object[i].radius);
		printf("BEFORE WHILE___specular  = %f\n", src.params.object[i].specular);
		printf("BEFORE WHILE___angle     = %f\n", src.params.object[i].angle);
		printf("BEFORE WHILE___reflection= %f\n", src.params.object[i].reflection);
		printf("BEFORE WHILE___position  = [%f, %f, %f]\n", src.params.object[i].mid.x, 
					src.params.object[i].mid.y , src.params.object[i].mid.z );
		printf("BEFORE WHILE___rotation  = [%f, %f, %f]\n", src.params.object[i].direction.x, 
					src.params.object[i].direction.y , src.params.object[i].direction.z );
		printf("BEFORE WHILE___color     = [%f, %f, %f]\n\n", src.params.object[i].color.x, 
					src.params.object[i].color.y , src.params.object[i].color.z );
	}
	printf("t_min = [%f] t_max = [%f]\n", src.params.t_min, src.params.t_min );
	printf("src.params.object = %d\nsrc.params.light = %d\n", src.params.objects, src.params.lights);
	printf("width = %d\n heigth = %d\n",src.params.width, src.params.height );


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

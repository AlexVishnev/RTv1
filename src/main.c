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

int		expose_hook(t_src *src)
{
	SDL_Event	e_k;
	SDL_Event 	event_mouse;
	int tmp_x;
	int tmp_y;

	if (SDL_GetMouseState(&src->c.mouse_x, &src->c.mouse_y)){
		SDL_WarpMouseInWindow(src->wind, src->c.mouse_x, src->c.mouse_y);
		printf("x = [%d]\ny = %d\n", src->c.mouse_x, src->c.mouse_y);
	}
	if (SDL_PollEvent(&e_k))
	{
		tmp_x = src->c.mouse_x;
		tmp_y = src->c.mouse_y;
		printf("%u\n", e_k.key.keysym.scancode );
		if ((e_k.type == SDL_QUIT) ||
		e_k.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_UP)
			src->params.O.z += 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_LEFT)
			src->params.O.x -= 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			src->params.O.x += 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_DOWN)
			src->params.O.z -= 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
			src->params.O.y += 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
			src->params.O.y -= 0.1;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_4)
			src->params.camera_rot.y -= 0.042;		
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_6)
			src->params.camera_rot.y += 0.042;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_8)
			src->params.camera_rot.x -= 0.042;
		else if (e_k.key.keysym.scancode == SDL_SCANCODE_KP_2)
			src->params.camera_rot.x += 0.042;
		else if (e_k.key.keysym.scancode == 55) //fix it
		{
			src->c.flag = src->params.object->type;
		//	printf("src->c.flag %d\n", src->c.flag);
		}
		else if (e_k.key.keysym.scancode == 54)
		{
			src->params.object[0].color.x = 0;
			src->params.object[0].color.y = 0;
			src->params.object[0].color.z = 0;

		}
		if (e_k.key.keysym.scancode == 1)
		{
			printf("tmpx = %d\ntmp_y = %d\n",tmp_x , tmp_y);
			if (src->c.mouse_x < tmp_x)
				src->params.camera_rot.x -= 0.042;
			else if (src->c.mouse_y < tmp_y)
				src->params.camera_rot.y -= 0.042;
			if (src->c.mouse_x > tmp_x)
				src->params.camera_rot.x += 0.042;
			else if (src->c.mouse_y > tmp_y)
				src->params.camera_rot.y += 0.042;

		}
	}
	return (1);
}

void	exit_work(t_src *src)
{
	SDL_FreeCursor(src->curs);
	SDL_DestroyWindow(src->wind);
	IMG_Quit();
	SDL_Quit();
	free(src->params.light);
	free(src->objects);
	free(src->params.object);
	free(src->buffer);
	system("leaks -q RTv1");
}
static		void  print(t_src *src)
{
	int i = 0;
	printf("src->params.O{x =[%f] y = [%f] z = [%f]}\nsrc->params.D{x =[%f] y = [%f] z = [%f]}\n",src->params.O.x,src->params.O.y,src->params.O.z,src->params.D.x,src->params.D.y,src->params.D.z);
	printf("src->params.camera_rot{x =[%f] y = [%f] z = [%f]}\n",src->params.camera_rot.x,src->params.camera_rot.y,src->params.camera_rot.z);
	printf("src->params.object.type = [%d]\nsrc->object->mid{x = [%f] y = [%f] z = [%f]}\n",src->params.object->type,src->params.object->mid.x,src->params.object->mid.y,src->params.object->mid.z);
	printf("src->params.object.direction{x = [%f] y = [%f] z = [%f]}\n",src->params.object->direction.x,src->params.object->direction.y,src->params.object->direction.z);
	printf("src->params.object.color{x = [%f] y = [%f] z = [%f]}\n",src->params.object->color.x,src->params.object->color.y,src->params.object->color.z);
	printf("src->params.object.specular = [%f]\nsrc->params.object.radius = [%f]\nsrc->params.object.angle = [%f]\nsrc->params.object.reflection = [%f]\n",src->params.object->specular, src->params.object->radius, src->params.object->angle, src->params.object->reflection);
	printf("src->params.lights = [%d]\n",src->params.lights);
}
int		main(int ac, char **av)
{
	t_src	src;

	if (ac != 2)
		error_manadge(MSG, 0, NULL);
	src.buffer = ft_memalloc(0x40000);
	read_from_file(av[1], &src);
	print(&src);
	init_host(&src);
	init_parametrs(&src);
	create_videohost(&src);
	while (DICK)
	{
		if (!expose_hook(&src))
			break ;
		kernel_function(&src);
		SDL_UpdateWindowSurface(src.wind);
	}
	exit_work(&src);
	return (0);
}

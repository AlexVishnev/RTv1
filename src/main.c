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

void	instruction(void)
{
	error_manadge(MSG);	
}

void	init_host(t_src *src)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error_manadge((char *)SDL_GetError());
	if (TTF_Init() < 0)
		error_manadge((char *)SDL_GetError());
	src->wind = SDL_CreateWindow("RT_v1", 
					SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOWPOS_UNDEFINED,
					WIN_WD, WIN_HG, 
					SDL_WINDOW_ALLOW_HIGHDPI);
	src->surf = SDL_GetWindowSurface(src->wind);
	src->img_pxl = src->surf->pixels;
}

int 		expose_hook(t_src *src)
{
	SDL_Event	key;

	while (SDL_PollEvent(&key))
	{
		if ((key.type == SDL_QUIT) ||
		 key.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
	}
	return (1);	
}

int		main(int ac, char **av)
{
	t_src	*src;

	if (ac != 2)
		instruction();
	if (!(src = (t_src *)ft_memalloc(sizeof(t_src))))
		return (0);
	init_host(src);
	read_from_file(av[1], src);
	while (42)
	{
		if (!expose_hook(src))
			break ;
		SDL_UpdateWindowSurface(src->wind);

	}
		// SDL_DestroyWindow(src->wind);
		// IMG_Quit();
		// SDL_Quit();
	return (0);
}

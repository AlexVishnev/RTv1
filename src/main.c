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
	SDL_Event	event_key;

	while (SDL_PollEvent(&event_key))
	{
		if ((event_key.type == SDL_QUIT) ||
		event_key.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
	}

	return (1);
}

void	exit_work(t_src *src)
{
	SDL_DestroyWindow(src->wind);
	IMG_Quit();
	SDL_Quit();
// 	free(src->light.light_p);
//	free(src->objects);
//	free(src->params.object);
	free(src);
	system("leaks -q RTv1");
}

int		main(int ac, char **av)
{
	t_src	*src;

	if (ac != 2)
		error_manadge(MSG, 0, NULL);
	src = (t_src *)ft_memalloc(sizeof(t_src));
	read_from_file(av[1], src);
//	init_host(src);
//	create_videohost(src);
//	while (DICK)
//	{
//		if (!expose_hook(src))
//			break ;
//		kernel_function(src);
//		SDL_UpdateWindowSurface(src->wind);
//	}
	printf("%f\n ",ft_atof("1.511"));
	exit_work(src);
	return (0);
}

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
}

int		main(int ac, char **av)
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
		SDL_UpdateWindowSurface(src.wind);
	}
	exit_work(&src);
	return (0);
}

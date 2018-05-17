/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:24:24 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/11 17:24:58 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_host(t_src *src)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error_manadge((char *)SDL_GetError(), 0, NULL);
	if (TTF_Init() < 0)
		error_manadge((char *)SDL_GetError(), 0, NULL);
	src->wind = SDL_CreateWindow("RT_v1",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WIN_WD, WIN_HG,
					SDL_WINDOW_ALLOW_HIGHDPI);
	src->surf = SDL_GetWindowSurface(src->wind);
	src->img_pxl = src->surf->pixels;
}

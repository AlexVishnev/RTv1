/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:36:39 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/23 20:36:40 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	take_screenshot(t_src *src, const char *pathfile)
{
	Uint32		rmask;
	Uint32		gmask;
	Uint32		bmask;
	char		*name;
	SDL_Surface	*screen;

	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	name = ft_strjoin("screenshots/screenshot[", pathfile);
	screen = SDL_CreateRGBSurfaceFrom(src->surf->pixels, src->surf->w,
		src->surf->h, 32, src->surf->pitch, rmask,
		gmask, bmask, 0x0);
	SDL_SaveBMP(screen, name);
	SDL_FreeSurface(screen);
	free(name);
}

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

#include "rt.h"

void		take_screenshot(t_src *src, const char *pathfile)
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

static void	focus_change(t_src *src)
{
	if (src->c.e_k.wheel.y > 0)
		src->params.focus += 0.00025;
	else
		src->params.focus -= 0.00025;
}

static void	mouse_capture_false(t_src *src)
{
	SDL_CaptureMouse(false);
	src->c.mouse_on = 42;
	SDL_ShowCursor(1);
}

int			expose_hook(t_src *src)
{
	if (SDL_GetMouseState(&src->c.mouse_x, &src->c.mouse_y))
		SDL_WarpMouseInWindow(src->wind, src->c.mouse_x, src->c.mouse_y);
	if (SDL_PollEvent(&src->c.e_k))
	{
		if (src->c.e_k.key.state == SDL_PRESSED)
		{
			if ((src->c.e_k.type == SDL_QUIT) ||
			src->c.e_k.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return (0);
			else if (src->c.e_k.key.keysym.scancode > 1 &&
				src->c.e_k.key.keysym.scancode < 89)
				keyboards_control(src, src->c.e_k.key.keysym.scancode);
		}
		if (src->c.e_k.button.button == SDL_BUTTON_LEFT)
			src->c.mouse_on = 2;
		else if (src->c.e_k.button.button == SDL_BUTTON_RIGHT)
			mouse_capture_false(src);
		else if (src->c.mouse_on == 2)
			mouse_control(src, src->c.e_k);
		if (src->c.e_k.type == SDL_MOUSEWHEEL &&
								!(!src->c.e_k.wheel.x && !src->c.e_k.wheel.y))
			focus_change(src);
	}
	return (1);
}

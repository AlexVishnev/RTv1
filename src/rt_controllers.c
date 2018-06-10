/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_controllers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:27:30 by avishnev          #+#    #+#             */
/*   Updated: 2018/06/10 20:27:31 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	keyboards_control(t_src *src, Uint8 scancode)
{
	if (scancode == SDL_SCANCODE_UP)
		src->params.o.z += 0.1;
	else if (scancode == SDL_SCANCODE_LEFT)
		src->params.o.x -= 0.1;
	else if (scancode == SDL_SCANCODE_RIGHT)
		src->params.o.x += 0.1;
	else if (scancode == SDL_SCANCODE_DOWN)
		src->params.o.z -= 0.1;
	else if (scancode == SDL_SCANCODE_KP_PLUS)
		src->params.o.y += 0.1;
	else if (scancode == SDL_SCANCODE_KP_MINUS)
		src->params.o.y -= 0.1;
	else if (scancode == SDL_SCANCODE_KP_4)
		src->params.camera_rot.y -= 0.042;
	else if (scancode == SDL_SCANCODE_KP_6)
		src->params.camera_rot.y += 0.042;
	else if (scancode == SDL_SCANCODE_KP_8)
		src->params.camera_rot.x -= 0.042;
	else if (scancode == SDL_SCANCODE_KP_2)
		src->params.camera_rot.x += 0.042;
	else if (scancode == SDL_SCANCODE_R)
	{
		src->params.camera_rot.y = 0;
		src->params.camera_rot.x = 0;
	}
}

void	mouse_control(t_src *src, SDL_Event e_k)
{
	SDL_ShowCursor(0);
	while (DICK)
	{
		if (e_k.motion.xrel < 0)
			src->params.camera_rot.y += 0.015;
		else if (e_k.motion.x > 0)
			src->params.camera_rot.y -= 0.015;
		if (e_k.motion.yrel < 0)
			src->params.camera_rot.x += 0.015;
		else if (e_k.motion.yrel > 0)
			src->params.camera_rot.x -= 0.015;
		break ;
	}
}

int		expose_hook(t_src *src)
{
	if (SDL_GetMouseState(&src->c.mouse_x, &src->c.mouse_y))
		SDL_WarpMouseInWindow(src->wind, src->c.mouse_x, src->c.mouse_y);
	if (SDL_PollEvent(&src->c.e_k))
	{
		if ((src->c.e_k.type == SDL_QUIT) ||
		src->c.e_k.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
		if (src->c.flag != 2)
			keyboards_control(src, src->c.e_k.key.keysym.scancode);
		if (src->c.e_k.button.button == SDL_BUTTON_LEFT)
			src->c.flag = 2;
		if (src->c.e_k.button.button == SDL_BUTTON_RIGHT)
			src->c.flag = 3;
		if (src->c.flag == 2)
			mouse_control(src, src->c.e_k);
		if (src->c.flag != 2)
			SDL_ShowCursor(1);
	}
	return (1);
}

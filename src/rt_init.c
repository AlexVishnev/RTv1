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

#include "rt.h"

void		init_host(t_src *src)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error_manadge((char *)SDL_GetError(), 0, NULL);
	if (TTF_Init() < 0)
		error_manadge((char *)SDL_GetError(), 0, NULL);
	src->wind = SDL_CreateWindow("Ray Tracer",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WIN_WD, WIN_HG,
					SDL_WINDOW_ALLOW_HIGHDPI);
	src->surf = SDL_GetWindowSurface(src->wind);
	src->img_pxl = src->surf->pixels;
}

void		init_parametrs(t_src *src)
{
	src->params.t_max = INFINITY;
	src->params.t_min = 0.0001f;
	src->params.look_pos.width = 1.0f;
	src->params.look_pos.height = 1.0f;
	src->params.look_pos.dist = 1.0f;
	src->params.width = src->surf->w;
	src->params.height = src->surf->h;
	src->params.lights = src->lights_cnt;
	src->params.objects = src->objects_cnt;
	src->params.color_filter = 0;
	src->buffer = ft_memalloc(0x40000);
	src->c.row = 0;
	src->c.i = -1;
	src->params.d.x = src->params.d.x * M_PI / 180.f;
	src->params.d.y = src->params.d.y * M_PI / 180.f;
	src->params.d.z = src->params.d.z * M_PI / 180.f;
	src->params.camera_rot = src->params.d;
	if (src->params.ssaa != 4 && src->params.ssaa != 8)
		src->params.ssaa = 1;
}

void		wr_data(Uint8 data[], Uint8 mask[], const char *im[], t_src *s)
{
	(void)data;
	(void)mask;
	if (im[s->c.row + 4][s->c.col] == 'X')
	{
		s->c.data[s->c.i] |= 0x01;
		s->c.mask[s->c.i] |= 0x01;
	}
	if (im[s->c.row + 4][s->c.col] == '.')
		s->c.mask[s->c.i] |= 0x01;
	if (im[s->c.row + 4][s->c.col] == ' ')
		return ;
}

SDL_Cursor	*init_system_cursor(const char *image[], t_src *src)
{
	src->c.i = -1;
	while (src->c.row < 32)
	{
		src->c.col = 0;
		while (src->c.col < 32)
		{
			if (src->c.col % 8)
			{
				src->c.data[src->c.i] <<= 1;
				src->c.mask[src->c.i] <<= 1;
			}
			else
			{
				++src->c.i;
				src->c.data[src->c.i] = 0;
				src->c.mask[src->c.i] = 0;
			}
			wr_data(src->c.data, src->c.mask, image, src);
			++src->c.col;
		}
		++src->c.row;
	}
	return (SDL_CreateCursor(src->c.data, src->c.mask, 32, 32,
		src->c.hot_x, src->c.hot_y));
}

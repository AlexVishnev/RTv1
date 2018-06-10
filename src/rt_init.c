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

static	const	char	*g_arrow[] = {
	"    32    32        3            1",
	"X c #f49842",
	". c #000000",
	"  c f49842",
	"           .X....X.                 ",
	"          .XX....XX.                ",
	"        .XXXX..XXXXX.               ",
	"       .XXXXXXXXXXXXX.              ",
	"      .XXXXXXXXXXXXXXX.             ",
	"       .XXXXXXXXXXXXX.              ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                 ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"   .XXX. .XXXXXXXXX. .XXX.         ",
	"  .XXXXXXXXXXXXXXXXXXXXXXX.       ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.      ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.     ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.     ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.      ",
	"  .XXXXXXXXXXXXXXXXXXXXXXX.       ",
	"   .XXXXXXXXXXXXXXXXXXXXX.        ",
	"     .XXXXXXXX..XXXXXXXX.         ",
	"      .XXXXXXX..XXXXXXX.          ",
	"                                    ",
	"0,0"
};

void		init_host(t_src *src)
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
	src->curs = init_system_cursor(g_arrow, src);
	SDL_SetCursor(src->curs);
}

void		init_parametrs(t_src *src)
{
	src->params.t_max = INFINITY;
	src->params.t_min = 0.001f;
	src->params.look_pos.width = 1.0f;
	src->params.look_pos.height = 1.0f;
	src->params.look_pos.dist = 1.0f;
	src->params.width = src->surf->w;
	src->params.height = src->surf->h;
	src->params.lights = src->lights_cnt;
	src->params.objects = src->objects_cnt;
	src->buffer = ft_memalloc(0x40000);
	src->c.row = 0;
	src->c.i = -1;
}

void		wr_data(Uint8 data[], Uint8 mask[], const char *im[], t_src *s)
{
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

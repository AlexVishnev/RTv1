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

static	const	char	*arrow[] = {
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
	"   .XXX. .XXXXXXXXX. .XXXX.         ",
	"  .XXXXX..XXXXXXXXX..XXXXXXX.       ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXXXX.      ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXXXXX.     ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXXXXX.     ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXXXX.      ",
	"  .XXXXXXXXXXXXXXXXXXXXXXXXX.       ",
	"   .XXXXXXXXXXX. .XXXXXXXXX.        ",
	"     .XXXXXXXX.   .XXXXXXX.         ",
	"      .XXXXX.      .XXXXX.          ",
	"                                    ",
	"0,0"
};

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
	src->curs = init_system_cursor(arrow);
	SDL_SetCursor(src->curs);

}

void	init_parametrs(t_src *src)
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
}


SDL_Cursor	*init_system_cursor(const char *image[])
{
	int		i;
	int		row;
	int		col;
	Uint8	data[4*32];
	Uint8	mask[4*32];
	int		hot_x;
	int		hot_y;

	i = -1;
	for (row=0; row<32; ++row) 
	{
		for (col=0; col<32; ++col)
		{
			if (col % 8) 
			{
				data[i] <<= 1;
				mask[i] <<= 1;
			}
			else
			{
				++i;
				data[i] = mask[i] = 0;
			}
	switch (image[4+row][col])
	{
		case 'X':
			data[i] |= 0x01;
			mask[i] |= 0x01;
			break;
		case '.':
			mask[i] |= 0x01;
			break;
		case ' ':
			break;
		}
	}
	}
	sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
	return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

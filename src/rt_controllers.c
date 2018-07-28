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
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"         .XXXXXXXXX.                ",
	"   .XXX. .XXXXXXXXX. .XXX.          ",
	"  .XXXXXXXXXXXXXXXXXXXXXXX.         ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.        ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.        ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.        ",
	" .XXXXXXXXXXXXXXXXXXXXXXXXX.        ",
	"  .XXXXXXXXXXXXXXXXXXXXXXX.         ",
	"   .XXXXXXXXXXXXXXXXXXXXX.          ",
	"     .XXXXXXXX..XXXXXXXX.           ",
	"      .XXXXXXX..XXXXXXX.            ",
	"                                    ",
	"0,0"
};

void	keyboards_control(t_src *src, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_UP)
		src->params.o.z += 0.4;
	else if (scancode == SDL_SCANCODE_LEFT)
		src->params.o.x -= 0.4;
	else if (scancode == SDL_SCANCODE_RIGHT)
		src->params.o.x += 0.4;
	else if (scancode == SDL_SCANCODE_DOWN)
		src->params.o.z -= 0.4;
	else if (scancode == SDL_SCANCODE_KP_PLUS)
		src->params.o.y += 0.4;
	else if (scancode == SDL_SCANCODE_KP_MINUS)
		src->params.o.y -= 0.4;
	else
		keyboards_control1(src, scancode);
}

void	mouse_control(t_src *src, SDL_Event e_k)
{
	SDL_ShowCursor(0);
	SDL_CaptureMouse(true);
	while (DICK)
	{
		if (e_k.motion.xrel < 0 && e_k.motion.xrel > -42)
			src->params.camera_rot.y -= MOUSE_SPEED;
		else if (e_k.motion.xrel > 0 && e_k.motion.xrel < 42)
			src->params.camera_rot.y += MOUSE_SPEED;
		if (e_k.motion.yrel < 0 && e_k.motion.yrel > -42)
			src->params.camera_rot.x -= MOUSE_SPEED;
		else if (e_k.motion.yrel > 0 && e_k.motion.yrel < 42)
			src->params.camera_rot.x += MOUSE_SPEED;
		break ;
	}
}

void	keyboards_control1(t_src *src, SDL_Scancode scancode)
{
	char		*fr;
	char		*it;
	static int	i;

	(void)scancode;
	if (src->c.e_k.key.keysym.scancode == SDL_SCANCODE_R)
	{
		src->params.camera_rot.y = 0;
		src->params.camera_rot.x = 0;
		SDL_FreeCursor(src->curs);
	}
	else if (src->c.e_k.key.keysym.scancode == SDL_SCANCODE_H)
	{
		src->curs = init_system_cursor(g_arrow, src);
		SDL_SetCursor(src->curs);
	}
	else if (src->c.e_k.key.keysym.scancode == SDL_SCANCODE_S)
	{
		it = ft_itoa(i);
		take_screenshot(src, fr = ft_strjoin(it , "].bmp"));
		i++;
		free(fr);
		free(it);
	}
}

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

int		expose_hook(t_src *src)
{
	if (SDL_GetMouseState(&src->c.mouse_x, &src->c.mouse_y))
		SDL_WarpMouseInWindow(src->wind, src->c.mouse_x, src->c.mouse_y);
	while (SDL_PollEvent(&src->c.e_k))
	{
		if ((src->c.e_k.type == SDL_QUIT) ||
		src->c.e_k.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
		if (src->c.e_k.key.keysym.scancode > 10 &&
			src->c.e_k.key.keysym.scancode < 89)
			keyboards_control(src, src->c.e_k.key.keysym.scancode);
		if (src->c.e_k.button.button == SDL_BUTTON_LEFT)
			src->c.mouse_on = 2;
		if (src->c.e_k.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_CaptureMouse(false);
			src->c.mouse_on = 42;
			SDL_ShowCursor(1);
		}
		if (src->c.mouse_on == 2)
			mouse_control(src, src->c.e_k);
	}
	return (1);
}

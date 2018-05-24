/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:21:54 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 18:06:10 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_manadge(char *str, int fl, char *src)
{
	if (fl == 1)
		free(src);
	printf("BEFORE EXIT %s\n", src);
	ft_putendl(str);
	system("leaks -q RTv1");
	exit(1);
}

int		check_adecvate(int lim, t_pos *cord, int fl, char *free, t_color *s)
{
	if (cord)
	{
		if (cord->x < -lim || cord->y < -lim || cord->z < -lim
			|| cord->x > lim || cord->y > lim || cord->z > lim)
		{
			if (fl == 1)
				error_manadge(MSG_CAM, 0, free);
			if (fl == 2)
				error_manadge(MSG_LGHT, 0, free);
			if (fl == 3)
				error_manadge(MSG_OBJ, 0, free);
		}
	}
	else if (s)
	{
		if (s->red > lim || s->green > lim || s->blue > lim)
			error_manadge(MSG_CLR, 0, free);
	}
	return (0);
}

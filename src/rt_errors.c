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

void	error_manadge(char *message, int flag, char *src)
{
	if (flag == 1)
		free(src);
	ft_putendl(message);
	exit(1);
}

int		check_adecvate(int lim, t_pos *cord, int fl, t_color *s)
{
	if (cord)
	{
		if (cord->x < -lim || cord->y < -lim || cord->z < -lim
			|| cord->x > lim || cord->y > lim || cord->z > lim)
		{
			if (fl == 1)
				error_manadge(MSG_CAM, 0, NULL);
			if (fl == 2)
				error_manadge(MSG_LGHT, 0, NULL);
			if (fl == 3)
				error_manadge(MSG_OBJ, 0, NULL);
		}
	}
	else if (s)
	{
		if (s->red > (t_uint)lim || s->green > (t_uint)lim || s->blue > (t_uint)lim)
			error_manadge(MSG_CLR, 0, NULL);
	}
	return (0);
}

int		br_adecvat(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		while (s[i] == '{' || s[i] == '(' || s[i] == '[')
			i++;
		if ((s[i - 1] == '{' && s[i] != '}') || (s[i - 1] == '(' && s[i] != ')')
			|| (s[i - 1] == '[' && s[i] != ']'))
			return (1);
		i++;
	}
	return (0);
}

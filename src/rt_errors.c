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

void		error_manadge(char *str, int flag, char *src)
{
	if (flag == 1)
		free(src);
	ft_putendl(str);
	system("leaks -q RTv1");
	exit(1);
}

int			check_adecvate(int limit, t_pos *cord, int flag, char *free)
{
	if (cord->x < -limit || cord->y < -limit || cord->z < -limit
		|| cord->x > limit || cord->y > limit || cord->z > limit)
	{
		if (flag == 1)
			error_manadge(MSG_CAM, 0, free);
	}
	return (0);
}

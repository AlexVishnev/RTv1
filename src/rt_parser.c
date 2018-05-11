/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:26:38 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/11 17:26:39 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_camera_position(char *cord, t_src *src)
{
	int		len;

	len = ft_strlen(cord);
	if (len > 15 || len < 9 || cord[0] != '[' || cord[len - 1] != ']')
		error_manadge(MSG_FORMAT, 0, cord);
	while (*cord)
	{
		if (*cord == '{')
			src->camera.cam_pos.x = ft_atoi(++cord);
		if (*cord == '-' || ft_isdigit(*cord))
		{
			cord++;
			while (ft_isdigit(*cord))
				cord++;
		}
		if (*cord == ',' && src->camera.cam_pos.y == 0)
			src->camera.cam_pos.y = ft_atoi(++cord);
		if (*cord == ',' && src->camera.cam_pos.z == 0)
			src->camera.cam_pos.z = ft_atoi(++cord);
		cord++;
	}
	check_adecvate(50, &src->camera.cam_pos, 1, cord);

}

void	get_spotlights_params(char *cord, t_src *src)
{
	int		nbr;
	
	nbr = ft_count_chars(cord, ';') + 1;

	src->ligth.l_pos = (t_pos **)ft_memalloc(sizeof(t_pos *) * nbr); //////////////////////
	while (*cord)
	{
		if (*cord == '{')
			src->ligth.l_pos->x = ft_atoi(++cord);

		cord++;
	}
	free(src->ligth.l_pos);

}

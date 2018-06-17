/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:26:38 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 19:21:12 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_camera_direction(char *cord, t_src *src)
{
	src->cam_pos = (t_ray){-500, -505, -501, -500, 0};
	while (*cord && *cord != ']')
	{
		if (*cord == '{')
			src->cam_pos.x = ft_atof(++cord, ',');
		else if (*cord == ',' && src->cam_pos.y == -505)
			src->cam_pos.y = ft_atof(++cord, ',');
		else if (src->cam_pos.z == -501 && *cord == ',')
			src->cam_pos.z = ft_atof(++cord, '}');
		cord++;
	}
	check_adecvate(POS_LIM, (t_pos *)&src->cam_pos, 1, NULL);
	src->params.d = (t_ray){(src->cam_pos.x * M_PI) / 180,
		(src->cam_pos.y * M_PI) / 180,
		(src->cam_pos.z * M_PI) / 180, 0, 0};
	src->cam_pos = (t_ray){0, 0, 0, 0 - 0, 0};
}

void	get_camera_position(char *cord, t_src *src)
{
	int		len;

	len = ft_strlen(cord);
	if (ft_count_chars(cord, ',') != 4)
		error_manadge(MSG_FORMAT, 0, cord);
	if (len < 9 || cord[0] != '[' || cord[len - 1] != ']')
		error_manadge(MSG_FORMAT, 0, cord);
	get_camera_direction(&cord[len / 2], src);
	while (*cord && *cord != ';' && *(cord - 1) != '}')
	{
		if (*cord == '{')
			src->cam_pos.x = ft_atof(++cord, ',');
		else if (*cord == ',' && src->cam_pos.y == 0)
			src->cam_pos.y = ft_atof(++cord, ',');
		else if (*cord == ',' && src->cam_pos.z == 0)
			src->cam_pos.z = ft_atof(++cord, '}');
		cord++;
	}
	src->params.o = (t_ray){src->cam_pos.x,
		src->cam_pos.y,
		src->cam_pos.z, 0, 0};
	check_adecvate(POS_LIM, (t_pos *)&src->cam_pos, 1, NULL);
}

void	get_spotlights_direction(char *cord, t_src *src, int ind)
{
	src->params.light[ind].direction = (t_ray){0, 0, 0, 0, 0};
	src->params.light[ind].position = (t_ray){0, 0, 0, 0, 0};
	while (*cord != ']' && *cord)
	{
		if (*cord == '{')
			src->params.light[ind].direction.x = ft_atof(++cord, ',');
		else if (*cord == ',' && src->params.light[ind].direction.y == 0)
			src->params.light[ind].direction.y = ft_atof(++cord, ',');
		else if (*cord == ',' && src->params.light[ind].direction.z == 0)
			src->params.light[ind].direction.z = ft_atof(++cord, '}');
		else if (*cord == '(')
			src->params.light[ind].intensive = ft_atof(++cord, ')');
		cord++;
	}
	check_adecvate(POS_LIM, (t_pos *)&src->params.light[ind].direction,
		2, NULL);
}

void	get_spotlights_params(char *cord, t_src *src, int ind)
{
	if (ft_count_chars(cord, ',') != 4)
		error_manadge(MSG_FORMAT, 0, cord);
	get_spotlights_direction(&cord[ft_strlen(cord) / 2], src, ind);
	while (*cord != '}')
	{
		if (*cord == '(' && *(cord + 3) == '{')
			src->params.light[ind].type = ft_atoi(++cord);
		else if (*cord == '{')
			src->params.light[ind].position.x = ft_atof(++cord, ',');
		else if (*cord == ',' && src->params.light[ind].position.y == 0)
			src->params.light[ind].position.y = ft_atof(++cord, ',');
		else if (*cord == ',' && src->params.light[ind].position.z == 0)
			src->params.light[ind].position.z = ft_atof(++cord, ',');
		cord++;
	}
	if (src->params.light[ind].type < 1 || src->params.light[ind].type > 3)
		error_manadge(MSG_L, 0, NULL);
	check_adecvate(POS_LIM, (t_pos *)&src->params.light[ind].position, 2, NULL);
}

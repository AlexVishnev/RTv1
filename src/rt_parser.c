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

void	get_camera_position(char *cord, t_src *src)
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

void	get_spotlights_params(char *cord, t_src *src, int ind)
{
	//try to rework whit strsplit
	printf("cor ========== %s\n", cord);
	src->light.light_p = (t_pos *)malloc(sizeof(t_pos) * src->light.nbr + 1);
	src->light.light_p[ind].y = 0;
	src->light.light_p[ind].z = 0;
	src->light.light_p[ind].x = 0;
	while (*cord && (*cord != ';' || *cord != ']'))
	{
		if (*cord == '{' && src->light.light_p[ind].x == 0)
			src->light.light_p[ind].x = ft_atoi(++cord);
		if (*cord == '-' || ft_isdigit(*cord))
		{
			cord++;
			while (ft_isdigit(*cord))
				cord++;
		}
		if (*cord == ',' && src->light.light_p[ind].y == 0)
			src->light.light_p[ind].y = ft_atoi(++cord);
		if (*cord == ',' && src->light.light_p[ind].z == 0)
			src->light.light_p[ind].z = ft_atoi(++cord);
		cord++;
	}
	printf("WHILEEEEES == [%d]\n",ind);
	printf("x == [%d]\ny == [%d]\nz == [%d]\n", src->light.light_p[ind].x, src->light.light_p[ind].y,src->light.light_p[ind].z);
	//printf("x == [%d]\ny == [%d]\nz == [%d]\n", src->light.light_p[1].x, src->light.light_p[1].y,src->light.light_p[1].z);
	free(src->light.light_p);
}

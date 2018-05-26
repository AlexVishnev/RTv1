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
	printf("cord cam = %s\nlen = [%d]\n",cord, len );
	if (len > 33 || len < 9 || cord[0] != '[' || cord[len - 1] != ']')
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
	check_adecvate(POS_LIM, &src->camera.cam_pos, 1, cord, NULL);
}

void	get_spotlights_params(char *cord, t_src *src, int ind)
{
	src->light.light_p = malloc(sizeof(t_pos) * src->light.nbr);
	src->light.light_p[ind].y = 0;
	src->light.light_p[ind].z = 0;
	src->light.light_p[ind].x = 0;
	while (*cord != '{')
		cord++;
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
	check_adecvate(POS_LIM, src->light.light_p, 2, cord, NULL);
	free(src->light.light_p);
}

t_pos	get_position_object(char *cord, t_pos pos)
{
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	while (*cord != '}' && *cord)
	{
		if (*cord == '{' && pos.x == 0)
			pos.x = ft_atoi(++cord);
		if (*cord == ',' && pos.y == 0)
			pos.y = ft_atoi(++cord);
		if (*cord == ',' && pos.z == 0)
			pos.z = ft_atoi(++cord);
		cord++;
	}
	check_adecvate(100, &pos, 0, cord, NULL);
	return (pos);
}

t_color	get_color_object(char *col)
{
	t_color	color;

	col = ft_strchr(col, '{');
	color.green = -255;
	color.blue = -255;
	while (*col != '}' && *col)
	{
		if (*col == '{')
			color.red =	ft_u_atoi(++col);
		if (*col == ',' && color.green == -255)
			color.green = ft_u_atoi(++col);
		if (*col == ',' && color.blue == -255)
			color.blue = ft_u_atoi(++col);
		col++;
	}
	check_adecvate(255, NULL, 1, col, &color);
	//free(col);
	return (color);
}

t_obj	*get_object_params(char *params, t_obj *obj)
{
	while (*params != '(' && *params)
		params++;
	obj->type = ft_atoi(++params);
	if (obj->type > 4 || obj->type < 1)
		error_manadge("Error: wrong object type", 0, params);
	while (*params && *params != ']')
	{
		if (*params == ')' && *(params + 1) == '{')
		{
			obj->color = get_color_object(params);
			params += 6;
		}
		if (*params == '{' && ft_unstrlen(&(*params), '}') > 10)
		{
			obj->object_pos = get_position_object(params, obj->object_pos);
			printf("x = [%f]\ny = [%f]\nz = [%f]\n",obj->object_pos.x,obj->object_pos.y,obj->object_pos.z );
			params += 6;
		}
		params++;
	}
	printf("red [%u]\ngreen [%u]\nblue [%u]\n", obj->color.red, obj->color.green, obj->color.blue);
	return (obj);
}
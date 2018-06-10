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
	src->params.D = (t_ray){(src->cam_pos.x * M_PI) / 180,
		(src->cam_pos.y * M_PI) / 180,
		(src->cam_pos.z * M_PI) / 180, 0, 0};
	src->cam_pos = (t_ray){0, 0, 0, 0, 0};
}

void	get_camera_position(char *cord, t_src *src)
{
	int		len;

	len = ft_strlen(cord);
	if (len > 33 || len < 9 || cord[0] != '[' || cord[len - 1] != ']')
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
	src->params.O = (t_ray){src->cam_pos.x,
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
	check_adecvate(POS_LIM, (t_pos *)&src->params.light[ind].position, 2, NULL);
}

t_ray	get_position_object(char *cord, t_src *src)
{
	t_ray		ray;

	src->pos = (t_pos){0, 0, 0};
	while (*cord != '}' && *cord)
	{
		if (*cord == '{' && src->pos.x == 0)
			src->pos.x = ft_atof(++cord, ',');
		if (*cord == ',' && src->pos.y == 0)
			src->pos.y = ft_atof(++cord, ',');
		if (*cord == ',' && src->pos.z == 0)
			src->pos.z = ft_atof(++cord, ',');
		cord++;
	}
	check_adecvate(100, &src->pos, 0, NULL);
	ray = (t_ray){src->pos.x, src->pos.y, src->pos.z, 0, 0};
	return (ray);
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
			color.red = ft_u_atoi(++col);
		if (*col == ',' && color.green == -255)
			color.green = ft_u_atoi(++col);
		if (*col == ',' && color.blue == -255)
			color.blue = ft_u_atoi(++col);
		col++;
	}
	check_adecvate(255, NULL, 1, &color);
	return (color);
}

void	get_spetial_params(t_obj *obj, char *params)
{
	while (*params != ']' && *params)
	{
		if (*params == '(' && obj->radius == 0)
			obj->radius = ft_atof(++params, ')');
		if (*params == '(' && obj->specular == 0)
			obj->specular = ft_atof(++params, ')');
		if (*params == '(' && obj->angle == 0)
			obj->angle = ft_atof(++params, ')');
		if (*params == '(' && obj->reflection == 0)
			obj->reflection = ft_atof(++params, ')');
		params++;
	}
}

t_obj	get_object_params(char *par, t_obj *obj, t_src *src)
{
	while (*par != '(' && *par)
		par++;
	obj->type = ft_atoi(++par);
	if (obj->type > 4 || obj->type < 1)
		error_manadge("Error: wrong object type", 0, par);
	while (*par && *par != '(')
	{
		if (*par == ')' && *(par + 1) == '{')
		{
			src->color = get_color_object(par);
			par += 6;
		}
		else if (*par == '{' && *(par + ft_unstrlen(&(*par), '}') + 1) != '(')
		{
			obj->mid = get_position_object(par, src);
			par += ft_unstrlen(&(*par), '}');
		}
		else if (*par == '{' && *(par + ft_unstrlen(&(*par), '}') + 1) == '(')
			obj->direction = get_position_object(par, src);
		par++;
	}
	get_spetial_params(obj, par);
	obj->color = (t_ray){src->color.red, src->color.blue,
		src->color.green, 0, 0};
	return (*obj);
}

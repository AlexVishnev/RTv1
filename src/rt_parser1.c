/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:31:41 by avishnev          #+#    #+#             */
/*   Updated: 2018/06/10 20:31:43 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_float3	get_position_object(char *cord, t_src *src)
{
	cl_float3		ray;

	src->pos = (t_pos){0, 0, 0, 0};
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
	check_adecvate(10000, &src->pos, 0, NULL);
	ray.x = src->pos.x;
	ray.y = src->pos.y;
	ray.z = src->pos.z;
	return (ray);
}

t_color	get_color_object(char *col)
{
	t_color	color;

	col = ft_strchr(col, '{');
	color.green = -255;
	color.blue = -245;
	while (*col != '}' && *col)
	{
		if (*col == '{')
			color.red = ft_u_atoi(++col);
		if (*col == ',' && color.green == (unsigned int)-255)
			color.green = ft_u_atoi(++col);
		if (*col == ',' && color.blue == (unsigned int)-245)
			color.blue = ft_u_atoi(++col);
		col++;
	}
	check_adecvate(254 + 1, NULL, 1, &color);
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
	if (obj->reflection > 1 || obj->reflection < 0)
		error_manadge(REF, 0, params);
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
	obj->color.x = src->color.red;
	obj->color.y = src->color.green;
	obj->color.z = src->color.blue;
	obj->color.w = 0;
	return (*obj);
}

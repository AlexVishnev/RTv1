#include "rt.h"

t_bool	parse_lights_angle_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "angle");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Number)
	{
		r->scene->lights[i]->angle = (float)temp2->valuedouble;
		if (!(parse_float_number_json_vers(&r->scene->lights[i]->angle,
				0, 180)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_len_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "len");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Number)
	{
		r->scene->lights[i]->len = (float)temp2->valuedouble;
		if (!(parse_float_number_json_vers(&r->scene->lights[i]->len,
				1, 10000)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_power_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "power");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Number)
	{
		r->scene->lights[i]->power = (float)temp2->valuedouble;
		if (!(parse_float_number_json_vers(&r->scene->lights[i]->power,
			P_MIN, P_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_color_detail(t_rt *r, cJSON *temp2, int i, char *color)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, color);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(color, "Red") == 0)
			r->scene->lights[i]->color.red = (float)temp3->valuedouble;
		else if (ft_strcmp(color, "Green") == 0)
			r->scene->lights[i]->color.green = (float)temp3->valuedouble;
		else if (ft_strcmp(color, "Blue") == 0)
			r->scene->lights[i]->color.blue = (float)temp3->valuedouble;
		else if (ft_strcmp(color, "Alpha") == 0)
			r->scene->lights[i]->color.alpha = (float)temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_color_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "color");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		if (!(parse_lights_color_detail(r, temp2, i, "Red")))
			return (false);
		if (!(parse_lights_color_detail(r, temp2, i, "Blue")))
			return (false);
		if (!(parse_lights_color_detail(r, temp2, i, "Green")))
			return (false);
		if (!(parse_lights_color_detail(r, temp2, i, "Alpha")))
			return (false);
		if (!(parse_color_json_vers(&r->scene->lights[i]->color, C_MIN, C_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

#include "rt.h"

t_bool		parse_mats_color_detail(t_rt *r, cJSON *temp2, int i, char *color)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, color);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(color, "Red") == 0)
			r->scene->materials[i]->diffuse.red = temp3->valuedouble;
		else if (ft_strcmp(color, "Green") == 0)
			r->scene->materials[i]->diffuse.green = temp3->valuedouble;
		else if (ft_strcmp(color, "Blue") == 0)
			r->scene->materials[i]->diffuse.blue = temp3->valuedouble;
		else if (ft_strcmp(color, "Alpha") == 0)
			r->scene->materials[i]->diffuse.alpha = temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_color_single(t_rt *r, cJSON *temp2, int i)
{
	i++;
	if (!(parse_mats_color_detail(r, temp2, i, "Red")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Green")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Blue")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Alpha")))
		return (false);
	if (!(parse_color_json_vers(&r->scene->materials[i]->diffuse,
		C_MIN, C_MAX)))
		return (false);
	return (true);
}

t_bool		parse_mats_color_array_1(t_rt *r, cJSON *temp2, int i)
{
	if (!(parse_mats_color_detail(r, temp2, i, "Red")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Green")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Blue")))
		return (false);
	if (!(parse_mats_color_detail(r, temp2, i, "Alpha")))
		return (false);
	if (!(parse_color_json_vers(&r->scene->materials[i]->diffuse,
		C_MIN, C_MAX)))
		return (false);
	return (true);
}

t_bool		parse_mats_color_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;
	cJSON	*temp2;

	i = 0;
	while (i < cJSON_GetArraySize(temp))
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		temp2 = cJSON_GetObjectItem(elem, "color");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Object)
		{
			if (!(parse_mats_color_array_1(r, temp2, i)))
				return (false);
		}
		else
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_mats_color_1(t_rt *r, cJSON *temp, int i)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "color");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Object && r->scene->mats_n == 1)
		{
			if (!(parse_mats_color_single(r, temp2, i)))
				return (false);
		}
		else
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_color_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

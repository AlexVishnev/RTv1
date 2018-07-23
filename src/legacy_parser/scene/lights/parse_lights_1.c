#include "rt.h"

t_bool	read_lights_type_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "type");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Number)
	{
		r->scene->lights[i]->type = (float)temp2->valuedouble;
		if (!(parse_float_number_json_vers(&r->scene->lights[i]->type, 0, 3)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_pos_single_dot(t_rt *r, cJSON *temp2, int i, char *dot)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, dot);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(dot, "x") == 0)
			r->scene->lights[i]->pos.x = (float)temp3->valuedouble;
		else if (ft_strcmp(dot, "y") == 0)
			r->scene->lights[i]->pos.y = (float)temp3->valuedouble;
		else if (ft_strcmp(dot, "z") == 0)
			r->scene->lights[i]->pos.z = (float)temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_pos_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "position");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		while (i++ < r->scene->lits_n - 1)
		{
			if (!(parse_lights_pos_single_dot(r, temp2, i, "x")))
				return (false);
			if (!(parse_lights_pos_single_dot(r, temp2, i, "y")))
				return (false);
			if (!(parse_lights_pos_single_dot(r, temp2, i, "z")))
				return (false);
			if (!(parse_vector_json_vers(&r->scene->lights[i]->pos,
					V_MIN, V_MAX)))
				return (false);
		}
		if (i != r->scene->lits_n)
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_direction_single_dot(t_rt *r, cJSON *temp2, int i, char *d)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, d);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(d, "x") == 0)
			r->scene->lights[i]->dir.x = (float)temp3->valuedouble;
		else if (ft_strcmp(d, "y") == 0)
			r->scene->lights[i]->dir.y = (float)temp3->valuedouble;
		else if (ft_strcmp(d, "z") == 0)
			r->scene->lights[i]->dir.z = (float)temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool	parse_lights_direction_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "direction");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		while (i++ < r->scene->lits_n - 1)
		{
			if (!(parse_lights_direction_single_dot(r, temp2, i, "x")))
				return (false);
			if (!(parse_lights_direction_single_dot(r, temp2, i, "y")))
				return (false);
			if (!(parse_lights_direction_single_dot(r, temp2, i, "z")))
				return (false);
			if (!(parse_vector_json_vers(&r->scene->lights[i]->dir,
					-1.0, 1.0f)))
				return (false);
		}
		if (i != r->scene->lits_n)
			return (false);
	}
	else
		return (false);
	return (true);
}

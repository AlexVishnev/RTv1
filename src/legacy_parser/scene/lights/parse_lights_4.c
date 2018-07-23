#include "rt.h"

static t_bool	parse_lights_pos_array_antinorm(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;
	cJSON	*temp2;

	elem = cJSON_GetArrayItem(temp, i);
	if (!elem)
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "position");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
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
	else
		return (false);
	return (true);
}

t_bool			parse_lights_pos_array(t_rt *r, cJSON *temp, int i)
{
	int		n;

	n = cJSON_GetArraySize(temp);
	i = 0;
	while (i < n)
	{
		if (!(parse_lights_pos_array_antinorm(r, temp, i)))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	parse_lights_position_antinorm(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "lights_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object)
	{
		if (!parse_lights_pos_single(r, temp, i))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!parse_lights_pos_array(r, temp, i))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			parse_lights_position(t_rt *r)
{
	int		i;
	char	*realname;
	cJSON	*pt;

	i = -1;
	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		if (!(parse_lights_position_antinorm(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

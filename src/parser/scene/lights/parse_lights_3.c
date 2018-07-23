#include "rt.h"

static t_bool	parse_lights_type_array_antinorm(t_rt *r, cJSON *temp, int i)
{
	cJSON	*temp2;
	cJSON	*elem;

	elem = cJSON_GetArrayItem(temp, i);
	if (!elem)
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "type");
	if (!temp2)
		return (false);
	r->scene->lights[i]->type = (float)temp2->valuedouble;
	if (temp2->type == cJSON_Number)
	{
		if (!(parse_float_number_json_vers(&r->scene->lights[i]->type,
			0, 3)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			read_lights_type_array(t_rt *r, cJSON *temp, int i)
{
	int		n;

	n = cJSON_GetArraySize(temp);
	if (r->scene->lits_n != n)
		return (false);
	while (i < n)
	{
		if (!(parse_lights_type_array_antinorm(r, temp, i)))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	parse_lights_type_antinorm(t_rt *r, cJSON *pt, int i)
{
	cJSON *temp;

	temp = cJSON_GetObjectItem(pt, "lights_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object)
	{
		if (!read_lights_type_single(r, temp, i))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!read_lights_type_array(r, temp, i))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			parse_lights_type(t_rt *r)
{
	int		i;
	char	*realname;
	cJSON	*pt;

	i = 0;
	realname = get_json_string(r->pars->av[1]);
	free(realname);
	pt = cJSON_Parse(realname);
	if (!pt)
		return (false);
	else
	{
		if (!(parse_lights_type_antinorm(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

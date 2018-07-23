#include "rt.h"

static t_bool	parse_lights_color_array_antinorm(t_rt *r, cJSON *elem, int i)
{
	cJSON	*temp2;

	if (!elem)
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "color");
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
		if (!(parse_color_json_vers(&r->scene->lights[i]->color,
			C_MIN, C_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			parse_lights_color_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;
	int		n;

	n = cJSON_GetArraySize(temp);
	i = 0;
	while (i < n)
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!(parse_lights_color_array_antinorm(r, elem, i)))
			return (false);
		i++;
	}
	if (i != r->scene->lits_n)
		return (false);
	return (true);
}

static t_bool	parse_lights_color_antinorm(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "lights_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object)
	{
		if (!(parse_lights_color_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_lights_color_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			parse_lights_color(t_rt *r)
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
		if (!(parse_lights_color_antinorm(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

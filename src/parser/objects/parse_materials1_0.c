#include "rt.h"

t_bool		parse_mats_texture(t_rt *r)
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
		if (!(parse_mats_texture_1(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

t_bool		parse_mats_offset_single_dot(t_rt *r, cJSON *temp2, int i,
				char *dot)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, dot);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(dot, "x") == 0)
			r->scene->materials[i]->texture.offset.x = temp3->valuedouble;
		else if (ft_strcmp(dot, "y") == 0)
			r->scene->materials[i]->texture.offset.y = temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_offset_array_1(t_rt *r, cJSON *elem, int i)
{
	cJSON	*temp2;

	temp2 = cJSON_GetObjectItem(elem, "offset_texture");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		if (!(parse_mats_offset_single_dot(r, temp2, i, "x")))
			return (false);
		if (!(parse_mats_offset_single_dot(r, temp2, i, "y")))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_offset_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;

	i = 0;
	while (i < cJSON_GetArraySize(temp))
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		if (!(parse_mats_offset_array_1(r, elem, i)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.offset.x, OFFSET_MIN, OFFSET_MAX)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.offset.y, OFFSET_MIN, OFFSET_MAX)))
			return (false);
		i++;
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

t_bool		parse_mats_offset_single(t_rt *r, cJSON *temp, int i)
{
	while (i++ < r->scene->mats_n - 1)
	{
		if (!(parse_mats_offset_array_1(r, temp, i)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.offset.x, OFFSET_MIN, OFFSET_MAX)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.offset.y, OFFSET_MIN, OFFSET_MAX)))
			return (false);
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

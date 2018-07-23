#include "rt.h"

t_bool		parse_mats_scale_single(t_rt *r, cJSON *temp, int i)
{
	while (i++ < r->scene->mats_n - 1)
	{
		if (!(parse_mats_scale_array_1(r, temp, i)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.scale.x, SCALE_MIN, SCALE_MAX)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.scale.y, SCALE_MIN, SCALE_MAX)))
			return (false);
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

t_bool		parse_mats_scale_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;

	i = 0;
	while (i < cJSON_GetArraySize(temp))
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		if (!(parse_mats_scale_array_1(r, elem, i)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.scale.x, SCALE_MIN, SCALE_MAX)))
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->texture.scale.y, SCALE_MIN, SCALE_MAX)))
			return (false);
		i++;
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

t_bool		parse_mats_scale_1(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "materials_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object && r->scene->mats_n == 1)
	{
		if (!(parse_mats_scale_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_scale_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_scale(t_rt *r)
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
		if (!(parse_mats_scale_1(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

t_bool		parse_materials(t_rt *r)
{
	if (!(parse_mats_color(r)))
		return (false);
	if (!(parse_mats_reflection(r)))
		return (false);
	if (!(parse_mats_transparent(r)))
		return (false);
	if (!(parse_mats_refraction(r)))
		return (false);
	if (!(parse_mats_texture(r)))
		return (false);
	if (!(parse_mats_offset(r)))
		return (false);
	if (!(parse_mats_scale(r)))
		return (false);
	return (true);
}

#include "rt.h"

t_bool		parse_mats_color(t_rt *r)
{
	int		i;
	char	*realname;
	cJSON	*pt;
	cJSON	*temp;

	i = -1;
	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		temp = cJSON_GetObjectItem(pt, "materials_obj");
		if (!temp)
			return (false);
		if (!(parse_mats_color_1(r, temp, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

t_bool		parse_mats_reflection_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	while (i++ < r->scene->mats_n - 1)
	{
		temp2 = cJSON_GetObjectItem(temp, "reflection");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->materials[i]->reflection = temp2->valuedouble;
		else
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->reflection, R_MIN, R_MAX)))
			return (false);
	}
	return (true);
}

t_bool		parse_mats_reflection_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*temp2;
	cJSON	*elem;

	i = 0;
	while (i < cJSON_GetArraySize(temp))
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		temp2 = cJSON_GetObjectItem(elem, "reflection");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->materials[i]->reflection = temp2->valuedouble;
		else
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->reflection, R_MIN, R_MAX)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_mats_reflection_1(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "materials_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object && r->scene->mats_n == 1)
	{
		if (!(parse_mats_reflection_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_reflection_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_reflection(t_rt *r)
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
		if (!(parse_mats_reflection_1(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

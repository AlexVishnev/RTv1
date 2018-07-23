#include "rt.h"

t_bool		parse_mats_transparent_single(t_rt *r, cJSON *temp, int i)
{
	cJSON *temp2;

	while (i++ < r->scene->mats_n - 1)
	{
		temp2 = cJSON_GetObjectItem(temp, "transparent");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->materials[i]->transparent = temp2->valuedouble;
		else
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->transparent, R_MIN, R_MAX)))
			return (false);
	}
	return (true);
}

t_bool		parse_mats_transparent_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*temp2;
	cJSON	*elem;
	int		n;

	n = cJSON_GetArraySize(temp);
	i = 0;
	while (i < n)
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		temp2 = cJSON_GetObjectItem(elem, "transparent");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->materials[i]->transparent = temp2->valuedouble;
		else
			return (false);
		if (!(parse_float_number_json_vers(
			&r->scene->materials[i]->transparent, R_MIN, R_MAX)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_mats_transparent_1(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "materials_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object && r->scene->mats_n == 1)
	{
		if (!(parse_mats_transparent_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_transparent_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

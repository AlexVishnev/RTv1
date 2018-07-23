#include "rt.h"

t_bool		parse_mats_offset_1(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "materials_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object && r->scene->mats_n == 1)
	{
		if (!(parse_mats_offset_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_offset_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_offset(t_rt *r)
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
		if (!(parse_mats_offset_1(r, pt, i)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

t_bool		parse_mats_scale_single_dot(t_rt *r, cJSON *temp2, int i, char *dot)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, dot);
	if (!temp3)
		return (false);
	if (temp3->type == cJSON_Number)
	{
		if (ft_strcmp(dot, "x") == 0)
			r->scene->materials[i]->texture.scale.x = temp3->valuedouble;
		else if (ft_strcmp(dot, "y") == 0)
			r->scene->materials[i]->texture.scale.y = temp3->valuedouble;
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_scale_array_1(t_rt *r, cJSON *elem, int i)
{
	cJSON	*temp2;

	temp2 = cJSON_GetObjectItem(elem, "scale_texture");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		if (!(parse_mats_scale_single_dot(r, temp2, i, "x")))
			return (false);
		if (!(parse_mats_scale_single_dot(r, temp2, i, "y")))
			return (false);
	}
	else
		return (false);
	return (true);
}

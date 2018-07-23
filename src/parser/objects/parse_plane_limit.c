#include "rt.h"

t_bool		parse_plane_valid_all(cJSON *elem)
{
	if (!(parse_plane_l_validation_single(elem, "position")))
		return (false);
	if (!(parse_plane_l_validation_single(elem, "angle")))
		return (false);
	if (!(parse_plane_validation_value(elem, "height")))
		return (false);
	if (!(parse_plane_validation_value(elem, "width")))
		return (false);
	if (!(parse_plane_validation_value(elem, "material")))
		return (false);
	return (true);
}

t_bool		parse_plane_limit_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	float		hwm[3];
	Uint16		mat;
	cJSON		*temp2;

	alloc_new_plane_limit(rt, i);
	if (!(parse_plane_valid_all(temp)))
		return (false);
	pr[0] = parse_plane_l_single_pos(temp);
	pr[1] = parse_plane_l_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "height");
	hwm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "width");
	hwm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	hwm[2] = temp2->valuedouble;
	if (!(parse_plane_l_fin_valid(pr[0], pr[1], hwm[0], hwm[1])))
		return (false);
	if (!(valid_material(rt, hwm[2], M_MIN, M_MAX)))
		return (false);
	set_plane_limit(rt->scene->objects[i], pr, hwm, mat);
	return (true);
}

t_bool		parse_plane_limit_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	float		hwm[3];
	Uint16		mat;
	cJSON		*temp2;

	if (!(parse_plane_valid_all(elem)))
		return (false);
	pr[0] = parse_plane_l_single_pos(elem);
	pr[1] = parse_plane_l_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "height");
	hwm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "width");
	hwm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	hwm[2] = temp2->valuedouble;
	if (!(parse_plane_l_fin_valid(pr[0], pr[1], hwm[0], hwm[1])))
		return (false);
	if (!(valid_material(rt, hwm[2], M_MIN, M_MAX)))
		return (false);
	set_plane_limit(rt->scene->objects[i], pr, hwm, mat);
	return (true);
}

t_bool		parse_plane_limit_array(t_rt *rt, int i, cJSON *temp, int j)
{
	cJSON		*elem;

	while (++j < cJSON_GetArraySize(temp))
	{
		alloc_new_plane_limit(rt, i);
		elem = cJSON_GetArrayItem(temp, j);
		if (!elem)
			return (false);
		if (!(parse_plane_limit_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_plane_limit(t_rt *rt, int i, cJSON *temp)
{
	int	j;

	j = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_plane_limit_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_plane_limit_array(rt, i, temp, j)))
			return (false);
	}
	else
		return (false);
	return (true);
}

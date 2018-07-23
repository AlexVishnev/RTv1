#include "rt.h"

t_bool		parse_cone_fin_valid(t_vec3 pos, t_vec3 rot, float angle)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&angle, A_MIN, A_MAX)))
		return (false);
	return (true);
}

t_bool		parse_cone_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	Uint16		mat;
	float		am[2];
	cJSON		*temp2;

	alloc_new_cone(rt, i);
	if (!(parse_cone_valid_all(temp)))
		return (false);
	pr[0] = parse_cone_single_pos(temp);
	pr[1] = parse_cone_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "angle");
	am[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	am[1] = temp2->valuedouble;
	if (!(parse_cone_fin_valid(pr[0], pr[1], am[0])))
		return (false);
	if (!(valid_material(rt, am[1], M_MIN, M_MAX)))
		return (false);
	set_cone(rt->scene->objects[i], pr, am[0], mat);
	return (true);
}

t_bool		parse_cone_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	Uint16		mat;
	float		am[2];
	cJSON		*temp2;

	if (!(parse_cone_valid_all(elem)))
		return (false);
	pr[0] = parse_cone_single_pos(elem);
	pr[1] = parse_cone_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "angle");
	am[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	am[1] = temp2->valuedouble;
	if (!(parse_cone_fin_valid(pr[0], pr[1], am[0])))
		return (false);
	if (!(valid_material(rt, am[1], M_MIN, M_MAX)))
		return (false);
	set_cone(rt->scene->objects[i], pr, am[0], mat);
	return (true);
}

t_bool		parse_cone_array(t_rt *rt, int i, cJSON *temp, int k)
{
	cJSON *elem;

	while (++k < cJSON_GetArraySize(temp))
	{
		alloc_new_cone(rt, i);
		elem = cJSON_GetArrayItem(temp, k);
		if (!elem)
			return (false);
		if (!(parse_cone_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_cone(t_rt *rt, int i, cJSON *temp)
{
	int k;

	k = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_cone_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_cone_array(rt, i, temp, k)))
			return (false);
	}
	else
		return (false);
	return (true);
}

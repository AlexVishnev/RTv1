#include "rt.h"

t_bool		parse_parab_fin_valid(t_vec3 pos, t_vec3 rot, float a)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&a, V_MIN, V_MAX)))
		return (false);
	return (true);
}

t_bool		parse_paraboloid_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	float		am[2];
	Uint16		mat;
	cJSON		*temp2;

	alloc_new_paraboloid(rt, i);
	if (!(parse_parab_valid_all(temp)))
		return (false);
	pr[0] = parse_parab_single_pos(temp);
	pr[1] = parse_parab_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "a");
	am[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	am[1] = temp2->valuedouble;
	if (!(parse_parab_fin_valid(pr[0], pr[1], am[0])))
		return (false);
	if (!(valid_material(rt, am[1], M_MIN, M_MAX)))
		return (false);
	set_paraboloid(rt->scene->objects[i], pr, am[0], mat);
	return (true);
}

t_bool		parse_parab_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	float		am[2];
	Uint16		mat;
	cJSON		*temp2;

	if (!(parse_parab_valid_all(elem)))
		return (false);
	pr[0] = parse_parab_single_pos(elem);
	pr[1] = parse_parab_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "a");
	am[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	am[1] = temp2->valuedouble;
	if (!(parse_parab_fin_valid(pr[0], pr[1], am[0])))
		return (false);
	if (!(valid_material(rt, am[1], M_MIN, M_MAX)))
		return (false);
	set_paraboloid(rt->scene->objects[i], pr, am[0], mat);
	return (true);
}

t_bool		parse_paraboloid_array(t_rt *rt, int i, cJSON *temp, int j)
{
	cJSON		*elem;

	while (++j < cJSON_GetArraySize(temp))
	{
		alloc_new_paraboloid(rt, i);
		elem = cJSON_GetArrayItem(temp, j);
		if (!elem)
			return (false);
		if (!(parse_parab_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_paraboloid(t_rt *rt, int i, cJSON *temp)
{
	int	j;

	j = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_paraboloid_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_paraboloid_array(rt, i, temp, j)))
			return (false);
	}
	else
		return (false);
	return (true);
}

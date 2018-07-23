#include "rt.h"

t_bool		parse_disc_fin_valid(t_vec3 pos, t_vec3 rot, float r1, float r)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&r1, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&r, V_MIN, V_MAX)))
		return (false);
	return (true);
}

t_bool		parse_disc_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	float		r1rm[3];
	Uint16		mat;
	cJSON		*temp2;

	alloc_new_disc(rt, i);
	if (!(parse_disc_valid_all(temp)))
		return (false);
	pr[0] = parse_disc_single_pos(temp);
	pr[1] = parse_disc_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "large_radius");
	r1rm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "small_radius");
	r1rm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	r1rm[2] = temp2->valuedouble;
	if (!(parse_disc_fin_valid(pr[0], pr[1], r1rm[0], r1rm[1])))
		return (false);
	if (!(valid_material(rt, r1rm[2], M_MIN, M_MAX)))
		return (false);
	set_disc(rt->scene->objects[i], pr, r1rm, mat);
	return (true);
}

t_bool		parse_disc_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	float		r1rm[3];
	Uint16		mat;
	cJSON		*temp2;

	if (!(parse_disc_valid_all(elem)))
		return (false);
	pr[0] = parse_disc_single_pos(elem);
	pr[1] = parse_disc_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "large_radius");
	r1rm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "small_radius");
	r1rm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	r1rm[2] = temp2->valuedouble;
	if (!(parse_disc_fin_valid(pr[0], pr[1], r1rm[0], r1rm[1])))
		return (false);
	if (!(valid_material(rt, r1rm[2], M_MIN, M_MAX)))
		return (false);
	set_disc(rt->scene->objects[i], pr, r1rm, mat);
	return (true);
}

t_bool		parse_disc_array(t_rt *rt, int i, cJSON *temp, int j)
{
	cJSON		*elem;

	while (++j < cJSON_GetArraySize(temp))
	{
		alloc_new_disc(rt, i);
		elem = cJSON_GetArrayItem(temp, j);
		if (!elem)
			return (false);
		if (!(parse_disc_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_disc(t_rt *rt, int i, cJSON *temp)
{
	int j;

	j = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_disc_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_disc_array(rt, i, temp, j)))
			return (false);
	}
	else
		return (false);
	return (true);
}

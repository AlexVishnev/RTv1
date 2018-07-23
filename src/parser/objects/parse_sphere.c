#include "rt.h"

t_bool		parse_sphere_fin_valid(t_rt *rt, t_vec3 pos, float rad, float mat)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_number_json_vers(&rad, V_MIN, V_MAX)))
		return (false);
	if (!(valid_material(rt, mat, M_MIN, M_MAX)))
		return (false);
	return (true);
}

t_bool		parse_sphere_single(t_rt *rt, int i, cJSON *temp)
{
	cJSON		*temp2;
	t_vec3		pos;
	float		rad;
	Uint16		mat;
	float		material;

	alloc_new_sphere(rt, i);
	if (!(parse_sphere_validation_single(temp, "position")))
		return (false);
	pos = parse_sphere_single_pos(temp);
	if (!(parse_sphere_validation_value(temp, "radius")))
		return (false);
	temp2 = cJSON_GetObjectItem(temp, "radius");
	rad = temp2->valuedouble;
	if (!(parse_sphere_validation_value(temp, "material")))
		return (false);
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_sphere_fin_valid(rt, pos, rad, material)))
		return (false);
	set_sphere(rt->scene->objects[i], pos, rad, mat);
	return (true);
}

t_bool		parse_sphere_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pos;
	float		rad;
	Uint16		mat;
	float		material;
	cJSON		*temp2;

	if (!(parse_sphere_validation_single(elem, "position")))
		return (false);
	pos = parse_sphere_single_pos(elem);
	if (!(parse_sphere_validation_value(elem, "radius")))
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "radius");
	rad = temp2->valuedouble;
	if (!(parse_sphere_validation_value(elem, "material")))
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_sphere_fin_valid(rt, pos, rad, material)))
		return (false);
	set_sphere(rt->scene->objects[i], pos, rad, mat);
	return (true);
}

t_bool		parse_sphere_array(t_rt *rt, int i, cJSON *temp, int k)
{
	cJSON		*elem;

	while (++k < cJSON_GetArraySize(temp))
	{
		alloc_new_sphere(rt, i);
		elem = cJSON_GetArrayItem(temp, k);
		if (!elem)
			return (false);
		if (!(parse_sphere_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_sphere(t_rt *rt, int i, cJSON *temp)
{
	int k;

	k = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_sphere_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_sphere_array(rt, i, temp, k)))
			return (false);
	}
	else
		return (false);
	return (true);
}

#include "rt.h"

t_bool		parse_cyl_fin_valid(t_vec3 pos, t_vec3 rot, float rad)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(parse_number_json_vers(&rad, V_MIN, V_MAX)))
		return (false);
	return (true);
}

t_bool		parse_cylinder_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	float		rm[2];
	Uint16		mat;
	cJSON		*temp2;

	alloc_new_cylinder(rt, i);
	if (!(parse_cyl_valid_all(temp)))
		return (false);
	pr[0] = parse_cyl_single_pos(temp);
	pr[1] = parse_cyl_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "radius");
	rm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	rm[1] = temp2->valuedouble;
	if (!(parse_cyl_fin_valid(pr[0], pr[1], rm[0])))
		return (false);
	if (!(valid_material(rt, rm[1], M_MIN, M_MAX)))
		return (false);
	set_cylinder(rt->scene->objects[i], pr, rm[0], mat);
	return (true);
}

t_bool		parse_cylinder_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	float		rm[2];
	Uint16		mat;
	cJSON		*temp2;

	if (!(parse_cyl_valid_all(elem)))
		return (false);
	pr[0] = parse_cyl_single_pos(elem);
	pr[1] = parse_cyl_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "radius");
	rm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	rm[1] = temp2->valuedouble;
	if (!(parse_cyl_fin_valid(pr[0], pr[1], rm[0])))
		return (false);
	if (!(valid_material(rt, rm[1], M_MIN, M_MAX)))
		return (false);
	set_cylinder(rt->scene->objects[i], pr, rm[0], mat);
	return (true);
}

t_bool		parse_cylinder_array(t_rt *rt, int i, cJSON *temp, int k)
{
	cJSON	*elem;

	while (++k < cJSON_GetArraySize(temp))
	{
		alloc_new_cylinder(rt, i);
		elem = cJSON_GetArrayItem(temp, k);
		if (!elem)
			return (false);
		if (!(parse_cylinder_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_cylinder(t_rt *rt, int i, cJSON *temp)
{
	int k;

	k = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_cylinder_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_cylinder_array(rt, i, temp, k)))
			return (false);
	}
	else
		return (false);
	return (true);
}

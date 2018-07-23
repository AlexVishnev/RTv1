#include "rt.h"

t_bool		parse_triangle_fin_valid(t_vec3 a, t_vec3 b, t_vec3 c)
{
	if (!(parse_vector_json_vers(&a, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_json_vers(&b, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_json_vers(&c, V_MIN, V_MAX)))
		return (false);
	return (true);
}

t_bool		parse_triangle_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		abc[3];
	Uint16		mat;
	float		material;
	cJSON		*temp2;

	alloc_new_triangle(rt, i);
	if (!(parse_triangle_valid_all(temp)))
		return (false);
	abc[0] = parse_triangle_single_a(temp);
	abc[1] = parse_triangle_single_b(temp);
	abc[2] = parse_triangle_single_c(temp);
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_triangle_fin_valid(abc[0], abc[1], abc[2])))
		return (false);
	if (!(valid_material(rt, material, M_MIN, M_MAX)))
		return (false);
	set_triangle(rt->scene->objects[i], abc, mat);
	return (true);
}

t_bool		parse_triangle_array_cyl(t_rt *rt, int i, cJSON *elem, cJSON *temp2)
{
	t_vec3		abc[3];
	Uint16		mat;
	float		material;

	abc[0] = parse_triangle_single_a(elem);
	abc[1] = parse_triangle_single_b(elem);
	abc[2] = parse_triangle_single_c(elem);
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_triangle_fin_valid(abc[0], abc[1], abc[2])))
		return (false);
	if (!(valid_material(rt, material, M_MIN, M_MAX)))
		return (false);
	set_triangle(rt->scene->objects[i], abc, mat);
	return (true);
}

t_bool		parse_triangle_array(t_rt *rt, int i, cJSON *temp, int k)
{
	cJSON	*temp2;
	cJSON	*elem;
	int		n;

	n = cJSON_GetArraySize(temp);
	while (k < n)
	{
		alloc_new_triangle(rt, i);
		elem = cJSON_GetArrayItem(temp, k);
		if (!elem)
			return (false);
		if (!(parse_triangle_valid_all(elem)))
			return (false);
		temp2 = cJSON_GetObjectItem(elem, "material");
		if (!(parse_triangle_array_cyl(rt, i, elem, temp2)))
			return (false);
		i++;
		k++;
	}
	return (true);
}

t_bool		parse_triangle(t_rt *rt, int i, cJSON *temp)
{
	int		k;

	k = 0;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_triangle_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_triangle_array(rt, i, temp, k)))
			return (false);
	}
	else
		return (false);
	return (true);
}

#include "rt.h"

t_vec3		parse_plane_single_rot(cJSON *temp)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	rot;

	temp2 = cJSON_GetObjectItem(temp, "rotate");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	rot.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	rot.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	rot.z = temp3->valuedouble;
	return (rot);
}

t_bool		parse_plane_fin_valid(t_rt *rt, t_vec3 pos, t_vec3 rot, float mat)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(valid_material(rt, mat, M_MIN, M_MAX)))
		return (false);
	return (true);
}

t_bool		parse_plane_validation_material(cJSON *temp)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, "material");
	if (!temp2)
		return (false);
	if (temp2->type != cJSON_Number)
		return (false);
	return (true);
}

t_bool		parse_plane_single(t_rt *rt, int i, cJSON *temp)
{
	cJSON		*temp2;
	t_vec3		pos;
	t_vec3		rot;
	Uint16		mat;
	float		material;

	alloc_new_plane(rt, i);
	if (!(parse_plane_validation_single(temp, "position")))
		return (false);
	pos = parse_plane_single_pos(temp);
	if (!(parse_plane_validation_single(temp, "rotate")))
		return (false);
	rot = parse_plane_single_rot(temp);
	if (!(parse_plane_validation_material(temp)))
		return (false);
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_plane_fin_valid(rt, pos, rot, mat)))
		return (false);
	set_plane(rt->scene->objects[i], pos, rot, mat);
	return (true);
}

t_bool		parse_plane_validation_array_pos(cJSON *elem, char *str)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(elem, str);
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		if (!(parse_validation_single_dot(temp2, "x")))
			return (false);
		if (!(parse_validation_single_dot(temp2, "y")))
			return (false);
		if (!(parse_validation_single_dot(temp2, "z")))
			return (false);
	}
	else
		return (false);
	return (true);
}

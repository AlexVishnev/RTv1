#include "rt.h"

t_vec3		parse_plane_array_pos(cJSON *elem)
{
	t_vec3	pos;
	cJSON	*temp2;
	cJSON	*temp3;

	temp2 = cJSON_GetObjectItem(elem, "position");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	pos.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	pos.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	pos.z = temp3->valuedouble;
	return (pos);
}

t_vec3		parse_plane_array_rot(cJSON *elem)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	rot;

	temp2 = cJSON_GetObjectItem(elem, "rotate");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	rot.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	rot.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	rot.z = temp3->valuedouble;
	return (rot);
}

t_bool		parse_plane_array_cont(t_rt *rt, int i, cJSON *elem)
{
	cJSON		*temp2;
	t_vec3		pos;
	t_vec3		rot;
	Uint16		mat;
	float		material;

	if (!(parse_plane_validation_array_pos(elem, "position")))
		return (false);
	pos = parse_plane_array_pos(elem);
	if (!(parse_plane_validation_array_pos(elem, "rotate")))
		return (false);
	rot = parse_plane_single_rot(elem);
	if (!(parse_plane_validation_material(elem)))
		return (false);
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	material = temp2->valuedouble;
	if (!(parse_plane_fin_valid(rt, pos, rot, mat)))
		return (false);
	set_plane(rt->scene->objects[i], pos, rot, mat);
	return (true);
}

t_bool		parse_plane_array(t_rt *rt, int i, cJSON *temp, int j)
{
	cJSON		*elem;

	while (++j < cJSON_GetArraySize(temp))
	{
		alloc_new_plane(rt, j);
		elem = cJSON_GetArrayItem(temp, j);
		if (!elem)
			return (false);
		if (!(parse_plane_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_plane(t_rt *rt, int i, cJSON *temp)
{
	int j;

	j = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_plane_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_plane_array(rt, i, temp, j)))
			return (false);
	}
	else
		return (false);
	return (true);
}

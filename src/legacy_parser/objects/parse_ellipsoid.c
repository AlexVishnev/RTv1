#include "rt.h"

t_bool		parse_ellipsoid_single(t_rt *rt, int i, cJSON *temp)
{
	t_vec3		pr[2];
	float		krm[3];
	Uint16		mat;
	cJSON		*temp2;

	alloc_new_ellipsoid(rt, i);
	if (!(parse_ellip_valid_all(temp)))
		return (false);
	pr[0] = parse_ellip_single_pos(temp);
	pr[1] = parse_ellip_single_rot(temp);
	temp2 = cJSON_GetObjectItem(temp, "k");
	krm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "radius");
	krm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(temp, "material");
	mat = (Uint16)temp2->valuedouble;
	krm[2] = temp2->valuedouble;
	if (!(parse_ellip_fin_valid(pr[0], pr[1], krm[0], krm[1])))
		return (false);
	if (!(valid_material(rt, krm[2], M_MIN, M_MAX)))
		return (false);
	set_ellipsoid(rt->scene->objects[i], pr, krm, mat);
	return (true);
}

t_bool		parse_ellipsoid_array_cont(t_rt *rt, int i, cJSON *elem)
{
	t_vec3		pr[2];
	float		krm[3];
	Uint16		mat;
	cJSON		*temp2;

	if (!(parse_ellip_valid_all(elem)))
		return (false);
	pr[0] = parse_ellip_single_pos(elem);
	pr[1] = parse_ellip_single_rot(elem);
	temp2 = cJSON_GetObjectItem(elem, "k");
	krm[0] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "radius");
	krm[1] = temp2->valuedouble;
	temp2 = cJSON_GetObjectItem(elem, "material");
	mat = (Uint16)temp2->valuedouble;
	krm[2] = temp2->valuedouble;
	if (!(parse_ellip_fin_valid(pr[0], pr[1], krm[0], krm[1])))
		return (false);
	if (!(valid_material(rt, krm[2], M_MIN, M_MAX)))
		return (false);
	set_ellipsoid(rt->scene->objects[i], pr, krm, mat);
	return (true);
}

t_bool		parse_ellipsoid_array(t_rt *rt, int i, cJSON *temp, int j)
{
	cJSON		*elem;

	while (++j < cJSON_GetArraySize(temp))
	{
		alloc_new_ellipsoid(rt, i);
		elem = cJSON_GetArrayItem(temp, j);
		if (!elem)
			return (false);
		if (!(parse_ellipsoid_array_cont(rt, i, elem)))
			return (false);
		i++;
	}
	return (true);
}

t_bool		parse_ellipsoid(t_rt *rt, int i, cJSON *temp)
{
	int j;

	j = -1;
	if (temp->type == cJSON_Object)
	{
		if (!(parse_ellipsoid_single(rt, i, temp)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_ellipsoid_array(rt, i, temp, j)))
			return (false);
	}
	else
		return (false);
	return (true);
}

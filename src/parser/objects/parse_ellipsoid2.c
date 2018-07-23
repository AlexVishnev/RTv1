#include "rt.h"

void		alloc_new_ellipsoid(t_rt *rt, int i)
{
	rt->scene->objects[i] = new_object(ellipsoid);
	rt->scene->objects[i]->type = new_ellipsoid();
	rt->scene->objects[i]->intersect = intersect_ellipsoid;
	rt->scene->objects[i]->normal = normal_ellipsoid;
}

t_vec3		parse_ellip_single_pos(cJSON *temp)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	pos;

	temp2 = cJSON_GetObjectItem(temp, "position");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	pos.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	pos.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	pos.z = temp3->valuedouble;
	return (pos);
}

t_vec3		parse_ellip_single_rot(cJSON *temp)
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

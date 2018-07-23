#include "rt.h"

void		alloc_new_triangle(t_rt *rt, int i)
{
	rt->scene->objects[i] = new_object(triangle);
	rt->scene->objects[i]->type = new_triangle();
	rt->scene->objects[i]->intersect = intersect_triangle;
	rt->scene->objects[i]->normal = normal_triangle;
}

t_bool		parse_triangle_valid_value(cJSON *temp, char *str)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, str);
	if (!temp2)
		return (false);
	if (temp2->type != cJSON_Number)
		return (false);
	return (true);
}

t_bool		parse_validation_single_dot(cJSON *temp2, char *str)
{
	cJSON *temp3;

	temp3 = cJSON_GetObjectItem(temp2, str);
	if (!temp3)
		return (false);
	if (temp3->type != cJSON_Number)
		return (false);
	return (true);
}

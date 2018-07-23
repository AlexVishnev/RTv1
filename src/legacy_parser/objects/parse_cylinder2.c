#include "rt.h"

void		alloc_new_cylinder(t_rt *rt, int i)
{
	rt->scene->objects[i] = new_object(cylinder);
	rt->scene->objects[i]->type = new_cylinder();
	rt->scene->objects[i]->intersect = intersect_cylinder;
	rt->scene->objects[i]->normal = normal_cylinder;
}

t_bool		parse_cyl_validation_single(cJSON *temp, char *str)
{
	cJSON	*temp2;

	temp2 = cJSON_GetObjectItem(temp, str);
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

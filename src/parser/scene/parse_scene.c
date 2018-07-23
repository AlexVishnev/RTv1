#include "rt.h"

t_bool	get_obj_info(t_rt *r, cJSON *pt, char *name)
{
	float	n;
	cJSON	*temp;

	n = 0;
	temp = cJSON_GetObjectItem(pt, name);
	if (!temp)
		return (false);
	if (temp->type == cJSON_Number)
		n = temp->valueint;
	else
		return (false);
	if (n < S_MIN || n > S_MAX)
		return (false);
	if (ft_strcmp(name, "lights") == 0)
		r->scene->lits_n = (Uint8)n;
	else if (ft_strcmp(name, "materials") == 0)
		r->scene->mats_n = (Uint8)n;
	else if (ft_strcmp(name, "objects") == 0)
		r->scene->objs_n = (Uint8)n;
	return (true);
}

t_bool	parse_scene_objects(t_rt *r, cJSON *pt)
{
	if (!(get_obj_info(r, pt, "lights")))
		return (false);
	if (!(get_obj_info(r, pt, "materials")))
		return (false);
	if (!(get_obj_info(r, pt, "objects")))
		return (false);
	cJSON_Delete(pt);
	return (true);
}

t_bool	parse_scene(t_rt *r)
{
	cJSON	*pt;
	char	*realname;

	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		if (!(parse_scene_objects(r, pt)))
			return (false);
	}
	return (true);
}

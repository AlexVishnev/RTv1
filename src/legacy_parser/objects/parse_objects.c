#include "rt.h"

int			get_disc(t_rt *r, int i, cJSON *pt)
{
	cJSON	*temp;
	int		n;

	temp = cJSON_GetObjectItem(pt, "disc");
	if (!(parse_disc(r, i, temp)))
		return (-1);
	if (temp->type == cJSON_Object)
		i++;
	else if (temp->type == cJSON_Array)
	{
		n = cJSON_GetArraySize(temp);
		i += n;
	}
	return (i);
}

int			get_triangle(t_rt *r, int i, cJSON *pt)
{
	cJSON	*temp;
	int		n;

	temp = cJSON_GetObjectItem(pt, "triangle");
	if (!(parse_triangle(r, i, temp)))
		return (-1);
	if (temp->type == cJSON_Object)
		i++;
	else if (temp->type == cJSON_Array)
	{
		n = cJSON_GetArraySize(temp);
		i += n;
	}
	return (i);
}

t_bool		choose_objects(t_rt *r, int i, cJSON *pt)
{
	if (cJSON_GetObjectItem(pt, "plane"))
		i = get_plane(r, i, pt);
	if (cJSON_GetObjectItem(pt, "plane_limit") && i != -1)
		i = get_plane_limit(r, i, pt);
	if (cJSON_GetObjectItem(pt, "sphere") && i != -1)
		i = get_sphere(r, i, pt);
	if (cJSON_GetObjectItem(pt, "cylinder") && i != -1)
		i = get_cylinder(r, i, pt);
	if (cJSON_GetObjectItem(pt, "cone") && i != -1)
		i = get_cone(r, i, pt);
	if (cJSON_GetObjectItem(pt, "ellipsoid") && i != -1)
		i = get_ellipsoid(r, i, pt);
	if (cJSON_GetObjectItem(pt, "paraboloid") && i != -1)
		i = get_paraboloid(r, i, pt);
	if (cJSON_GetObjectItem(pt, "torus") && i != -1)
		i = get_torus(r, i, pt);
	if (cJSON_GetObjectItem(pt, "disc") && i != -1)
		i = get_disc(r, i, pt);
	if (cJSON_GetObjectItem(pt, "triangle") && i != -1)
		i = get_triangle(r, i, pt);
	if (i != r->scene->objs_n || i == -1)
		return (false);
	return (true);
}

t_bool		choose(t_rt *r, int i)
{
	char	*realname;
	cJSON	*pt;

	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		if (!(choose_objects(r, i, pt)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

t_bool		parse_objects(t_rt *r)
{
	int i;

	i = 0;
	if (!(choose(r, i)))
		return (false);
	return (true);
}

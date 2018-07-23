#include "rt.h"

int			get_plane(t_rt *r, int i, cJSON *pt)
{
	cJSON	*temp;
	int		n;

	temp = cJSON_GetObjectItem(pt, "plane");
	if (!(parse_plane(r, i, temp)))
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

int			get_plane_limit(t_rt *r, int i, cJSON *pt)
{
	cJSON	*temp;
	int		n;

	temp = cJSON_GetObjectItem(pt, "plane_limit");
	if (!(parse_plane_limit(r, i, temp)))
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

int			get_sphere(t_rt *r, int i, cJSON *pt)
{
	cJSON	*temp;
	int		n;

	temp = cJSON_GetObjectItem(pt, "sphere");
	if (!(parse_sphere(r, i, temp)))
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

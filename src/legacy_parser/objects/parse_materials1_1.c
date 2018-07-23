#include "rt.h"

t_bool		parse_mats_texture_11(t_rt *r, cJSON *elem, int i)
{
	cJSON	*temp2;

	temp2 = cJSON_GetObjectItem(elem, "texture");
	if (!temp2)
		return (false);
	if (temp2->type == cJSON_String)
	{
		if (ft_strcmp(temp2->valuestring, "null") != 0)
		{
			r->scene->materials[i]->texture.status = true;
			r->scene->materials[i]->texture.map =
				IMG_Load(temp2->valuestring);
			if (!r->scene->materials[i]->texture.map ||
				r->scene->materials[i]->texture.map->w < T_MIN ||
				r->scene->materials[i]->texture.map->h < T_MIN ||
				r->scene->materials[i]->texture.map->w > T_MAX ||
				r->scene->materials[i]->texture.map->h > T_MAX)
				return (false);
		}
		else
			r->scene->materials[i]->texture.status = false;
	}
	else
		return (false);
	return (true);
}

t_bool		parse_mats_texture_array(t_rt *r, cJSON *temp, int i)
{
	cJSON	*elem;

	i = -1;
	while (++i < cJSON_GetArraySize(temp))
	{
		elem = cJSON_GetArrayItem(temp, i);
		if (!elem)
			return (false);
		if (!(parse_mats_texture_11(r, elem, i)))
			return (false);
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

t_bool		parse_mats_texture_single(t_rt *r, cJSON *temp, int i)
{
	while (i++ < r->scene->mats_n - 1)
	{
		if (!(parse_mats_texture_11(r, temp, i)))
			return (false);
	}
	if (i != r->scene->mats_n)
		return (false);
	return (true);
}

t_bool		parse_mats_texture_1(t_rt *r, cJSON *pt, int i)
{
	cJSON	*temp;

	temp = cJSON_GetObjectItem(pt, "materials_obj");
	if (!temp)
		return (false);
	if (temp->type == cJSON_Object && r->scene->mats_n == 1)
	{
		if (!(parse_mats_texture_single(r, temp, i)))
			return (false);
	}
	else if (temp->type == cJSON_Array)
	{
		if (!(parse_mats_texture_array(r, temp, i)))
			return (false);
	}
	else
		return (false);
	return (true);
}

#include "rt.h"

t_bool		parse_render_info_glossy(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "show_glossy");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_String)
		{
			if (ft_strcmp(temp2->valuestring, "true") == 0)
				r->scene->status_glossy = true;
			else if (ft_strcmp(temp2->valuestring, "false") == 0)
				r->scene->status_glossy = false;
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_render_info_shadow(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "show_shadow");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_String)
		{
			if (ft_strcmp(temp2->valuestring, "true") == 0)
				r->scene->status_shadow = true;
			else if (ft_strcmp(temp2->valuestring, "false") == 0)
				r->scene->status_shadow = false;
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_render_info_texture(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "show_texture");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_String)
		{
			if (ft_strcmp(temp2->valuestring, "true") == 0)
				r->scene->status_texture = true;
			else if (ft_strcmp(temp2->valuestring, "false") == 0)
				r->scene->status_texture = false;
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_render_info_lvl_refr(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "level_refraction");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->max_level_transparent = temp2->valueint;
		else
			return (false);
		if (!(parse_int_number_json_vers(&r->scene->max_level_transparent,
				RE_MIN, RE_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_render_info_lvl_refl(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "level_reflection");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->max_level_reflection = temp2->valueint;
		else
			return (false);
		if (!(parse_int_number_json_vers(&r->scene->max_level_reflection,
				RE_MIN, RE_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

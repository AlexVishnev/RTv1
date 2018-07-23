#include "rt.h"

t_bool			parse_render_info_aa(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "aa");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->aa = temp2->valueint;
		else
			return (false);
		if (!(parse_int_number_json_vers(&r->scene->aa, AA_MIN, AA_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool			parse_render_info_typecol(t_rt *r, cJSON *temp)
{
	cJSON	*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "type_color");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->status_color = temp2->valueint;
		else
			return (false);
		if (!(parse_int_number_json_vers(&r->scene->status_color,
				COLOR_MIN, COLOR_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

static t_bool	parse_render_info(t_rt *r, cJSON *temp)
{
	if (!(parse_render_info_aa(r, temp)))
		return (false);
	if (!(parse_render_info_typecol(r, temp)))
		return (false);
	if (!(parse_render_info_lvl_refl(r, temp)))
		return (false);
	if (!(parse_render_info_lvl_refr(r, temp)))
		return (false);
	if (!(parse_render_info_texture(r, temp)))
		return (false);
	if (!(parse_render_info_shadow(r, temp)))
		return (false);
	if (!(parse_render_info_glossy(r, temp)))
		return (false);
	return (true);
}

t_bool			parse_render(t_rt *r)
{
	cJSON	*pt;
	cJSON	*temp;
	char	*realname;

	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		temp = cJSON_GetObjectItem(pt, "render");
		if (!temp)
			return (false);
		if (!(parse_render_info(r, temp)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

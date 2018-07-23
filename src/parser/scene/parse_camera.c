#include "rt.h"

t_bool		parse_camera_position(t_rt *r, cJSON *temp2)
{
	cJSON		*temp3;

	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		temp3 = cJSON_GetObjectItem(temp2, "x");
		if (temp3->type == cJSON_Number)
			r->scene->cam.pos.x = temp3->valueint;
		temp3 = cJSON_GetObjectItem(temp2, "y");
		if (temp3->type == cJSON_Number)
			r->scene->cam.pos.y = temp3->valueint;
		temp3 = cJSON_GetObjectItem(temp2, "z");
		if (temp3->type == cJSON_Number)
			r->scene->cam.pos.z = temp3->valueint;
		if (!(parse_vector_json_vers(&r->scene->cam.pos, V_MIN, V_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_camera_direction(t_rt *r, cJSON *temp2)
{
	cJSON		*temp3;

	if (!temp2)
		return (false);
	if (temp2->type == cJSON_Object)
	{
		temp3 = cJSON_GetObjectItem(temp2, "x");
		if (temp3->type == cJSON_Number)
			r->scene->cam.eye.x = temp3->valueint;
		temp3 = cJSON_GetObjectItem(temp2, "y");
		if (temp3->type == cJSON_Number)
			r->scene->cam.eye.y = temp3->valueint;
		temp3 = cJSON_GetObjectItem(temp2, "z");
		if (temp3->type == cJSON_Number)
			r->scene->cam.eye.z = temp3->valueint;
		if (!(parse_vector_json_vers(&r->scene->cam.eye, V_MIN, V_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_camera_info(t_rt *r, cJSON *temp)
{
	cJSON		*temp2;

	if (temp->type == cJSON_Object)
	{
		temp2 = cJSON_GetObjectItem(temp, "camera_position");
		if (!(parse_camera_position(r, temp2)))
			return (false);
		temp2 = cJSON_GetObjectItem(temp, "camera_direction");
		if (!(parse_camera_direction(r, temp2)))
			return (false);
		temp2 = cJSON_GetObjectItem(temp, "fov");
		if (!temp2)
			return (false);
		if (temp2->type == cJSON_Number)
			r->scene->cam.p.fov = temp2->valueint;
		else
			return (false);
		if (!(parse_number_json_vers(&r->scene->cam.p.fov, F_MIN, F_MAX)))
			return (false);
	}
	else
		return (false);
	return (true);
}

t_bool		parse_camera(t_rt *r)
{
	cJSON		*pt;
	cJSON		*temp;
	char		*realname;

	realname = get_json_string(r->pars->av[1]);
	pt = cJSON_Parse(realname);
	free(realname);
	if (!pt)
		return (false);
	else
	{
		temp = cJSON_GetObjectItem(pt, "camera");
		if (!temp)
			return (false);
		if (!(parse_camera_info(r, temp)))
			return (false);
	}
	cJSON_Delete(pt);
	return (true);
}

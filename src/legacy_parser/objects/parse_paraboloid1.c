#include "rt.h"

t_vec3		parse_parab_single_rot(cJSON *temp)
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

t_bool		parse_parab_validation_single(cJSON *temp, char *str)
{
	cJSON *temp2;

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

t_bool		parse_parab_validation_value(cJSON *temp, char *str)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, str);
	if (!temp2)
		return (false);
	if (temp2->type != cJSON_Number)
		return (false);
	return (true);
}

t_bool		parse_parab_valid_all(cJSON *temp)
{
	if (!(parse_parab_validation_single(temp, "position")))
		return (false);
	if (!(parse_parab_validation_single(temp, "rotate")))
		return (false);
	if (!(parse_parab_validation_value(temp, "a")))
		return (false);
	if (!(parse_parab_validation_value(temp, "material")))
		return (false);
	return (true);
}

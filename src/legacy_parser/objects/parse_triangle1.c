#include "rt.h"

t_bool		parse_triangle_valid_single(cJSON *temp, char *str)
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

t_bool		parse_triangle_valid_all(cJSON *temp)
{
	if (!(parse_triangle_valid_single(temp, "position A")))
		return (false);
	if (!(parse_triangle_valid_single(temp, "position B")))
		return (false);
	if (!(parse_triangle_valid_single(temp, "position C")))
		return (false);
	if (!(parse_triangle_valid_value(temp, "material")))
		return (false);
	return (true);
}

t_vec3		parse_triangle_single_a(cJSON *temp)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	a;

	temp2 = cJSON_GetObjectItem(temp, "position A");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	a.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	a.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	a.z = temp3->valuedouble;
	return (a);
}

t_vec3		parse_triangle_single_b(cJSON *temp)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	b;

	temp2 = cJSON_GetObjectItem(temp, "position B");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	b.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	b.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	b.z = temp3->valuedouble;
	return (b);
}

t_vec3		parse_triangle_single_c(cJSON *temp)
{
	cJSON	*temp2;
	cJSON	*temp3;
	t_vec3	c;

	temp2 = cJSON_GetObjectItem(temp, "position C");
	temp3 = cJSON_GetObjectItem(temp2, "x");
	c.x = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "y");
	c.y = temp3->valuedouble;
	temp3 = cJSON_GetObjectItem(temp2, "z");
	c.z = temp3->valuedouble;
	return (c);
}

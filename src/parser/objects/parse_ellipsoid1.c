#include "rt.h"

t_bool		parse_ellip_validation_single(cJSON *temp, char *str)
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

t_bool		parse_ellip_validation_value(cJSON *temp, char *str)
{
	cJSON *temp2;

	temp2 = cJSON_GetObjectItem(temp, str);
	if (!temp2)
		return (false);
	if (temp2->type != cJSON_Number)
		return (false);
	return (true);
}

t_bool		parse_ellip_valid_all(cJSON *temp)
{
	if (!(parse_ellip_validation_single(temp, "position")))
		return (false);
	if (!(parse_ellip_validation_single(temp, "rotate")))
		return (false);
	if (!(parse_ellip_validation_value(temp, "k")))
		return (false);
	if (!(parse_ellip_validation_value(temp, "radius")))
		return (false);
	if (!(parse_ellip_validation_value(temp, "material")))
		return (false);
	return (true);
}

t_bool		parse_ellip_fin_valid(t_vec3 pos, t_vec3 rot, float k, float rad)
{
	if (!(parse_vector_json_vers(&pos, V_MIN, V_MAX)))
		return (false);
	if (!(parse_vector_float_json_vers(&rot, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&k, V_MIN, V_MAX)))
		return (false);
	if (!(parse_float_number_json_vers(&rad, V_MIN, V_MAX)))
		return (false);
	return (true);
}

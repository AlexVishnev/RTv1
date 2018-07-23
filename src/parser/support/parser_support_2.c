#include "rt.h"

t_bool	parse_number_json_vers(float *n, int min, int max)
{
	if (*n >= min && *n <= max)
		return (true);
	return (false);
}

t_bool	parse_vector_json_vers(t_vec3 *v, int min, int max)
{
	if (!(parse_number_json_vers(&v->x, min, max)))
		return (false);
	if (!(parse_number_json_vers(&v->y, min, max)))
		return (false);
	if (!(parse_number_json_vers(&v->z, min, max)))
		return (false);
	return (true);
}

t_bool	parse_float_number_json_vers(float *n, float min, float max)
{
	if (*n >= min && *n <= max)
		return (true);
	return (false);
}

t_bool	parse_color_json_vers(t_rgbap *c, float min, float max)
{
	if (!(parse_float_number_json_vers(&c->red, min, max)))
		return (false);
	if (!(parse_float_number_json_vers(&c->green, min, max)))
		return (false);
	if (!(parse_float_number_json_vers(&c->blue, min, max)))
		return (false);
	if (!(parse_float_number_json_vers(&c->alpha, min, max)))
		return (false);
	return (true);
}

t_bool	parse_vector_float_json_vers(t_vec3 *v, float min, float max)
{
	if (!(parse_float_number_json_vers(&v->x, min, max)))
		return (false);
	if (!(parse_float_number_json_vers(&v->y, min, max)))
		return (false);
	if (!(parse_float_number_json_vers(&v->z, min, max)))
		return (false);
	return (true);
}

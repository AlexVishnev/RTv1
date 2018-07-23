#include "rt.h"

t_bool		parse_lights(t_rt *r)
{
	if (r->scene->lits_n == 0)
		return (true);
	if (!(parse_lights_type(r)))
		return (false);
	if (!(parse_lights_position(r)))
		return (false);
	if (!(parse_lights_direction(r)))
		return (false);
	if (!(parse_lights_angle(r)))
		return (false);
	if (!(parse_lights_len(r)))
		return (false);
	if (!(parse_lights_power(r)))
		return (false);
	if (!(parse_lights_color(r)))
		return (false);
	return (true);
}

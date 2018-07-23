#include "rt.h"

t_bool	parse_int_number_json_vers(int *n, int min, int max)
{
	if (*n >= min && *n <= max)
		return (true);
	return (false);
}

/*
** Parses and checks if the parsed material value is valid.
*/

t_bool	valid_material(t_rt *r, float material, int min, int max)
{
	if (!(parse_number_json_vers(&material, min, max)))
		return (false);
	if (material > r->scene->mats_n - 1)
		return (false);
	return (true);
}

t_bool	valid_texture(t_rt *r, t_texture *t, int min, int max)
{
	if (!get_str(r))
		return (false);
	if (ft_strcmp(r->pars->line, "\t\t\t\t\tnull") != 0)
	{
		t->status = true;
		t->map = IMG_Load(r->pars->line);
		free(r->pars->line);
		if (!t->map || t->map->w < min || t->map->h < min
			|| t->map->w > max || t->map->h > max)
			return (false);
	}
	else
		t->status = false;
	return (true);
}

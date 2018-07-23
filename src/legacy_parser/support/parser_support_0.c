#include "rt.h"

/*
** Closes the file, and checks for the errors.
*/

void	close_file(t_rt *r)
{
	if ((close(r->pars->fd)) < 0)
		rtv_error(file_close_error);
}

/*
** Opens the file, and checks for the errors.
*/

void	open_file(t_rt *r)
{
	r->pars->fd = open(r->pars->av[1], O_RDONLY);
	if (r->pars->fd < 0)
		rtv_error(file_open_error);
}

/*
** Checks for the GNL errors.
*/

void	gnl_error(t_rt *r, int i)
{
	if (i < 0)
	{
		close_file(r);
		rtv_error(gnl_error_code);
	}
}

/*
** Parses line by line vector values.
*/

t_bool	parse_vector(t_rt *r, t_vec3 *v, int min, int max)
{
	if (!(parse_number(r, &v->x, min, max)))
		return (false);
	if (!(parse_number(r, &v->y, min, max)))
		return (false);
	if (!(parse_number(r, &v->z, min, max)))
		return (false);
	return (true);
}

/*
** Parses line by line vector float values.
*/

t_bool	parse_vector_float(t_rt *r, t_vec3 *v, float min, float max)
{
	if (!(parse_float_number(r, &v->x, min, max)))
		return (false);
	if (!(parse_float_number(r, &v->y, min, max)))
		return (false);
	if (!(parse_float_number(r, &v->z, min, max)))
		return (false);
	return (true);
}

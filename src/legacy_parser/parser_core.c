#include "rt.h"

char	*get_json_string(char *map_name)
{
	int		fd;
	int		bytes;
	char	buff[1024];
	char	*str;
	int		file_size;

	file_size = 10000;
	str = strdup(map_name);
	if ((fd = open(str, O_RDONLY)) < 0 || (read(fd, buff, 0)) < 0)
		return (0);
	while ((bytes = read(fd, buff, 1023)))
		file_size += bytes;
	close(fd);
	fd = open(str, O_RDONLY);
	free(str);
	str = (char*)malloc(file_size + 1);
	read(fd, str, file_size);
	str[file_size] = '\0';
	close(fd);
	return (str);
}

t_bool	parser_core(t_rt *r)
{
	open_file(r);
	if (!(parse_scene(r)))
		return (false);
	create_scene(r);
	if (!(parse_render(r)))
		return (false);
	if (!(parse_camera(r)))
		return (false);
	if (!(parse_lights(r)))
		return (false);
	if (!(parse_materials(r)))
		return (false);
	if (!(parse_objects(r)))
		rtv_error(parse_error);
	close_file(r);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:15:09 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 19:21:20 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_size(char *av)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	while (ft_getline(fd, &str) > 0)
	{
		ft_memdel((void **)&str);
		i++;
	}
	ft_memdel((void **)&str);
	close(fd);
	return (i);
}

void		validate_data(char *source, t_src *src)
{
	char		*tmp;

	tmp = ft_strsub(source, 0, 6);
	if (!(ft_strcmp(tmp, "camera") || ft_strcmp(tmp, "object")
		|| ft_strcmp(tmp, "sligth")))
		error_manadge(MSG_FORMAT, 1, tmp);
	free(tmp);
	tmp = ft_strsub(source, 7, ft_strlen(source));
	if (tmp[0] != '[' || tmp[ft_strlen(tmp) - 1] != ']')
		error_manadge(MSG_FORMAT, 1, tmp);
	if ((tmp[1] != '(' && tmp[1] != '{') || (tmp[ft_strlen(tmp) - 2] != ')'
		&& tmp[ft_strlen(tmp) - 2] != '}'))
		error_manadge(MSG_FORMAT, 1, tmp);
	free(tmp);
	tmp = ft_strsub(source, 0, ft_strlen(source));
	get_data_values(tmp, src);
	free(tmp);
}

void		get_parameters(char *str, t_src *src)
{
	if (str[0] == '#' || str[0] == '\0' || str[0] == ' '
		|| str[0] == '\t' || str[0] == '\b')
		return ;
	else if (str[0] == '-' && str[1] == '>')
		validate_data(&str[2], src);
	if (str[0] != '-' && str[1] != '>')
		error_manadge(MSG_RULES, 1, str);
}



int			get_data_values(char *string, t_src *src)
{
	char		*tmp;
	int			index;

	index = -1;
	tmp = ft_strsub(string, 0, 6);
	if (ft_strcmp(tmp, "camera") == 0)
		get_camera_position(&string[7], src);
	if (ft_strcmp(tmp, "slight") == 0)
	{
		if ((src->light.nbr = ft_count_chars(string, ';') + 1) > 5)
			error_manadge("Erorr: ", 0, string);
		while (++index < src->light.nbr)
			get_spotlights_params(&string[kostyl(string, ';', index)], src, index);// это просто,блять, пиздец. я ненавижу себя за этот бред. Прости меня будущий я который эту хуету прочтет и, блять, не взудмай так больше писать
	}
//	printf("%d\n", src->objects_cnt);
	src->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * src->objects_cnt + 1); /////// leak
	if (ft_strcmp(tmp, "object") == 0)
	{
		src->objects = get_object_params(&string[7], src->objects);
		ft_putendl(string);
	}
	free(src->objects);/// for first time
	free(tmp);
	return (0);
}

void		read_from_file(char *av, t_src *src)
{
	int		fd;
	char	**params;
	int		size;

	fd = open(av, O_RDONLY);
	if (read(fd, av, 0))
	{
		close(fd);
		error_manadge(MSG_PARSE, 0, NULL);
	}
	size = get_size(av);
	params = (char **)ft_memalloc(sizeof(char *) * size + 1);
	check_nbrs_object(av, src, size);
	while (ft_getline(fd, &(*params)))
	{
		get_parameters(*params, src);
		free(*params);
		(*params)++;
	}
	free(params);
	close(fd);
}

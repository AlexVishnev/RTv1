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

int			get_size(char *av, t_src *src)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	src->index = 0;
	src->index1 = 0;
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
	if (!brackects(source))
		error_manadge(MSG_FORMAT, 1, tmp);
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
	else if (str[0] != '-' && str[1] != '>')
		error_manadge(MSG_RULES, 1, str);
}

int			get_data_values(char *string, t_src *src)
{
	char		*tmp;

	tmp = ft_strsub(string, 0, 6);
	if (ft_strcmp(tmp, "camera") == 0)
		get_camera_position(&string[7], src);
	if (ft_strcmp(tmp, "slight") == 0)
	{
		get_spotlights_params(string, src, src->index);
		src->index++;
	}
	if (ft_strcmp(tmp, "object") == 0)
	{
		if (ft_count_chars(&string[7], ',') != 6)
			error_manadge(MSG_FORMAT, 0, string);
		src->params.object[src->index1] = get_object_params(&string[7],
			&src->params.object[src->index1], src);
		src->index1++;
	}
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
		error_manadge(MSG_PARSE, 0, NULL);
	size = get_size(av, src);
	params = (char **)ft_memalloc(sizeof(char *) * size + 1);
	check_nbrs_object(av, src, size);
	src->params.object = (t_obj *)ft_memalloc(sizeof(t_obj) *
		src->objects_cnt + 1);
	src->params.light = (t_light *)ft_memalloc(sizeof(t_light) *
		src->lights_cnt + 1);
	while (ft_getline(fd, &(*params)))
	{
		get_parameters(*params, src);
		free(*params);
		(*params)++;
	}
	free(params);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:15:09 by avishnev          #+#    #+#             */
/*   Updated: 2018/04/17 12:15:11 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		error_manadge(char *str, int flag, char *src)
{
	if (flag == 1)
		free(src);
	ft_putendl(str);
	system("leaks -q RTv1");
	exit(1);
}

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

int			validate_data(char *source, t_src *src)
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
	if ((tmp[1] != '(' && tmp[1] != '{') || 
		(tmp[ft_strlen(tmp) - 2] != ')' && tmp[ft_strlen(tmp) - 2] != '}'))
		error_manadge(MSG_FORMAT, 1, tmp);
	free(tmp);
	tmp = ft_strsub(source, 0, ft_strlen(source));
	get_data_values(tmp, src);
	free(tmp); 
	return (0);
}

void		get_parameters(char *str, t_src *src)
{
	if (str[0] == '#' || str[0] == '\0') /*ignore blyad coments*/
		return ;
	else if (str[0] == '-' && str[1] == '>')
		validate_data(&str[2], src);
}


void		get_camera_position(char *cord, t_src *src)
{
	int		len;

	len = ft_strlen(cord);
	//printf("len == %d cord[0] == %c cord[len] == %c\n", len, cord[0], cord[len - 1]);
	if (len > 15 || len < 9 || cord[0] != '[' || cord[len - 1] != ']')
		error_manadge(MSG_FORMAT, 0, cord);
	while (*cord)
	{
		if (*cord == '{')
		{
			src->camera.x = ft_atoi(++cord);
			printf("src->camera.x == %d\n", src->camera.x);
		}
		// printf("CORD == %c\n", *cord);
		else if (*cord == ',')
		{
			src->camera.y = ft_atoi(++cord);
			printf("src->camera.y == %d\n", src->camera.y);
		}
		else if (*cord == ',' && (*(cord + 2) == '}' ||
				*(cord + 4) == '}' || *(cord + 3) == '}'))
		{
			src->camera.z = ft_atoi(++cord);
			printf("src->camera.z == %d\n", src->camera.z);
		}
		cord++;
	}
	if (src->camera.x < -50 || src->camera.x > 50 ||
		src->camera.y < -50 || src->camera.y > 50 ||
		src->camera.z < -50 || src->camera.z > 50)
		error_manadge(MSG_CAM, 0, cord);
}


int			get_data_values(char *string, t_src *src)
{
	char		*tmp;

	tmp = ft_strsub(string, 0, 6);
	if (ft_strcmp(tmp, "camera") == 0)
	{
		get_camera_position(&string[7], src);
		ft_putendl(string);
	
	}
	free(tmp);
	return (0);
}

void		read_from_file(char *av, t_src *src)
{
	int		i;
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
	i = 0;
	while (ft_getline(fd, &params[i]))
	{
		get_parameters(params[i], src);
		free(params[i]);
		i++;
	}
	free(params);
	close(fd);
}

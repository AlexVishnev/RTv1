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

void		error_manadge(char *str)
{
	ft_putendl(str);
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
void		get_parameters(char *str)
{
	if (str[0] == '#')
		return ;
	if (str[0] == '-' && str[1] == '>')
		ft_putendl(&str[2]);
}

void		read_from_file(char *av, t_src *s)
{
	int		i;
	int		fd;
	char	**params;
	int		size;

	fd = open(av, O_RDONLY);
	size = get_size(av);
	s = NULL;
	params = (char **)ft_memalloc(sizeof(char *) * size + 1);
	i = 0;
	while (ft_getline(fd, &params[i]))
	{
		get_parameters(params[i]);
		i++;
	}
	params[i] = NULL;
	close(fd);
}
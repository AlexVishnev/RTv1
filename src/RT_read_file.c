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
	exit (1);
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

int			fill_data(char *source, t_src *src)
{
	char		*tmp;

	tmp = ft_strsub(source, 0, 6);
	if (!(ft_strcmp(tmp, "camera") || ft_strcmp(tmp, "object") || 
			ft_strcmp(tmp, "sligth"))) 
	{
		free(tmp);
		error_manadge("Error: invalid params"); // add free
	}
	free(tmp);
	tmp = ft_strsub(source, 7, ft_strlen(source));
	if (*tmp != '[')
		error_manadge("Error: invalid params");
	free(tmp);
	return (0);


}

	

void		get_parameters(char *str, t_src *src)
{
	//ft_putendl(str);
	if (str[0] == '#' || str[0] == '\n')
		return ;
	else if (str[0] == '-' && str[1] == '>')
		fill_data(&str[2], src);
	else if (str[9] == ' ')
		error_manadge("Error: invalid format of data");
}

void		read_from_file(char *av, t_src *src)
{
	int		i;
	int		fd;
	char	**params;
	int		size;

	fd = open(av, O_RDONLY);
	if (read(fd, av, 0 ))
		error_manadge("Error: You argunent are shit");
	size = get_size(av);
	src = NULL;
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
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

int			validate_file(char **params)
{

}
void		read_from_file(char *av, t_src *s)
{
	int		fd;
	char	**params;

	params = (char **)malloc(sizeof(char *) * sizeoffile + 1);

	if (fd = open(av, O_RDONLY) < 0 || read(fd, NULL, 0) < 0)
		error_manadge("Error: can't open this shit");
	while (ft_getline(fd, &params[i]))
		i++;

	paramsp[i] = NULL;

	

}
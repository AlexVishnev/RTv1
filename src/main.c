/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:43:10 by avishnev          #+#    #+#             */
/*   Updated: 2018/04/14 15:39:31 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char 	brackets(char *s, char c, char c1)
{
	if (s[0] != c || s[ft_strlen(s) - 1] != c1)
		error_manadge("Error: parish hren polnyu");
}

void	instruction(void)
{
	error_manadge("_____________MSG__________");	
}

int	main(int ac, char **av)
{
	t_src	*src;

	if (ac != 2)
		instruction();
	src = (t_src *)malloc(sizeof(t_src));
	read_from_file(av[1], &src);
//	else
		//rt_init(av[1]);
	return (0);
}

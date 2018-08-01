/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:21:54 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 18:06:10 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_manadge(char *message, int flag, char *src)
{
	if (flag == 1)
		free(src);
	ft_putendl(message);
	exit(1);
}

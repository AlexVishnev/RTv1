/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:30:31 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 17:30:46 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*buff;

	if (!(buff = (void *)malloc(sizeof(void *) * size)))
		return (NULL);
	ft_bzero(buff, size);
	return (buff);
}

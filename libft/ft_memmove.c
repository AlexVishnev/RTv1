/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:00:50 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 15:00:51 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dbuff;
	char	*sbuff;

	dbuff = (char*)dst;
	sbuff = (char*)src;
	if (dbuff > sbuff)
	{
		while (len--)
			dbuff[len] = sbuff[len];
	}
	else
		ft_memcpy(dbuff, sbuff, len);
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:29:41 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 17:29:51 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*dest1;
	size_t			i;

	if (len == 0)
		return (dest);
	i = 0;
	dest1 = (unsigned char *)dest;
	while (i < len)
		dest1[i++] = c;
	return (dest);
}

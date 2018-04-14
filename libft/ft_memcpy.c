/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:34:05 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 17:34:12 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *restrict d, const void *restrict s, size_t n)
{
	unsigned char		*des;
	const unsigned char	*srcs;

	des = (unsigned char *)d;
	srcs = (unsigned char *)s;
	while (n--)
		*des++ = *srcs++;
	return (d);
}

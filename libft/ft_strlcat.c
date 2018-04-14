/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 11:18:49 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 11:18:51 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	i = 0;
	if (size <= d_len)
		return (s_len + size);
	while (dst[i] && i < size - 1)
		i++;
	while (size - 1 > i && *src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (d_len + s_len);
}

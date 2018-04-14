/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 11:37:49 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 15:17:50 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen((char *)str);
	if (ft_strchr(str, c) == NULL)
		return (NULL);
	while (len != 0 && str[len] != (char)c)
		len--;
	return ((str[len] == (char)c) ? ((char *)&str[len]) : NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 11:37:49 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 11:37:50 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, int c, int len)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c && i <= len)
		i++;
	if (str[i] == (char)c)
		return ((char*)str);
	return (NULL);
}

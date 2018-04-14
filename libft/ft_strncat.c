/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 09:52:29 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/03 09:52:32 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *app, size_t n)
{
	char	*buff;

	buff = dest;
	while (*buff != '\0')
		buff++;
	while (*app != '\0' && n > 0)
	{
		*buff = *app;
		buff++;
		app++;
		n--;
	}
	*buff = '\0';
	return (dest);
}

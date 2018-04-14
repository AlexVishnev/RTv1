/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:50:59 by avishnev          #+#    #+#             */
/*   Updated: 2017/10/30 15:02:46 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(*str) * (ft_strlen(src) + 1))))
		return (NULL);
	return (ft_strcpy(str, src));
}

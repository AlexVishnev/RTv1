/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:49:01 by avishnev          #+#    #+#             */
/*   Updated: 2017/11/06 14:49:02 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *str)
{
	unsigned long	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_unstrlen(const char *str, int chr)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != chr)
		len++;
	return (len);
}
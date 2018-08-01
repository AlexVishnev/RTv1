/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:31:15 by avishnev          #+#    #+#             */
/*   Updated: 2018/08/01 17:31:17 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

void	print_error_and_exit(const char *erorr_msg, int exit_stat)
{
	perror(erorr_msg);
	exit(exit_stat);
}

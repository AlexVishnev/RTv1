/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_external.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apisotsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:44:43 by apisotsk          #+#    #+#             */
/*   Updated: 2018/08/01 13:44:44 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "cJSON/cJSON.h"
# include "rtv_shared_types.h"
# include "libft/includes/libft.h"

typedef struct	s_field_info
{
	char		*name;
	bool		is_array;
	bool		is_int;
	u_int8_t	type;
	u_int8_t	arr_type;
	u_int8_t	max_allowed_arr_size;
	int			array_size;
	int			max_abs;
	bool		can_be_signed;
}				t_field_info;

void			please_parse_field(cJSON *json_chain,
			struct s_field_info *field_info, void *data);
void			please_parse_camera(cJSON *json_chain, void *data);
void			please_parse_lights(cJSON *json_chain, void *data);
void			please_parse_objects(cJSON *json_chain, void *data);
void			please_validate_and_save(void *src,
			void *dst, t_field_info *info);
void			print_error_and_exit(const char *erorr_msg, int exit_stat);

#endif

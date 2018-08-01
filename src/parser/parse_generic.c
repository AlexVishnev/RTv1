/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apisotsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:55:01 by apisotsk          #+#    #+#             */
/*   Updated: 2018/08/01 16:55:03 by apisotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static inline void	please_parse_array_field(cJSON *json_aray,
	struct s_field_info *field_info, void *addr)
{
	cJSON		*tmp;
	int			arr_idx;
	float		arr[field_info->array_size];

	arr_idx = -1;
	while (++arr_idx < field_info->array_size)
	{
		tmp = cJSON_GetArrayItem(json_aray, arr_idx);
		if (tmp->type != field_info->arr_type)
			print_error_and_exit("Fuck, arr_type", -6);
		arr[arr_idx] = ((float)(tmp->valuedouble));
	}
	please_validate_and_save((void*)arr, addr, field_info);
}

void				please_parse_field(cJSON *json_chain,
	struct s_field_info *field_info, void *addr)
{
	cJSON	*json_field;
	float	tmp;

	if (!(json_field = cJSON_GetObjectItem(json_chain,
		field_info->name)))
		print_error_and_exit("FUCKING cJSON_GetObjectItem", -3);
	if (json_field->type != field_info->type)
		print_error_and_exit("Fuck, arr_type", -4);
	if (field_info->is_array)
	{
		field_info->array_size = cJSON_GetArraySize(json_field);
		if (field_info->array_size != field_info->max_allowed_arr_size)
			print_error_and_exit("Fuck, arr_size", -13);
		please_parse_array_field(json_field, field_info, addr);
	}
	else
	{
		field_info->array_size = 1;
		tmp = (float)json_field->valuedouble;
		if (field_info->is_int)
			please_validate_and_save((void*)&(json_field->valueint),
															addr, field_info);
		else
			please_validate_and_save((void*)&tmp, addr, field_info);
	}
}

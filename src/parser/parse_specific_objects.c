/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specific_objects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchaus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 19:46:27 by vchaus            #+#    #+#             */
/*   Updated: 2018/08/01 19:46:28 by vchaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	parse_single_object_part(cJSON *json_object, t_obj *p_ob,
													t_field_info *field_info)
{
	field_info->name = "specular";
	field_info->max_abs = 100000;
	please_parse_field(json_object, field_info, ((void *)&(p_ob->specular)));
	field_info->name = "angle";
	please_parse_field(json_object, field_info, ((void *)&(p_ob->angle)));
	field_info->name = "reflect";
	field_info->max_abs = 1;
	please_parse_field(json_object, field_info, ((void *)&(p_ob->reflection)));
	field_info->type = cJSON_Array;
	field_info->is_array = true;
	field_info->arr_type = cJSON_Number;
	field_info->name = "position";
	field_info->can_be_signed = true;
	field_info->max_abs = 1000;
	field_info->max_allowed_arr_size = 3;
	please_parse_field(json_object, field_info, ((void *)&(p_ob->mid)));
	field_info->name = "rotation";
	please_parse_field(json_object, field_info, ((void *)&(p_ob->direction)));
	field_info->name = "color";
	field_info->can_be_signed = false;
	field_info->max_abs = 255;
	please_parse_field(json_object, field_info, ((void *)&(p_ob->color)));
}

static void	please_parse_single_object(cJSON *json_object, void *data)
{
	t_obj			*p_ob;
	t_field_info	field_info;

	p_ob = (t_obj *)data;
	field_info.max_allowed_arr_size = 1;
	field_info.type = cJSON_Number;
	field_info.is_array = false;
	field_info.name = "type";
	field_info.is_int = true;
	field_info.can_be_signed = false;
	field_info.max_abs = 4;
	please_parse_field(json_object, &field_info, ((void *)&(p_ob->type)));
	field_info.is_int = false;
	field_info.name = "size";
	please_parse_field(json_object, &field_info, ((void *)&(p_ob->radius)));
	parse_single_object_part(json_object, p_ob, &field_info);
}

void		please_parse_objects(cJSON *json_chain, void *data)
{
	cJSON	*json_objects;
	cJSON	*tmp;
	t_src	*p_src;
	int		arr_idx;

	if (!(json_objects = cJSON_GetObjectItem(json_chain, "objects")))
		print_error_and_exit("FUCKING objects", -10);
	if (json_objects->type != cJSON_Array)
		print_error_and_exit("objects must be array", -11);
	p_src = (t_src*)data;
	p_src->objects_cnt = cJSON_GetArraySize(json_objects);
	p_src->params.object = (t_obj *)ft_memalloc(sizeof(t_obj) *
		p_src->objects_cnt + 1);
	arr_idx = -1;
	while (++arr_idx < p_src->objects_cnt)
	{
		tmp = cJSON_GetArrayItem(json_objects, arr_idx);
		please_parse_single_object(tmp,
			((void*)&p_src->params.object[arr_idx]));
	}
}

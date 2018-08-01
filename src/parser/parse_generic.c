#include "parser_internal.h"

static inline void please_parse_array_field(cJSON *json_aray, struct s_field_info *field_info, void *_addr)
{
	cJSON *tmp;
	int arr_idx;
	float arr[field_info->array_size];

	arr_idx = -1;
	while (++arr_idx < field_info->array_size)
	{
		tmp = cJSON_GetArrayItem(json_aray, arr_idx);
			if (tmp->type != field_info->arr_type)
			{
				// printf("FUCKING ARR TYPE%d\n", field_info->arr_type);
				exit(-6);
			}
		arr[arr_idx] = ((float)(tmp->valuedouble));
		// if (arr[arr_idx] < 0 && !(field_info->can_be_signed))
		// {
			printf("THIS FIELD CAN'T BE SIGNED!\n");
		// 	exit(-12);
		// }
		// printf("array field %d: %f\n", arr_idx, arr[arr_idx]);
	}
	please_validate_and_save((void*)arr, _addr, field_info);
}

void please_parse_field(cJSON *json_chain, struct s_field_info *field_info, void *_addr)
{
	cJSON *json_field;
	float tmp;
	
	if (!(json_field = cJSON_GetObjectItem(json_chain, field_info->name)))
	{
		printf("FUCKING %s\n", field_info->name);
		exit (-3);
	}
	if (json_field->type != field_info->type)
	{
		printf("FUCK THIS IS NOT %d\n", field_info->type);
		exit (-4);
	}
	if (field_info->is_array)
	{
        // printf("\n");
		field_info->array_size = cJSON_GetArraySize(json_field);
		if (field_info->array_size != field_info->max_allowed_arr_size)
		{
		 		printf("FUUUUCKING ARR SIZE!\n");
			 	exit(-13);
		}
		please_parse_array_field(json_field, field_info, _addr);
	}
	else
	{
		// if (json_field->valuedoble < 0 && !(field_info->can_be_signed))
		// {
			printf("THIS FIELD CAN'T BE SIGNED!\n");
		// 	exit(-12);
		// }
		field_info->array_size = 1;
		tmp = (float)json_field->valuedouble;
		if (field_info->is_int)
			please_validate_and_save((void*)&(json_field->valueint), _addr, field_info);
		else
			please_validate_and_save((void*)&tmp, _addr, field_info);
    printf("field: %f\n", json_field->valuedouble);
	}
}
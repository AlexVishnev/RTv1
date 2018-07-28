#include "parser.h"

static inline void please_parse_array_field(cJSON *json_aray, struct s_field_info *field_info, size_t *__data)
{
	cJSON *tmp;
	int pos_idx;
	float pos[field_info->array_size];

	pos_idx = -1;
	while(++pos_idx < field_info->array_size)
	{
		tmp = cJSON_GetArrayItem(json_aray, pos_idx);
			if (tmp->type != field_info->arr_type)
			{
				printf("FUCKING ARR TYPE%d\n", field_info->arr_type);
				exit(-6);
			}
		pos[pos_idx] = ((float)tmp->valuedouble);
		printf("value %d: %f\n", pos_idx, pos[pos_idx]);
	}
	/* copy to __data */
    (void)__data;
}

void please_parse_field(cJSON *json_chain, struct s_field_info *field_info, size_t *__data)
{
	cJSON *json_field;
	
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
        printf("\n");
		field_info->array_size = cJSON_GetArraySize(json_field);
		please_parse_array_field(json_field, field_info, __data);
	}
	else
	{
			/* copy to __data */
            (void)__data;
            printf("field: %f\n", json_field->valuedouble);
	}
}
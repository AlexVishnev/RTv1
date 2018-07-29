#ifndef __PARSER_INTERNAL_H__
# define __PARSER_INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> 
#include "cJSON/cJSON.h"
#include "rtv_shared_types.h"

typedef struct s_field_info
{
	char *name;
	bool is_array;
	u_int8_t type;
	u_int8_t arr_type;
	int array_size;
} t_field_info;

void please_parse_field(cJSON *json_chain, struct s_field_info *field_info, void *__data);
void please_parse_camera(cJSON *json_chain, void *__data);
void please_parse_lights(cJSON *json_chain, void *__data);
void please_parse_objects(cJSON *json_chain, void *__data);

void please_validate_and_save_enum_of_int(void *src, void *dst, int arr_size, int max_abs);
void please_validate_and_save_enum_of_float(void *src, void *dst, int arr_size, int max_abs);

#endif 
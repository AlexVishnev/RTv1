#ifndef __PARSER_INTERNAL_H__
# define __PARSER_INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> 
#include "cJSON/cJSON.h"
#include "rtv_shared_types.h"
#include "libft/includes/libft.h"

typedef struct s_field_info
{
	char *name;
	bool is_array;
	bool is_int;
	u_int8_t type;
	u_int8_t arr_type;
	u_int8_t max_allowed_arr_size;
	int array_size;
	int max_abs;
	bool can_be_signed;
} t_field_info;

void please_parse_field(cJSON *json_chain, struct s_field_info *field_info, void *__data);
void please_parse_camera(cJSON *json_chain, void *__data);
void please_parse_lights(cJSON *json_chain, void *__data);
void please_parse_objects(cJSON *json_chain, void *__data);
void please_validate_and_save(void *src, void *dst, t_field_info *info);

#endif 

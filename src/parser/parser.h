#ifndef __PARSER_H__
# define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> 
#include "../../cJSON/cJSON.h"

typedef struct s_field_info
{
	char *name;
	bool is_array;
	u_int8_t type;
	u_int8_t arr_type;
	size_t array_size;
} t_field_info;

void please_parse_field(cJSON *json_chain, struct s_field_info *field_info, size_t *__data);


#endif 
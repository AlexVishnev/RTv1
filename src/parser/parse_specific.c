#include "parser_internal.h"

void please_parse_camera(cJSON *json_chain, void *__data)
{
	cJSON *json_camera;
	t_field_info field_info;

	if (!(json_camera = cJSON_GetObjectItem(json_chain, "camera")))
	{
		printf("FUCKING CAMERA\n");
		exit (-2);
	}
	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	please_parse_field(json_camera, &field_info, __data);
	field_info.name = "rotation";
	please_parse_field(json_camera, &field_info, __data);
}

static void please_parse_single_light(cJSON *json_light, void *__data)
{
	t_field_info field_info;

	printf("\nLIGHT JSON:\n");
	field_info.type = cJSON_Number;
	field_info.is_array = false;
	field_info.name = "type";
	please_parse_field(json_light, &field_info, __data);
	field_info.name = "intensive";
	please_parse_field(json_light, &field_info, __data);

	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	please_parse_field(json_light, &field_info, __data);
	field_info.name = "rotation";
	please_parse_field(json_light, &field_info, __data);
}

void please_parse_lights(cJSON *json_chain, void *__data)
{
	cJSON *json_lights, *tmp;
	int arr_idx;

	if (!(json_lights = cJSON_GetObjectItem(json_chain, "lights")))
	{
		printf("FUCKING lights\n");
		exit (-7);
	}
	if (json_lights->type != cJSON_Array)
	{
		printf("Lights must be array\n");
		exit (-8);
	}
	arr_idx = -1;
	while (++arr_idx < cJSON_GetArraySize(json_lights))
	{
		tmp = cJSON_GetArrayItem(json_lights, arr_idx);
		please_parse_single_light(tmp, __data);
	}
}

static void please_parse_single_object(cJSON *json_object, void *__data)
{
	t_field_info field_info;

	printf("\nObject JSON:\n");
	field_info.type = cJSON_Number;
	field_info.is_array = false;
	field_info.name = "type";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "size";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "specular";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "angle";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "reflect";
	please_parse_field(json_object, &field_info, __data);

	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "rotation";
	please_parse_field(json_object, &field_info, __data);
	field_info.name = "color";
	please_parse_field(json_object, &field_info, __data);
}

void please_parse_objects(cJSON *json_chain, void *__data)
{
	cJSON *json_objects, *tmp;
	int arr_idx;

	if (!(json_objects = cJSON_GetObjectItem(json_chain, "objects")))
	{
		printf("FUCKING objects\n");
		exit (-10);
	}
	if (json_objects->type != cJSON_Array)
	{
		printf("Objectss must be array\n");
		exit (-11);
	}
	arr_idx = -1;
	while (++arr_idx < cJSON_GetArraySize(json_objects))
	{
		tmp = cJSON_GetArrayItem(json_objects, arr_idx);
		please_parse_single_object(tmp, __data);
	}
}
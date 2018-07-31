#include "parser_internal.h"

void please_parse_camera(cJSON *json_chain, void *__data)
{
	cJSON *json_camera;
	t_field_info field_info;
	t_src *p_src;

	if (!(json_camera = cJSON_GetObjectItem(json_chain, "camera")))
	{
		ft_putstr("FUCKING CAMERA\n");
		exit (-2);
	}
	p_src = (t_src*)__data;
	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.can_be_signed = true;
	field_info.max_abs = 1000;
	field_info.name = "position";
	please_parse_field(json_camera, &field_info, ((void*)&(p_src->params.o)));
	field_info.name = "rotation";
	please_parse_field(json_camera, &field_info, ((void*)&(p_src->params.d)));
}

static void please_parse_single_light(cJSON *json_light, void *__data)
{
	t_field_info	field_info;
	t_light			*p_light;

	p_light =(t_light *)__data;

	field_info.type = cJSON_Number;
	field_info.is_array = false;
	field_info.name = "type";
	field_info.can_be_signed = false;
	field_info.max_abs = 3;
	field_info.is_int = true;
	please_parse_field(json_light, &field_info, ((void *)&(p_light->type)));
	printf("\nLIGHT FIIIIIIEEEEE\n");
	field_info.name = "intensive";
	field_info.can_be_signed = false;
	field_info.is_int = false;
	field_info.max_abs = 1;
	please_parse_field(json_light, &field_info, ((void *)&(p_light->intensive)));
	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	field_info.can_be_signed = true;
	field_info.max_abs = 1000;
	please_parse_field(json_light, &field_info, ((void *)&(p_light->position)));
	field_info.name = "rotation";
	please_parse_field(json_light, &field_info, ((void *)&(p_light->direction)));

}

void please_parse_lights(cJSON *json_chain, void *__data)
{
	cJSON *json_lights, *tmp;
	t_src *p_src;
	int arr_idx;

	if (!(json_lights = cJSON_GetObjectItem(json_chain, "lights")))
	{
		ft_putstr("FUCKING lights\n");
		exit (-7);
	}
	if (json_lights->type != cJSON_Array)
	{
		ft_putstr("Lights must be array\n");
		exit (-8);
	}
	/* it is a fucking amazing code */
	p_src = (t_src*)__data;
	p_src->lights_cnt = cJSON_GetArraySize(json_lights);
	p_src->params.light = (t_light *)ft_memalloc(sizeof(t_light) *
		p_src->lights_cnt + 1);
	/* fucking amazing code end */
	arr_idx = -1;
	while (++arr_idx < p_src->lights_cnt)
	{
		tmp = cJSON_GetArrayItem(json_lights, arr_idx);
		// printf("\n\n\n\n_____________[%d] < p_src->lights_cnt [%d]\n", arr_idx,  p_src->lights_cnt);
		// printf("p_src->lights_cnt ==== %d\n", p_src->lights_cnt);
		please_parse_single_light(tmp, ((void*)&(p_src->params.light[arr_idx])));
	}
}

static void please_parse_single_object(cJSON *json_object, void *__data)
{
	t_obj			*p_object;
	t_field_info	field_info;

	p_object =(t_obj *)__data;

	field_info.type = cJSON_Number;
	field_info.is_array = false;
	field_info.name = "type";
	field_info.is_int = true;
	field_info.can_be_signed = false;
	field_info.max_abs = 3;
	please_parse_field(json_object, &field_info, ((void *)&(p_object->type)));
	field_info.is_int = false;
	field_info.name = "size";
	please_parse_field(json_object, &field_info, ((void *)&(p_object->radius)));
	field_info.name = "specular";
	field_info.max_abs = 1000;
	please_parse_field(json_object, &field_info, ((void *)&(p_object->specular)));
	field_info.name = "angle";
	please_parse_field(json_object, &field_info, ((void *)&(p_object->angle)));
	field_info.name = "reflect";
	field_info.max_abs = 1;
	please_parse_field(json_object, &field_info,  ((void *)&(p_object->reflection)));

	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	field_info.can_be_signed = true;
	field_info.max_abs = 1000;
	printf("\nObject JSON:\n");
	please_parse_field(json_object, &field_info, ((void *)&(p_object->mid)));
	field_info.name = "rotation";
	please_parse_field(json_object, &field_info, ((void *)&(p_object->direction)));
	field_info.name = "color";
	field_info.can_be_signed = false;
	field_info.max_abs = 255;
	please_parse_field(json_object, &field_info, ((void *)&(p_object->color)));
}

void please_parse_objects(cJSON *json_chain, void *__data)
{
	cJSON *json_objects, *tmp;
	t_src *p_src;
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
	/* it is a fucking amazing code */
	p_src = (t_src*)__data;
	p_src->objects_cnt = cJSON_GetArraySize(json_objects);
	p_src->params.object = (t_obj *)ft_memalloc(sizeof(t_obj) *
		p_src->objects_cnt + 1);
	/* fucking amazing code end */
	arr_idx = -1;
	while (++arr_idx < p_src->objects_cnt)
	{
		printf("objects:\n");
		tmp = cJSON_GetArrayItem(json_objects, arr_idx);
		please_parse_single_object(tmp, ((void*)&p_src->params.object[arr_idx]));
	}
}
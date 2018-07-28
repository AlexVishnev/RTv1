#include "parser.h"

/* Fucking converter file into string
 * Dirty unsave code
 * Fuck youserlf, motherfacker!
 */
int read_file(char **file_str)
{
	 FILE *f;
	 long fsize;
	 char *fucking_tmp;

	 if (!(f = fopen("light.json", "rb")))
	 {
		printf("Fuck, file not found...\n");
		exit(-1);
	 }
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);


	fucking_tmp = malloc(fsize + 1);
	fread(fucking_tmp, fsize, 1, f);
	fclose(f);
	fucking_tmp[fsize] = 0;
	printf("File: \n%s", fucking_tmp);
	*file_str = fucking_tmp;
	return (0);
}

cJSON *get_json_chain(char *free_aft_use)
{
	cJSON *json_chain;

	if (!(json_chain = cJSON_Parse(free_aft_use)))
	{
		printf("FUCKING LIBRARY\n");
		exit (-1);
	}
	free(free_aft_use);
	return (json_chain);
}

void please_parse_camera(cJSON *json_chain, size_t *__data)
{
	cJSON *json_camera;
	t_field_info field_info;

	/* not key sensative */
	if (!(json_camera = cJSON_GetObjectItem(json_chain, "camera")))
	{
		printf("FUCKING CAMERA\n");
		exit (-2);
	}
	/* All validation inside functions */
	field_info.type = cJSON_Array;
	field_info.is_array = true;
	field_info.arr_type = cJSON_Number;
	field_info.name = "position";
	please_parse_field(json_camera, &field_info, __data);
	field_info.name = "rotation";
	please_parse_field(json_camera, &field_info, __data);

	/* Free json object */
	//cJSON_Delete(json_camera);
}

void please_parse_single_light(cJSON *json_light, size_t *__data)
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
	//(json_light);
}

void please_parse_lights(cJSON *json_chain, size_t *__data)
{
	cJSON *json_lights, *tmp;
	int arr_idx;

	/* not key sensative */
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
	//cJSON_Delete(json_lights);
}

void please_parse_single_object(cJSON *json_object, size_t *__data)
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
	//(json_object);
}

void please_parse_objects(cJSON *json_chain, size_t *__data)
{
	cJSON *json_objects, *tmp;
	int arr_idx;

	/* not key sensative */
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
	//cJSON_Delete(json_objects);
}

void please_parse_it_into_structure(cJSON *json_chain, size_t *__data)
{
	/* there will be cast pointer into relted data */
	/* All validation inside functions */
	please_parse_camera(json_chain, __data);
	please_parse_lights(json_chain, __data);
	please_parse_objects(json_chain, __data);
	/* parse other staf here */
}

void call_me_cacao(char *file_content, size_t *__data)
{
	cJSON *json_chain;

	/* All validation inside functions */
	json_chain = get_json_chain(file_content);

	please_parse_it_into_structure(json_chain, __data);
	cJSON_Delete(json_chain);
}

/* Ebbaniy stud a ne main */
int main(void)
{
	char *file_str;
	/* After call read_file() do not forget to clean up memory */
	read_file(&file_str);
	printf("Will fuck your Mom!\n%s", file_str);
	call_me_cacao(file_str, NULL);
	system("leaks -q a.out");
	sleep(5);
	return (0);
}

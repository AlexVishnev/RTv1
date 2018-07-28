#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../cJSON/cJSON.h"

/* Fucking converter file into string
 * Dirty unsave code
 * Fuck youserlf, motherfacker!
 */
int read_file(char **file_str)
{
	 FILE *f;
	 long fsize;
	 char *fucking_tmp;

	 if (!(f = fopen("textfile.txt", "rb")))
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

/* Ebbaniy stud a ne main */
int main(void)
{
	char *file_str;
	/* After call read_file() do not forget to clean up memory */
	read_file(&file_str);
	printf("Will fuck your Mom!\n%s", file_str);
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
	return (json_chain);
}

#define NORMAL_POS_ARR_SIZE 3

#define POS_X_IDX 0
#define POS_Y_IDX 1
#define POS_Z_IDX 2
#define POS_MAX_IDX 3

void please_save_vec3(cJSON *json_good_arr, size_t *__data)
{
	cJSON *tmp;
	u_int8_t pos_idx;
	float pos[3];

	pos_idx = -1;
	while(++pos_idx < POS_MAX_IDX) {
		tmp = cJSON_GetArrayItem(json_good_arr, POS_X_IDX);
			if (tmp->type != cJSON_Number)
			{
				printf("FUCKINg TYPE\n");
				exit(-6);
			}
		pos[pos_idx] = (float)tmp->valuedouble;
	}
	/* copy to __data */
}

void please_parse_vec3(cJSON *json_chain, const char * const field_name, size_t *__data)
{
	cJSON *json_pos_arr;
	size_t arr_size;

	if (!(json_pos_arr = cJSON_GetObjectItem(json_chain, field_name)))
	{
		printf("FUCKING %s\n", field_name);
		exit (-3);
	}
	if (json_pos_arr->type != cJSON_Array)
	{
		printf("FUCK THIS IS NOT ARRAY\n");
		exit (-4);
	}
	arr_size = cJSON_GetArraySize(json_pos_arr);
	if (arr_size != NORMAL_POS_ARR_SIZE)
	{
		printf("FUCKING ARR SIZE\n");
		exit (-5);
	}

	please_save_vec3(json_pos_arr, __data);
	free(json_pos_arr);
}

void please_parse_camera(cJSON *json_chain, size_t *__data)
{
	cJSON *json_camera;

	/* not key sensative */
	if (!(json_camera = cJSON_GetObjectItem(json_chain, "camera")))
	{
		printf("FUCKING CAMERA\n");
		exit (-2);
	}
	/* All validation inside functions */
	please_parse_vec3(json_camera, "position", __data);
	please_parse_vec3(json_camera, "direction", __data);
	/* Free json object */
	cJSON_Delete(json_camera);
}

void please_parse_it_into_structure(cJSON *json_chain, size_t *__data)
{
	/* there will be cast pointer into relted data */
	/* All validation inside functions */
	please_parse_camera(json_chain, __data);
	//please_parse_objects(json_chain, __data);
	//please_parse_lights(json_chain, __data);
	/* parse other staf here */
}

void call_me_cacao(char *file_content, size_t *__data)
{
	cJSON *json_chain;

	/* All validation inside functions */
	json_chain = get_json_chain(file_content);
	please_parse_it_into_structure(json_chain, __data);
}

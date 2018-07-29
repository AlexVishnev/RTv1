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

	 if (!(f = fopen("test.json", "rb")))
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
	// system("leaks -q a.out");
	// sleep(5);
	return (0);
}

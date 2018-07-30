#include <string.h>
#include <math.h>
#include "parser_internal.h"

#define MIN(a, b) (a) > (b) ? (b) : (a)
#define MAX (a, b) (a) > (b) ? (a) : (b)
#define CLAMP (c) MIN(MAX(c, min), max)
// # define CLAMP_f(x) fmin(fmax(x, min), max)

static void please_validate_and_save_enum_of_int(void *src,
	void *dst, t_field_info *info)
{
	int arr[info->array_size];
	int i;
	int *tmp;
	int min;
	int max;

	max = info->max_abs;
	min = (info->can_be_signed) ? (-max) : (0);
	tmp = (int*)src;
	i = -1;
	while (++i < info->array_size)
	{
		arr[i] = CLAMP(tmp[i]);
		printf ("original value: [%d], CLAMP value: [%d]", tmp[i], CLAMP(tmp[i]));
	}
	memcpy(dst, src, sizeof(arr));
}

static void please_validate_and_save_enum_of_float(void *src,
	void *dst, t_field_info *info)
{
	float arr[info->array_size];
	float *tmp;
	int i;
	int min;
	int max;

	max = info->max_abs;
	min = (info->can_be_signed) ? (-max) : (0);
	tmp = (float*)src;
	i = -1;
	while (++i < info->array_size)
	{
		arr[i] = CLAMP(tmp[i]);
		printf ("original value: [%f], CLAMP value: [%f]", tmp[i], CLAMP(tmp[i]));
	}
	memcpy(dst, src, sizeof(arr));
}

void please_validate_and_save(void *src, void *dst, t_field_info *info)
{
	if (info->is_int)
		please_validate_and_save_enum_of_int(src, dst, info);
	else
		please_validate_and_save_enum_of_float(src, dst, info);
}
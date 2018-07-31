#include <string.h>
#include <math.h>
#include "parser_internal.h"

#define MIN(a, b) (a) > (b) ? (b) : (a)
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define CLAMP(c, max) MIN(MAX(c, min), max)

static void please_validate_and_save_enum_of_int(void *src,
	void *dst, t_field_info *info)
{
	int arr[info->array_size];
	int i;
	int *tmp;
	int min;

	min = (info->can_be_signed) ? (-(info->max_abs)) : (0);
	tmp = (int*)src;
	i = -1;
	while (++i < info->array_size)
		arr[i] = CLAMP(tmp[i], info->max_abs);
	memcpy(dst, arr, sizeof(arr));
}

static void please_validate_and_save_enum_of_float(void *src,
	void *dst, t_field_info *info)
{
	float arr[info->array_size];
	float *tmp;
	int i;
	int min;

	min = (info->can_be_signed) ? (-(info->max_abs)) : (0);
	tmp = (float*)src;
	i = -1;
	while (++i < info->array_size)
		arr[i] = CLAMP(tmp[i], info->max_abs);
	memcpy(dst, arr, sizeof(arr));
}

void please_validate_and_save(void *src, void *dst, t_field_info *info)
{

	if (info->is_int)
		please_validate_and_save_enum_of_int(src, dst, info);
	else
		please_validate_and_save_enum_of_float(src, dst, info);
}


#include <string.h>
#include <math.h>
#include "parser_internal.h"

void please_validate_and_save_enum_of_int(void *src, void *dst, int arr_size, int max_abs)
{
	int arr[arr_size], i, sign, *tmp;

	tmp = (int*)src;
	i = -1;
	while (++i < arr_size)
	{
		arr[i] = (int)tmp[i];
		sign = (arr[i] < 0) ? (-1) : (1);
		arr[i] = (abs(arr[i]) > max_abs) ? (max_abs) : (arr[i] % max_abs);
		arr[i] *= sign;
	}
	memcpy(dst, src, sizeof(arr));
}

void please_validate_and_save_enum_of_float(void *src, void *dst, int arr_size, int max_abs)
{
	float arr[arr_size], *tmp;
	int i, sign;

	tmp = (float*)src;
	i = -1;
	while (i < arr_size)
	{
		arr[i] = tmp[i];
		sign = (arr[i] < 0) ? (-1) : (1);
		arr[i] = (fabsf(arr[i]) > max_abs) ? (max_abs) : ((int)arr[i] % max_abs);
		arr[i] *= sign;
	}
	memcpy(dst, src, sizeof(arr));
}
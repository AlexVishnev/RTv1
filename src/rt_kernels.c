/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kernels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:31:23 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/22 14:31:24 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		debugger(t_src *src)
{
	char	*msg;
	size_t	message_len;

	clGetProgramBuildInfo(src->op_cl.prog, src->op_cl.id_dev,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &message_len);
	msg = (char *)ft_memalloc(message_len);
	clGetProgramBuildInfo(src->op_cl.prog, src->op_cl.id_dev,
		CL_PROGRAM_BUILD_LOG, message_len, msg, NULL);
	ft_putendl(msg);
	ft_memdel((void **)&msg);
	free(msg);
	error_manadge("SMOTRI V COMPUTAX", 0, NULL);
}

void		compile_kernels(t_src *src, cl_int check, size_t size)
{
	src->op_cl.queue = clCreateCommandQueue(src->op_cl.text,
		src->op_cl.id_dev, 0, &check);
	if (check)
		error_manadge("Error: OpenCL clCreateCommandQueue", 0, NULL);
	src->op_cl.img_pxl = clCreateBuffer(src->op_cl.text, CL_MEM_READ_WRITE,
		src->op_cl.size, NULL, &check);
	if (check)
		error_manadge("Error: Falied creating buffer {img_pxl}", 0, NULL);
	src->op_cl.obj = clCreateBuffer(src->op_cl.text, CL_MEM_USE_HOST_PTR,
		src->objects_cnt * sizeof(t_params), src->params.object, &check);
	if (check)
		error_manadge("Error: Falied creating buffer {obj}", 0, NULL);
	src->op_cl.light = clCreateBuffer(src->op_cl.text, CL_MEM_USE_HOST_PTR,
		sizeof(t_params), src->params.light, &check);
	if (check)
		error_manadge("Error: Falied creating buffer {ligth}", 0, NULL);
	src->op_cl.prog = clCreateProgramWithSource(src->op_cl.text, 1,
		(const char **)&src->buffer, (const size_t *)&size, &check);
	if (check)
		error_manadge("Error: cant creat a programm", 0, NULL);
	check = clBuildProgram(src->op_cl.prog, 1, &src->op_cl.id_dev,
		NULL, NULL, NULL);
	check ? debugger(src) : 0;
	src->op_cl.kernel = clCreateKernel(src->op_cl.prog, "render", &check);
	check ? error_manadge("Error: kant create kernel", 0, NULL) : 0;
}

void		create_videohost(t_src *src)
{
	int		fd;
	size_t	size;
	cl_int	check;

	if ((fd = open("./computing/gpu_compute.cl", O_RDONLY)) <= 0)
		error_manadge("Error: cant open ./computing/gpu_compute.cl", 0, NULL);
	if (!src->buffer)
		error_manadge("Error: malloc in creating_videohost", 0, NULL);
	size = read(fd, src->buffer, 0x40000);
	close(fd);
	src->op_cl.size = src->surf->h * src->surf->w * sizeof(int);
	if ((check = clGetPlatformIDs(1, &src->op_cl.id_plat,
		&src->op_cl.nbr_platforms)))
		error_manadge("Error: OpenCL clGetPlatformIDs", 0, NULL);
	if ((check = clGetDeviceIDs(src->op_cl.id_plat, CL_DEVICE_TYPE_DEFAULT, 1,
		&src->op_cl.id_dev, &src->op_cl.nbr_device)))
		error_manadge("Error: OpenCL clGetDeviceIDs", 0, NULL);
	src->op_cl.text = clCreateContext(NULL, 1, &src->op_cl.id_dev,
		NULL, NULL, &check);
	if (check)
		error_manadge("Error: OpenCL clCreateContext", 0, NULL);
	compile_kernels(src, check, size);
}

void		opencl_kernel_run(t_src *src)
{
	cl_int		check;

	check = clSetKernelArg(src->op_cl.kernel, 0, sizeof(cl_mem),
		(void *)&src->op_cl.img_pxl);
	check ? error_manadge("Error: OpenCL set params", 0, NULL) : 0;
	check = clSetKernelArg(src->op_cl.kernel, 1, sizeof(t_params),
		(void *)&src->params);
	check ? error_manadge("Error: OpenCL set params", 0, NULL) : 0;
	check = clSetKernelArg(src->op_cl.kernel, 2, sizeof(cl_mem),
		(void *)&src->op_cl.obj);
	check ? error_manadge("Error: OpenCL set params", 0, NULL) : 0;
	check = clSetKernelArg(src->op_cl.kernel, 3, sizeof(cl_mem),
		(void *)&src->op_cl.light);
	check ? error_manadge("Error: OpenCL set params", 0, NULL) : 0;
	check = clEnqueueNDRangeKernel(src->op_cl.queue, src->op_cl.kernel, 2,
		NULL, (size_t[3]){src->surf->w, src->surf->h, 0}, NULL, 0, NULL, NULL);
	check ? error_manadge("Error: clEnqueueNDRangeKernel", 0, NULL) : 0;
	check = clEnqueueReadBuffer(src->op_cl.queue, src->op_cl.img_pxl, CL_TRUE,
		0, src->op_cl.size, src->surf->pixels, 0, NULL, NULL);
	check ? error_manadge("Error: clEnqueueReadBuffer", 0, NULL) : 0;
}

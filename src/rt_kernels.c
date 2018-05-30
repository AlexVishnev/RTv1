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

void		create_videohost(t_src *src)
{
	int		fd;
	char	*buffer;
	size_t	size;
	cl_int	rd ;

	fd = open("./computing/gpu_compute.cl", O_RDONLY); // loads instruction	
	buffer = ft_memalloc(2048 * 2048); // allocate memory for source file
	size = read(fd, buffer, 2048 * 2048); //read source file
	close(fd);
	src->op_cl.size = src->surf->h * src->surf->w * sizeof(int); 
	rd = clGetPlatformIDs(1, &src->op_cl.id_plat, &src->op_cl.nbr_platforms); //creating hosts platform 
	rd = clGetDeviceIDs(src->op_cl.id_plat, CL_DEVICE_TYPE_DEFAULT, 1, 
		&src->op_cl.id_dev, &src->op_cl.nbr_device); // seting type of  compute unit device 
	src->op_cl.text = clCreateContext(NULL, 1, &src->op_cl.id_dev,
		NULL, NULL, &rd); // manadge object kernel and programm
	src->op_cl.queue = clCreateCommandQueue(src->op_cl.text, 
		src->op_cl.id_dev, 0 , &rd);
	src->op_cl.img = clCreateBuffer(src->op_cl.text, CL_MEM_READ_WRITE, 
		src->op_cl.size, NULL, &rd);
	src->op_cl.obj = clCreateBuffer(src->op_cl.text, CL_MEM_USE_HOST_PTR, 
		src->objects_cnt * sizeof(t_params), src->params.object, &rd);
	src->op_cl.light = clCreateBuffer(src->op_cl.text, CL_MEM_USE_HOST_PTR, 
		sizeof(t_params), src->params.light, &rd);
	src->op_cl.prog = clCreateProgramWithSource(src->op_cl.text, 1,
		(const char **)&buffer, (const size_t *)&size, &rd);
	src->op_cl.kernel = clCreateKernel(src->op_cl.prog, "render", &rd);
	free(buffer);
}

void		kernel_function(t_src *src)
{
	cl_int		rd;

	rd = clSetKernelArg(src->op_cl.kernel, 0, sizeof(cl_mem),
		(void *)&src->op_cl.img);

	rd = clSetKernelArg(src->op_cl.kernel, 1, sizeof(t_params),
		(void *)&src->params);

	rd = clSetKernelArg(src->op_cl.kernel, 2, sizeof(cl_mem),
		(void *)&src->op_cl.obj);

	rd = clSetKernelArg(src->op_cl.kernel, 3, sizeof(cl_mem),
		(void *)&src->op_cl.light);
	rd = clEnqueueNDRangeKernel(src->op_cl.queue, src->op_cl.kernel, 2,
		NULL, (size_t[3]){src->surf->w,src->surf->h, 0}, NULL, 0, NULL, NULL);
	rd = clEnqueueReadBuffer(src->op_cl.queue, src->op_cl.img, CL_TRUE,
		 0, src->op_cl.size, (int*)src->surf->pixels, 0, NULL, NULL );
}

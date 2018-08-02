/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv_shared_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:43:27 by avishnev          #+#    #+#             */
/*   Updated: 2018/08/01 17:43:36 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_SHARED_TYPES_H
# define RTV_SHARED_TYPES_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <OpenCL/opencl.h>

typedef unsigned int	t_uint;

typedef	struct		s_light
{
	int				type;
	float			intensive;
	cl_float3		position;
	cl_float3		direction;
}					t_light;

typedef	struct		s_cam
{
	float			width;
	float			height;
	float			dist;
}					t_cam;


typedef	struct		s_obj
{
	int				type;
	cl_float3		mid;
	cl_float3		direction;
	cl_float4		color;
	float			specular;
	float			radius;
	float			reflection;
	float			angle;
}					t_obj;

typedef	struct		s_params
{
	cl_float3		o;
	cl_float3		d;
	cl_float3		camera_rot;
	t_obj			*object;
	t_light			*light;
	t_cam			look_pos;
	float			t_min;
	float			t_max;
	int				color;
	int				objects;
	int				lights;
	int				width;
	int				height;
	int				color_filter;
	int				stop_real_mode;
	int 			ssaa;
}					t_params;

typedef	struct		s_privat
{
	cl_command_queue	queue;
	cl_mem				img_pxl;
	cl_mem				obj;
	cl_mem				light;
	cl_program			prog;
	cl_device_id		id_dev;
	cl_platform_id		id_plat;
	cl_context			text;
	cl_kernel			kernel;
	cl_uint				nbr_platforms;
	cl_uint				nbr_device;
	size_t				size;
}					t_private;

typedef struct		s_control
{
	SDL_Event		e_k;
	int				flag;
	int				mouse_on;
	int				mouse_x;
	int				mouse_y;
	int				row;
	int				col;
	Uint8			data[4 * 32];
	Uint8			mask[4 * 32];
	int				hot_x;
	int				hot_y;
	int				i;
	int				chlen;
}					t_control;

typedef	struct		s_src
{
	SDL_Window		*wind;
	SDL_Surface		*surf;
	SDL_Surface		*fps;
	SDL_Cursor		*curs;
	TTF_Font		*ttf;
	t_obj			*objects;
	t_light			light;
	t_cam			camera;
	t_private		op_cl;
	t_params		params;
	unsigned int	*img_pxl;
	int				objects_cnt;
	int				lights_cnt;
	int				index;
	int				index1;
	char			*buffer;
	t_control		c;
}					t_src;

#endif

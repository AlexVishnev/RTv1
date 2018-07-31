#ifndef __RTV_SHARED_TYPES_H__
# define __RTV_SHARED_TYPES_H__

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
#  include <OpenCL/opencl.h>

typedef unsigned int	t_uint;

typedef struct		s_vector
{
	float			x;
	float			y;
}					t_vector;

typedef	struct		s_pos
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_pos;

typedef struct		s_ray
{
	float			x;
	float			y;
	float			z;
}					t_ray;

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

typedef	struct		s_color
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}					t_color;

typedef	struct		s_obj
{
	int				type;
	cl_float3		mid; // position
	cl_float3		direction;
	cl_float4		color; // r,g,b + a
	float			specular;
	float			radius; // size
	float			reflection;
	float			angle;
}					t_obj;

typedef	struct		s_params
{
	cl_float3		o; //camera position
	cl_float3		d; //camera direction
	cl_float3		camera_rot;
	t_obj			*object; //list of objects
	t_light			*light; //list of lights
	t_cam			look_pos;
	float			t_min; //wtf
	float			t_max; //wtf
	int				color; //wtf
	int				objects; //size
	int				lights;
	int				width;
	int				height;
	int 			color_filter;
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

typedef	struct		s_trace
{
	float			closest_t;
	t_obj			closest_obj;
	t_vector		t;
}					t_trace;

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
	t_color			color;
	t_pos			pos;
	// t_trace			tr;
	unsigned int	*img_pxl;
	int				objects_cnt;
	int				lights_cnt;
	int				index;
	int				index1;
	char			*buffer;
	t_control		c;
	t_ray			cam_pos;
}					t_src;

#endif 
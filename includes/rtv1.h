/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:44:26 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/17 18:43:43 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <time.h>
# include "libft/includes/libft.h"
# include <fcntl.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

# include <math.h>
# define WIN_WD 1024
# define WIN_HG 1024
# define MOUSE_SPEED 0.02

# ifdef __APPLE__
#  include <OpenCL/opencl.h>

# elif __linux__
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_mixer.h>
#  include <SDL2/SDL_ttf.h>
#  include <CL/cl.h>
# endif
# define MSG "\033[0;92m\033[3mUsage:\033[0m scenes/RT.sphere"
# define MSG_CLR "\033[4;31mError:\033[0m can't build color"
# define MSG_PARSE "\033[4;31mError:\033[0m You'r argunents are NOT support"
# define MSG_FORMAT "\033[4;31mError:\033[0m invalid format of data"
# define MSG_PARAMS "\033[4;31mError:\033[0m invalid params"
# define MSG_CAM "Error: invalid camera position"
# define MSG_LGHT "\033[4;31mError:\033[0m invalid spotlight position"
# define MSG_RULES "\033[4;31mRerspect rules!\033[0m"
# define MSG_OBJ "\033[4;31mError:\033[0m invalid object position"
# define REG "\nValide value [0.0 -> 1.0]"
# define REF "\033[4;31mError:\033[0m invalid value <reflection>"REG
# define MSG_OBJECT "\033[4;31mError:\033[0m objects missing"
# define MSG_L "\033[4;31mError:\033[0m wrong type of light"
# define DICK 42
# define POS_LIM 22100


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
	// float			r;
}					t_pos;

typedef struct		s_ray
{
	float			x;
	float			y;
	float			z;
	// float			w;
	// float			reflect;
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
	double			closest_t;
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
	t_trace			tr;
	unsigned int	*img_pxl;
	int				objects_cnt;
	int				lights_cnt;
	int				index;
	int				index1;
	char			*buffer;
	t_control		c;
	t_ray			cam_pos;
}					t_src;

void				wr_data(Uint8 d[], Uint8 m[], const char *z[], t_src *s);
SDL_Cursor			*init_system_cursor(const char *image[], t_src *src);

void				get_parameters(char *str, t_src *src);
cl_float3			get_position_object(char *cord, t_src *object);
void				get_spetial_params(t_obj *obj, char *params);
t_obj				get_object_params(char *cord, t_obj *object, t_src *src);
t_color				get_color_object(char *col);

int					get_data_values(char *data, t_src *src);
void				get_camera_position(char *cord, t_src *src);
void				get_spotlights_params(char *params, t_src *src, int index);

void				get_spotlights_direction(char *h, t_src *e, int r);
void				get_camera_direction(char *cord, t_src *src);

void				init_host(t_src *src);
void				init_parametrs(t_src *src);
void				opencl_kernel_run(t_src *src);
void				create_videohost(t_src *src);
void				compile_kernels(t_src *src, cl_int check, size_t size);
void				debugger(t_src *src);

int					expose_hook(t_src *src);

int					check_adecvate(int l, t_pos *p, int fl, t_color *s);
int					kostyl(char *s, int chr, int index);
int					brackects(char *s);
int					brackects_valide(char *s);
int					br_adecvat(char *s);
void				keyboards_control1(t_src *src, SDL_Scancode scancode);
void				mouse_control(t_src *src, SDL_Event e_k);

void				validate_data(char *source, t_src *src);
void				check_nbrs_object(char *av, t_src *src, int size);
void				read_from_file(char *data, t_src *s);
void				error_manadge(char *str, int flag, char *src);
int					get_size(char *av, t_src *src);
int					cnt_objects(char *params, t_src *src);

#endif

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

# include "libft.h"
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <math.h>
#  define WIN_WD 1280
#  define WIN_HG 1280
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
#  include "SDL_image.h"
#  include "SDL_mixer.h"
#  include "SDL_ttf.h"
# elif __linux__
 #  include <SDL2/SDL_image.h>
 #  include <SDL2/SDL_mixer.h>
 #  include <SDL2/SDL_ttf.h>
 #  include <CL/cl.h>
 # endif

# define MSG "Usage: scenes/scene.1"
# define MSG_CLR "Error: can't build color"
# define MSG_PARSE "Error: You'r argunents are shit"
# define MSG_FORMAT "Error: invalid format of data"
# define MSG_PARAMS "Error: invalid params"
# define MSG_CAM "Error: invalid camera position"
# define MSG_LGHT "Error: invalid spotlight position"
# define MSG_RULES "Rerspect rules!  "
# define MSG_OBJ "Error: invalid object position"
# define DICK 42
# define POS_LIM 100

typedef struct 			s_vector
{
	float				x;
	float				y;
}						t_vector;

typedef struct			s_ray
{
	float				x;
	float				y;
	float				z;
	float				w;
	float				reflect;
}						t_ray;

typedef	struct			s_pos
{
	float				x;
	float				y;
	float				z;
	float				w;
	float				r;
}						t_pos;

typedef	struct			s_cam
{
	t_pos				cam_pos;
	float				width;
	float				height;
	int					angle;
}						t_cam;

typedef	struct			s_light
{
	int					type;
	t_pos				*light_p;
	t_ray				direction;
	int					nbr;
	double				intensive;
}						t_light;

typedef	struct			s_color
{
	unsigned int		red;
	unsigned int		green;
	unsigned int		blue;
}						t_color;

typedef	struct			s_obj
{
	float				reflect;
	int					type;
	float				radius;
	t_pos				object_pos;
	t_color				color;
	int					obj_size;
	float				specular;
}						t_obj;

typedef	struct			s_params
{
	t_ray				O;
	t_ray				D;
	t_ray				camera_rot;
	int					color;
	float				t_min;
	float				t_max;
	int					objects;
	int					lights;
	t_obj				*object;
	t_light				*light;
	t_cam				look_pos;
	int					width;
	int					height;
}						t_params;


typedef	struct			s_privat
{
	cl_command_queue	queue;
	cl_mem				img;
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
}						t_private;

typedef	struct			s_src
{
	SDL_Window			*wind;
	SDL_Surface			*surf;
	unsigned int		*img_pxl;
	int					objects_cnt;
	t_obj				*objects;
	t_light				light;
	t_cam				camera;
	t_private			op_cl;
	t_params			params;
}						t_src;




void		kernel_function(t_src *src);
void		create_videohost(t_src *src);



void					init_parametrs(t_src *src);
int						cnt_objects(char *params, t_src *src);
void					check_nbrs_object(char *av, t_src *src, int size);

t_pos					get_position_object(char *cord, t_pos position);
t_obj					*get_object_params(char *cord, t_obj *object);
void					read_from_file(char *data, t_src *s);
void					error_manadge(char *str, int flag, char *src);
int						get_size(char *av);
void					get_parameters(char *str, t_src *src);

void					init_host(t_src *src);
int						expose_hook(t_src *src);
void					validate_data(char *source, t_src *src);

int						get_data_values(char *data, t_src *src);
void					get_camera_position(char *cord, t_src *src);
void					get_spotlights_params(char *params, t_src *src, int index);
int						check_adecvate(int l, t_pos *p, int fl, char *f, t_color *s);
int						kostyl(char *s, int chr, int index);

#endif

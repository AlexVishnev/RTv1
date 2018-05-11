/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:44:26 by avishnev          #+#    #+#             */
/*   Updated: 2018/04/14 12:45:13 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <time.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <math.h>
# include "libft.h"
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
# define MSG_PARSE "Error: You argunent are shit"
# define MSG_FORMAT "Error: invalid format of data"
# define MSG_PARAMS "Error: invalid params"
# define MSG_CAM "Error: invalid camera position"
# define MSG_RULES "Rerspect rules!  "
# define DICK 42


typedef	struct		s_pos
{
	int		x;
	int		y;
	int		z;
}					t_pos;

typedef	struct		s_ligth
{
	t_pos	**l_pos;
}					t_ligth;

typedef	struct		s_color
{
	int		red;
	int		green;
	int		blue;
}					t_color;

typedef	struct		s_obj
{
	int		obj_type;
	int		radius;
	t_pos	object_pos;
}					t_obj;

typedef	struct		s_cam
{
	t_pos	cam_pos;
}					t_cam;

typedef	struct	s_src
{
	SDL_Window		*wind;
	SDL_Surface		*surf;
	unsigned int	*img_pxl;

	t_obj		*object;
	t_ligth 	ligth;
	t_cam 		camera;
}				t_src;


void			read_from_file(char *data, t_src *s);
void			error_manadge(char *str, int flag, char *src);
int				get_size(char *av);
void			get_parameters(char *str, t_src *src);

void			init_host(t_src *src);
int				expose_hook(t_src *src);
void			validate_data(char *source, t_src *src);

int				get_data_values(char *data, t_src *src);
void			get_camera_position(char *cord, t_src *src);
void			get_spotlights_params(char *params, t_src *src);
void			check_adecvate(int limit, t_pos *p, int flag, char *free);

#endif

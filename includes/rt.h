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

#ifndef RT_H
# define RT_H

# include <time.h>
# include "libft/includes/libft.h"
# include <fcntl.h>
# include "rtv_shared_types.h"

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
# define MSG "\033[0;92m\033[3mUsage:\033[0m ./RT scene/scene_file"
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

# include "parser_external.h"

void				wr_data(Uint8 d[], Uint8 m[], const char *z[], t_src *s);
SDL_Cursor			*init_system_cursor(const char *image[], t_src *src);

void				init_host(t_src *src);
void				init_parametrs(t_src *src);
void				opencl_kernel_run(t_src *src);
void				create_videohost(t_src *src);
void				compile_kernels(t_src *src, cl_int check, size_t size);
void				debugger(t_src *src);

int					expose_hook(t_src *src);

void				keyboards_control1(t_src *src, SDL_Scancode scancode);
void				keyboards_control2(t_src *src, SDL_Scancode scancode);
void				keyboards_control(t_src *src, SDL_Scancode scancode);
void				mouse_control(t_src *src, SDL_Event e_k);
void				take_screenshot(t_src *src, const char *pathfile);

void				error_manadge(char *str, int flag, char *src);
void				print_error_and_exit(const char *erorr_msg, int exit_stat);

#endif

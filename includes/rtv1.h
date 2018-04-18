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

# include <fcntl.h>
# include "SDL2/SDL.h"
# include <math.h>
# include "libft.h"
# define WIN_WD 1080
# define WIN_HG 720



typedef struct	s_ligth
{
	float	x;
	float	y;
	float	z;
}				t_ligth;

typedef	struct	s_obj
{
	int		x;
	int		y;	
}				t_obj;

typedef	struct	s_src
{

	t_obj		*object;
	t_ligth 	*ligth;
	
}				t_src;

typedef	struct	s_cam
{
	
}				t_cam;

void		read_from_file(char *tmp, t_src *s);
void		error_manadge(char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 20:36:39 by avishnev          #+#    #+#             */
/*   Updated: 2018/05/23 20:36:40 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		check_nbrs_object(char *av, t_src *src, int size)
{
	int		fd;
	int		i;
	char	**params;

	i = 0;
	fd = open(av, O_RDONLY);
	if (read(fd, av, 0))
	{
		close(fd);
		error_manadge(MSG_PARSE, 0, NULL);
	}
	src->objects_cnt = 0;
	src->lights_cnt = 0;
	params = (char **)ft_memalloc(sizeof(char*) * size + 1);
	while (ft_getline(fd, &(params[i])))
	{
		cnt_objects(params[i], src);
		free(params[i]);
		i++;
	}
	if (src->objects_cnt == 0)
		error_manadge(MSG_OBJECT, 0, av);
	free(params);
	close(fd);
}

int			kostyl(char *s, int chr, int index)
{
	int		i;

	i = 0;
	while (index != 0)
	{
		while (s[i] && s[i] != chr)
			i++;
		if (s[i] == chr)
		{
			index--;
			i++;
		}
		else if (s[i] == '\0' && index != 0)
			break ;
	}
	return (i);
}

int			cnt_objects(char *str, t_src *src)
{
	int		c;
	char	*lox;

	c = -2;
	if (str[0] == '#' || str[0] == '\0' || str[0] == ' '
		|| str[0] == '\t' || str[0] == '\b')
		return (c);
	c = 0;
	lox = ft_strsub(str, 2, 6);
	if (ft_strcmp(lox, "object") == 0)
	{
		src->objects_cnt++;
		free(lox);
		return (1);
	}
	if (ft_strcmp(lox, "slight") == 0)
	{
		src->lights_cnt++;
		free(lox);
		return (1);
	}
	free(lox);
	return (-2);
}

int			brackects_valide(char *s)
{
	int			i;
	int			len;
	int			op;
	int			cl;

	op = 0;
	cl = 0;
	i = 0;
	len = ft_strlen(s) - 1;
	if (s[0] == '}' || s[0] == ')' || s[0] == ']')
		return (1);
	else if (s[len] == '[' || s[len] == '(' || s[len] == '{')
		return (1);
	while (s[i])
	{
		if (s[i] == '}' || s[i] == ')' || s[i] == ']')
			cl++;
		else if (s[i] == '{' || s[i] == '(' || s[i] == '[')
			op++;
		i++;
	}
	if (br_adecvat(s) == 1)
		return (1);
	return (op == cl ? 0 : 1);
}

int			brackects(char *s)
{
	int		i;
	int		cnt;
	char	stack[2048];

	cnt = 0;
	i = 0;
	while (i < 2048)
		stack[i++] = '\0';
	i = 0;
	while (s[i])
	{
		if (s[i] == '[' || s[i] == ']' || s[i] == '(' || s[i] == ')'
				|| s[i] == '{' || s[i] == '}')
		{
			stack[cnt] = s[i];
			cnt++;
		}
		i++;
	}
	if (brackects_valide(stack) == 0)
		return (1);
	return (0);
}

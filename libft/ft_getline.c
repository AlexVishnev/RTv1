/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:12:29 by avishnev          #+#    #+#             */
/*   Updated: 2018/01/17 14:22:26 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	t_gnl			*fill_list(t_list **list, const int fd)
{
	t_list			*new_list_elem;
	t_gnl			*data;

	new_list_elem = *list;
	while (new_list_elem)
	{
		if (((t_gnl *)new_list_elem->content)->fd == fd)
			return ((t_gnl *)new_list_elem->content);
		new_list_elem = new_list_elem->next;
	}
	if (!(data = (t_gnl *)ft_memalloc(sizeof(t_gnl *))))
		return (NULL);
	data->buf = ft_strnew(BUFF_SIZE);
	data->fd = fd;
	data->start = 0;
	new_list_elem = ft_lstnew(data, sizeof(t_gnl));
	ft_lstadd(list, new_list_elem);
	free(data);
	return ((t_gnl *)new_list_elem->content);
}

static	char			**merge_lines(char **line, char *buffer)
{
	char			*tmp;

	tmp = ft_strjoin(*line, buffer);
	ft_memdel((void *)line);
	*line = ft_memalloc(ft_strlen(tmp));
	ft_strcpy(*line, tmp);
	ft_memset(buffer, '\0', ft_strlen(buffer));
	ft_memdel((void *)&tmp);
	return (line);
}

static	int				seek_and_destroy(t_gnl **p, char *string)
{
	char *tmp;

	tmp = NULL;
	if (string)
		tmp = ft_strdup(string + 1);
	else
		tmp = ft_strdup("");
	ft_memset((*p)->buf, '\0', ft_strlen((*p)->buf));
	ft_memcpy((*p)->buf, tmp, ft_strlen(tmp));
	ft_memdel((void *)&tmp);
	return (1);
}

static	int				get_line(t_gnl **p, char **line)
{
	char			*str;
	char			*tmp;
	int				ret;

	ret = 1;
	tmp = NULL;
	while (!(str = ft_memchr((*p)->buf, '\n', ft_strlen((*p)->buf))) && ret > 0)
	{
		merge_lines(line, (*p)->buf);
		ret = read((*p)->fd, (*p)->buf, BUFF_SIZE);
		if (ret < 1 && !(**line))
			return (ret);
	}
	if ((str && !(tmp = ft_strsub((*p)->buf, (*p)->start, str - (*p)->buf)))
	|| (str && !(line = merge_lines(line, tmp))))
		return (-1);
	ft_memdel((void *)&tmp);
	if (!(seek_and_destroy(p, str)))
		return (-1);
	return (1);
}

int						ft_getline(const int fd, char **line)
{
	static t_list	*list;
	t_gnl			*tmp;
	int				ret;

	if (BUFF_SIZE < 1 || fd < 0)
		return (-1);
	if (!line || !(tmp = fill_list(&list, fd)))
		return (-1);
	*line = ft_strdup("");
	if ((ret = get_line(&tmp, line)) < 1)
		ft_memdel((void *)line);
	return (ret);
}

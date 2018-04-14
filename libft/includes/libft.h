/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avishnev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:31:05 by avishnev          #+#    #+#             */
/*   Updated: 2018/04/14 19:59:41 by avishnev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			*ft_strrev(char *str);
char			*ft_strnchr(const char *str, int c, int len);
char			*ft_delchr(char *s, char c);
char			*ft_strpbrk(const char *s1, const char *s2);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striter(char *s, void (*f)(char *));
void			*ft_memset(void *dest, int c, size_t len);
void			ft_bzero(void *dest, size_t len);
void			*ft_memcpy(void *restrict d, const void *restrict s, size_t n);
void			*ft_memccpy(void *d, const void *s, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *app, size_t n);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putchar(char c);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int				rgb_converce(int r, int g, int b);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *str1, const char *str2);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isdigits(char *s);
int				ft_isprint(int c);
char			ft_iswhitesp(char c);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strrchr(const char *str, int c);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *str1, const char *str2, size_t len);
char			*ft_itoa(int n);
char			*ft_strstr(const char *str1, const char *str2);
char			*ft_strchr(const char *str, int c);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *str, char split);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
#endif

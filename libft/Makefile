# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avishnev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 15:52:45 by avishnev          #+#    #+#              #
#    Updated: 2018/06/17 11:44:18 by avishnev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -c
FILES = ft_atoi \
		ft_atoi_base \
		ft_getline \
		ft_bzero \
		ft_isalpha \
		ft_isdigit \
		ft_isprint \
		ft_iswhitesp \
		ft_itoa \
		ft_lstnew \
		ft_lstdelone \
		ft_lstdel \
		ft_lstadd \
		ft_lstiter \
		ft_lstmap \
		ft_memset \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_memalloc \
		ft_memdel \
		ft_putchar \
		ft_putchar_fd \
		ft_putendl \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putnbr \
		ft_putstr \
		ft_putstr_fd \
		ft_strlen \
		ft_toupper \
		ft_tolower \
		ft_split_arr \
		ft_strdup \
		ft_strcpy \
		ft_strncpy \
		ft_strcat \
		ft_strncat \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strstr \
		ft_strnstr \
		ft_strcmp \
		ft_strncmp \
		ft_strnew \
		ft_strdel \
		ft_strclr \
		ft_striter \
		ft_striteri \
		ft_strmap \
		ft_strmapi \
		ft_strequ \
		ft_strnequ \
		ft_strsub \
		ft_strjoin \
		ft_strtrim \
		ft_strsplit \
		ft_delchr \
		ft_isalnum \
		ft_strrev \
		ft_strpjoin \
		ft_strpbrk \

HEAD = -I./includes
CC = clang

OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_F = $(addsuffix .o, $(FILES))

all: $(NAME)
	@if [ ! -d obj ] ; then mkdir obj; fi
$(NAME):$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[0;32m[ ✔ ] Library created!\033[0m"
obj/%.o: %.c
	@$(CC) -o $@ $(FLAGS) $(HEAD) -c $^
clean:
	@rm -f $(OBJ)
	@echo "\033[31m[ ✔ ] Cleaning succesed [ ✔ ] \033[33m(lib) \033[0m"
fclean: clean
	@rm -f $(NAME)
	@echo  "\033[0;31mFile \033[0;33m$(NAME) \033[0;31mremoved\033[0m"
re: fclean all

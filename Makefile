# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avishnev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 12:41:56 by avishnev          #+#    #+#              #
#    Updated: 2018/04/14 12:43:00 by avishnev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
FILES = main
LIB_D_FT = libft/
SRC = $(addprefix scr/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))

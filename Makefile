# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avishnev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 12:41:56 by avishnev          #+#    #+#              #
#    Updated: 2018/04/18 13:26:39 by avishnev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
FILES = main rt_read_file rt_init rt_parser rt_errors rt_tools
LIBA = libft/libft.a
LIB_D_FT = libft/
SRC = $(addprefix scr/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
FLAGS = 
HEADER = -I./includes -I./libft/includes
HED = ./includes/rtv1.h
MK_LIB = --no-print-directory -j3 -C
OS = $(shell uname)
ifeq ($(OS), Linux)
CGFLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_tff -lm
else
CGFLAGS = -lmlx -framework OpenGL -framework AppKit
INC	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer
endif

all: $(NAME)

$(NAME): $(LIBA) $(OBJ) $(HED)
	@$(CC) -o $(NAME) -O3 $(OBJ) $(CGFLAGS) $(FRWORKS) $(LIBA)
	@echo "\033[31mS------U=====K>>>>>S}}}}}}E++++E>>>>>>>S"
$(LIBA):
	@make $(MK_LIB) $(LIB_D_FT)
$(OBJ): obj/%.o: src/%.c $(HED)
	@$(CC) -o $@ $(HEADER) $(INC) -c $<
clean:
	@rm -f $(OBJ)
	@make $(MK_LIB) $(LIB_D_FT) clean
fclean: 
	 @rm -rf $(OBJ)
	 @rm -f $(NAME)
	 @make $(MK_LIB) $(LIB_D_FT) fclean
re: fclean all
	

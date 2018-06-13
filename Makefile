# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avishnev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 12:41:56 by avishnev          #+#    #+#              #
#    Updated: 2018/06/10 15:38:51 by avishnev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
FILES = main rt_read_file rt_init rt_parser rt_errors rt_tools rt_kernels rt_controllers rt_parser1
LIBA = libft/libft.a
LIB_DIR = libft/
SRC = $(addprefix scr/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_LIST = $(addsuffix .o, $(FILES))
HEADER = -I./includes -I./libft/includes
HED = ./includes/rtv1.h
MK_LIB = --no-print-directory -j3 -C
SOURCE_FILES = scene/scene.1-10
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
FRAMES	=	-F./frameworks \
			-rpath ./frameworks \
			-framework OpenGL -framework AppKit -framework OpenCl \
			-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
			-framework SDL2_mixer
endif

all: $(NAME)

$(NAME): $(LIBA) $(OBJ) $(HED)
	@$(CC) -o $(NAME) -O3 $(OBJ) $(CGFLAGS) $(FRAMES) $(LIBA)
	@echo "USAGE: \033[0;92m\033[3m ./$(NAME) $(SOURCE_FILES)\033[0m"
	@echo "ATTENTION: \033[4;31m\033[42mDO NOT PRESS 'H' WHEN BINARY RUNNING\033[0m"
$(LIBA):
	@make $(MK_LIB) $(LIB_DIR)
$(OBJ): obj/%.o: src/%.c $(HED)
	@$(CC) -o $@ $(HEADER) $(INC) -c $<
	@echo "\033[37mTrying to compile \033[4;33m\033[41m$(notdir $<)\033[0m file \033[0m\033[37m\n\033[0;92m \033[3m   <<<<-Success->>>> \033[0m"
norm:
	@norminette src/*.c
	@norminette includes/*.h
clean:
	@rm -f $(OBJ)
	@make $(MK_LIB) $(LIB_DIR) clean
fclean: 
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@make $(MK_LIB) $(LIB_DIR) fclean
re: fclean all
	

NAME = RT

RM = /bin/rm
MKDIR = /bin/mkdir
PRINTF = /usr/bin/printf
ECHO = /bin/echo

PREFIX=$(PWD)/build
DEP_DIR=$(PWD)/downloads
THIS_DIR=$(PWD)

LIBNAME = ft
LIBDIR = ./libft

INCLUDE_DIR = ./includes
SOURCES_DIR = ./src
OBJECTS_DIR = ./obj

SOURCES = rt_parser1.c \
			rt_controllers.c \
			rt_kernels.c \
			main.c \
			rt_init.c \
			rt_parser.c \
			rt_errors.c \
			rt_tools.c \
			rt_read_file.c \
			parser/parse_main.c \
			parser/parse_generic.c \
			parser/parse_specific.c \
			parser/parse_validate.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_DIR)/, $(SOURCES))

CC = clang
AR = ar
CFLAGS = -Wall -Werror -Wextra

# Colors
NO_COLOR = \033[0;00m
OK_COLOR = \033[38;5;02m
ERROR_COLOR = \033[38;5;01m
WARN_COLOR = \033[38;5;03m
SILENT_COLOR = \033[38;5;04m

IFLAGS = -I. -I$(INCLUDE_DIR) \
		 -I$(PREFIX)/include

LFLAGS = \
		-L$(LIBDIR) -lft \
		-L./cJSON/build \
		-L$(PREFIX)/lib -lSDL2 -lSDL2_ttf -lSDL2_image  -lcjson.1.7.7 \
		-framework OpenGL -framework AppKit -framework OpenCL

.PHONY: all download clean fclean re sdl2 install_dependencies update\
				sdl2_download sdl2_image_download sdl2_ttf_download \
				sdl2_install sdl2_image_install sdl2_ttf_install \
				sdl2_clean sdl2_image_clean sdl2_ttf_clean cjson

all: $(NAME)

$(NAME): install_dependencies $(LIBNAME) $(OBJECTS)
	@$(PRINTF) "$(SILENT_COLOR)./$(NAME) binary$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(FFLAGS) $(IFLAGS) $(LFLAGS) -o $(NAME) $(OBJECTS)
	@$(PRINTF)	"\t[$(OK_COLOR)✓$(NO_COLOR)]$(NO_COLOR)\n"

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	@mkdir -p $(OBJECTS_DIR)/sdl2 $(OBJECTS_DIR)/scenes $(OBJECTS_DIR)/objects
	@mkdir -p $(OBJECTS_DIR)/parser 
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
	@$(PRINTF) "$(OK_COLOR)✓ $(NO_COLOR)$<\n"

platforms:
	@$(CC) -framework OpenCL -o $@ -c $@.c
	@$(PRINTF) "$(OK_COLOR)✓ $(NO_COLOR)$@.c\n"

devices:
	@$(CC) -framework OpenCL -o $@ -c $@.c
	@$(PRINTF) "$(OK_COLOR)✓ $(NO_COLOR)$@.c\n"

$(LIBNAME):
	@make -C $(LIBDIR)

cjson:
	@mkdir -p $(DEP_DIR)
	@git submodule init;
	@git submodule update;
	@if [ ! -d "cJSON/build/" ]; then mkdir -p "cJSON/build"; fi;
	@if [ ! -f "$(PREFIX)/lib/libcjson.dylib" ]; then \
		cd cJSON/build/ && cmake .. -DCMAKE_INSTALL_PREFIX=$(PWD)/build && make install; \
	fi


sdl2_download:
	@mkdir -p $(DEP_DIR)
	@if [ ! -f $(PREFIX)/lib/libSDL2.a ] && [ ! -d $(DEP_DIR)/SDL2 ]; then \
		if [ ! -f $(DEP_DIR)/SDL2.zip ]; then \
			curl -o $(DEP_DIR)/SDL2.zip https://www.libsdl.org/release/SDL2-2.0.8.zip; \
		fi ;\
		unzip $(DEP_DIR)/SDL2.zip -d $(DEP_DIR); \
		mv $(DEP_DIR)/SDL2-2.0.8 $(DEP_DIR)/SDL2; \
		rm -rf $(DEP_DIR)/SDL2.zip; \
	fi

sdl2_image_download:
	@mkdir -p $(DEP_DIR)
	@if [ ! -f $(PREFIX)/lib/libSDL2_image.a ] && [ ! -d $(DEP_DIR)/SDL2_image ]; then \
		if [ ! -f $(DEP_DIR)/SDL2_image.zip ]; then \
			curl -o $(DEP_DIR)/SDL2_image.zip https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.zip; \
		fi ;\
		unzip $(DEP_DIR)/SDL2_image.zip -d $(DEP_DIR); \
		mv $(DEP_DIR)/SDL2_image-2.0.3 $(DEP_DIR)/SDL2_image; \
		rm -rf $(DEP_DIR)/SDL2_image.zip; \
	fi

sdl2_ttf_download:
	@mkdir -p $(DEP_DIR)
	@if [ ! -f $(PREFIX)/lib/libSDL2_ttf.a ] && [ ! -d $(DEP_DIR)/SDL2_ttf ]; then \
		if [ ! -f $(DEP_DIR)/SDL2_ttf.zip ]; then \
			curl -o $(DEP_DIR)/SDL2_ttf.zip https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.zip; \
		fi ;\
		unzip $(DEP_DIR)/SDL2_ttf.zip -d $(DEP_DIR); \
		mv $(DEP_DIR)/SDL2_ttf-2.0.14 $(DEP_DIR)/SDL2_ttf; \
		rm -rf $(DEP_DIR)/SDL2_ttf.zip; \
	fi

sdl2_install: sdl2_download
	@mkdir -p $(PREFIX)
	@if [ ! -f $(PREFIX)/lib/libSDL2.a ]; then \
		cd $(DEP_DIR)/SDL2; \
		./configure --prefix=$(PREFIX) ; \
		cd $(THIS_DIR); \
		make -C $(DEP_DIR)/SDL2; \
		make -C $(DEP_DIR)/SDL2 install; \
	fi

sdl2_image_install: sdl2_image_download
	@mkdir -p $(PREFIX)
	@if [ ! -f $(PREFIX)/lib/libSDL2_image.a ]; then \
		cd $(DEP_DIR)/SDL2_image; \
		./configure --prefix=$(PREFIX) ; \
		cd $(THIS_DIR); \
		make -C $(DEP_DIR)/SDL2_image; \
		make -C $(DEP_DIR)/SDL2_image install; \
	fi


sdl2_ttf_install: sdl2_ttf_download
	@mkdir -p $(PREFIX)
	@if [ ! -f $(PREFIX)/lib/libSDL2_ttf.a ]; then \
		cd $(DEP_DIR)/SDL2_ttf; \
		./configure --prefix=$(PREFIX) ; \
		cd $(THIS_DIR); \
		make -C $(DEP_DIR)/SDL2_ttf; \
		make -C $(DEP_DIR)/SDL2_ttf install; \
	fi

download: sdl2_download sdl2_image_download sdl2_ttf_download

install_dependencies: download sdl2_install sdl2_image_install sdl2_ttf_install cjson

clean_proj:
	@$(MAKE) -C $(LIBDIR) clean
	@$(RM) -rf $(OBJECTS)
	@$(RM) -rf $(OBJECTS_DIR)

fclean_proj: clean_proj
	@$(MAKE) -C $(LIBDIR) fclean
	@$(RM) -rf $(NAME)

update: fclean_proj all

norm: 
	@norminette src/*.c
	@norminette includes/*.h

cjson_clean:
	@if [ -f cJSON/build/Makefile ]; then $(MAKE) -C cJSON/build clean; fi;

sdl2_clean:
	@if [ -d $(DEP_DIR)/SDL2 ]; then \
		$(MAKE) -C $(DEP_DIR)/SDL2 clean; \
	fi

sdl2_image_clean:
	@if [ -d $(DEP_DIR)/SDL2_image ]; then \
		$(MAKE) -C $(DEP_DIR)/SDL2_image clean; \
	fi

sdl2_ttf_clean:
	@if [ -d $(DEP_DIR)/SDL2_ttf ]; then \
		$(MAKE) -C $(DEP_DIR)/SDL2_ttf clean; \
	fi

clean: sdl2_clean sdl2_image_clean sdl2_ttf_clean cjson_clean clean_proj

fclean: clean fclean_proj
	@$(RM) -rf $(PREFIX)
	@$(RM) -rf $(DEP_DIR)
	@git submodule deinit --all -f

re: fclean all

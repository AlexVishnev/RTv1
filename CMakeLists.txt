cmake_minimum_required(VERSION 3.8)
project(RTv1)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES src/main.c
				src/rt_controllers.c
				src/rt_errors.c
				src/rt_init.c
				src/rt_kernels.c
				src/rt_parser.c
				src/rt_parser1.c
				src/rt_read_file.c
				src/rt_tools.c)

set(LIBFT_SOURCES libft/ft_strncat.c
	libft/ft_split_arr.c
	libft/ft_strnstr.c
	libft/ft_iswhitesp.c
	libft/ft_lstadd.c
	libft/ft_isdigit.c
	libft/ft_putstr_fd.c
	libft/ft_strequ.c
	libft/ft_lstnew.c
	libft/ft_strlen.c
	libft/ft_strnchr.c
	libft/ft_memcmp.c
	libft/ft_putnbr.c
	libft/ft_strclr.c
	libft/ft_itoa_base.c
	libft/ft_strsplit.c
	libft/ft_putnbr_fd.c
	libft/ft_lstiter.c
	libft/ft_strchr.c
	libft/ft_strpjoin.c
	libft/ft_striteri.c
	libft/ft_bzero.c
	libft/ft_strjoin.c
	libft/ft_isascii.c
	libft/ft_delchr.c
	libft/ft_memcpy.c
	libft/ft_strstr.c
	libft/ft_memalloc.c
	libft/ft_putendl.c
	libft/ft_memccpy.c
	libft/ft_strcat.c
	libft/ft_isprint.c
	libft/ft_putendl_fd.c
	libft/ft_strdel.c
	libft/ft_lstmap.c
	libft/ft_strpbrk.c
	libft/ft_strnequ.c
	libft/ft_toupper.c
	libft/ft_putchar.c
	libft/ft_strrchr.c
	libft/ft_isalpha.c
	libft/ft_memchr.c
	libft/ft_strmap.c
	libft/ft_putchar_fd.c
	libft/ft_memset.c
	libft/ft_lstdel.c
	libft/ft_strncmp.c
	libft/ft_strcpy.c
	libft/ft_strmapi.c
	libft/ft_strtrim.c
	libft/ft_memdel.c
	libft/ft_memmove.c
	libft/ft_rgb.c
	libft/ft_strnew.c
	libft/ft_putstr.c
	libft/ft_strlcat.c
	libft/ft_strrev.c
	libft/ft_atoi_base.c
	libft/ft_strdup.c
	libft/ft_atoi.c
	libft/ft_isalnum.c
	libft/ft_lstdelone.c
	libft/ft_itoa.c
	libft/ft_striter.c
	libft/ft_getline.c
	libft/ft_strsub.c
	libft/ft_strncpy.c
	libft/ft_tolower.c
	libft/ft_strcmp.c
	)

if (APPLE)
	message(STATUS "MacOS")
	message(STATUS "${CMAKE_MODULE_PATH}")
	message(STATUS "$ENV{HOME}")
	find_package(OpenCL REQUIRED)
	message(STATUS "OpenCL found: ${OpenCL_FOUND}")
	message(STATUS "OpenCL includes: ${OpenCL_INCLUDE_DIRS}")
	message(STATUS "OpenCL CXX includes: ${OpenCL_HAS_CPP_BINDINGS}")
	message(STATUS "OpenCL libraries: ${OpenCL_LIBRARIES}")
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
	link_directories("${CMAKE_SOURCE_DIR}/build/lib")
	include_directories("${CMAKE_SOURCE_DIR}/build/include")
	set(SDL2_LIBRARIES SDL2 SDL2_ttf SDL2_image)
	message(STATUS "${SDL2_LIBRARIES}")
else()
	message(STATUS "LINUX")
	find_package(SDL2 REQUIRED)
	add_library(OpenCL SHARED IMPORTED)
	set_property(TARGET OpenCL PROPERTY IMPORTED_LOCATION
		"/usr/lib/x86_64-linux-gnu/libOpenCL.so.1")
	set(OpenCL_LIBRARIES OpenCL)
endif()

add_library(ft ${LIBFT_SOURCES})

add_executable(RTv1 ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} libft/includes includes)

target_link_libraries(RTv1 ${SDL2_LIBRARIES} ${OpenCL_LIBRARIES} ft m)

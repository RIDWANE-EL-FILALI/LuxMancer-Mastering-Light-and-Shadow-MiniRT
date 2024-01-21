NAME = MiniRT.a
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -lmlx -framework appkit -framework openGl
RM = rm -f
SRC = bmp_creater.c   color.c   cylinder_intersection.c     main.c   multi_threading.c           ray_tracing.c   sample_pixel.c  supersampel.c \
camera.c  cube_pyramid_intersection.c light.c   mlx_things.c    plane_intersection.c        reflect_and_refract.c       sphere_intersection.c  textures.c \
	parsing/parse.c        parsing/parse2.c       parsing/parse3.c       parsing/parse4.c       parsing/parse_utils.c  parsing/parse_utils2.c \
	vectors/vectors.c  vectors/vectors2.c vectors/vectors3.c \
	libft/ft_atoi.c         libft/ft_isalnum.c      libft/ft_isdigit.c      libft/ft_lstadd_back.c  libft/ft_lstdelone.c    libft/ft_lstmap.c  \
	libft/ft_memchr.c       libft/ft_memmove.c      libft/ft_putendl_fd.c   libft/ft_split.c        libft/ft_striteri.c     libft/ft_strlcpy.c  \
	libft/ft_strncmp.c      libft/ft_strtrim.c      libft/ft_toupper.c \
	libft/ft_bzero.c        libft/ft_isalpha.c      libft/ft_isprint.c      libft/ft_lstadd_front.c libft/ft_lstiter.c      libft/ft_lstnew.c  \
	libft/ft_memcmp.c       libft/ft_memset.c       libft/ft_putnbr_fd.c    libft/ft_strchr.c       libft/ft_strjoin.c      libft/ft_strlen.c    \
	libft/ft_strnstr.c      libft/ft_substr.c \
	libft/ft_calloc.c       libft/ft_isascii.c      libft/ft_itoa.c         libft/ft_lstclear.c     libft/ft_lstlast.c      libft/ft_lstsize.c    \
	libft/ft_memcpy.c       libft/ft_putchar_fd.c   libft/ft_putstr_fd.c    libft/ft_strdup.c       libft/ft_strlcat.c      libft/ft_strmapi.c  \
	libft/ft_strrchr.c      libft/ft_tolower.c 	libft/ft_strcat.c libft/ft_strcmp.c libft/ft_strncpy.c

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ) ggl_mlx_define.h main.h libft/libft.h
	@ar rc $(NAME) $(OBJ)
	@${CC} ${FRAMEWORK} ${CFLAGS} ${NAME} -o MiniRT

clean :
	${RM} ${OBJ} ${NAME}

fclean : clean
	${RM} MiniRT
re : fclean all

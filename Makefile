NAME = MiniRT.a
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -lmlx -framework appkit -framework openGl
RM = rm -f

LIBFT = libft/ft_atoi.c         libft/ft_isalnum.c      libft/ft_isdigit.c      libft/ft_lstadd_back.c  libft/ft_lstdelone.c    libft/ft_lstmap.c  \
	libft/ft_memchr.c       libft/ft_memmove.c      libft/ft_putendl_fd.c   libft/ft_split.c        libft/ft_striteri.c     libft/ft_strlcpy.c  \
	libft/ft_strncmp.c      libft/ft_strtrim.c      libft/ft_toupper.c \
	libft/ft_bzero.c        libft/ft_isalpha.c      libft/ft_isprint.c      libft/ft_lstadd_front.c libft/ft_lstiter.c      libft/ft_lstnew.c  \
	libft/ft_memcmp.c       libft/ft_memset.c       libft/ft_putnbr_fd.c    libft/ft_strchr.c       libft/ft_strjoin.c      libft/ft_strlen.c    \
	libft/ft_strnstr.c      libft/ft_substr.c \
	libft/ft_calloc.c       libft/ft_isascii.c      libft/ft_itoa.c         libft/ft_lstclear.c     libft/ft_lstlast.c      libft/ft_lstsize.c    \
	libft/ft_memcpy.c       libft/ft_putchar_fd.c   libft/ft_putstr_fd.c    libft/ft_strdup.c       libft/ft_strlcat.c      libft/ft_strmapi.c  \
	libft/ft_strrchr.c      libft/ft_tolower.c 	libft/ft_strcat.c libft/ft_strcmp.c libft/ft_strncpy.c\


VECT = vectors/vectors.c  vectors/vectors2.c vectors/vectors3.c

SRC =  manda/ray_tracing_manda_norm.c         manda/light.c                      manda/parsing3_manda.c    \
	  manda/camera.c                               manda/parsing_mandatory.c          manda/sample_pixel.c \
	  manda/color.c                      manda/main_mandatory.c             manda/parsing_mandatory_norm.c     manda/sphere_intersection.c \
	  manda/cylinder_intersection.c      manda/mlx_things.c                 manda/plane_intersection.c         manda/supersampel.c \
	  manda/cylinder_intersection_norm.c manda/multi_threading.c            manda/ray_tracing_manda.c         \
	  parsing/parse2.c       parsing/parse3.c        parsing/parse_utils.c  parsing/parse_utils2.c

SRCB =  bonus/bmp_creater.c                bonus/cylinder_intersection_norm.c bonus/plane_intersection.c         bonus/sphere_intersection.c \
		bonus/bmp_creater_norm.c           bonus/light.c                      bonus/ray_tracing.c                bonus/supersampel.c \
		bonus/camera.c                     bonus/main.c                       bonus/textures.c bonus/color.c \
		bonus/mlx_things.c                 bonus/reflect_and_refract.c \
		bonus/cylinder_intersection.c      bonus/multi_threading.c            bonus/sample_pixel.c  bonus/ray_tracing_norm.c\
		parsing/parse.c        parsing/parse2.c       parsing/parse3.c          parsing/parse_utils.c  parsing/parse_utils2.c

LIBFTOBJ = $(LIBFT:.c=.o)

OBJ = ${SRC:.c=.o}

OBJB = ${SRCB:.c=.o}

OBJVECT = ${VECT:.c=.o}

all : $(NAME)

$(NAME) : ${LIBFTOBJ} $(OBJ) $(OBJVECT) manda/main.h libft/libft.h
	@ar rc $(NAME) $(OBJ) ${LIBFTOBJ} $(OBJVECT)
	@${CC} ${FRAMEWORK} ${CFLAGS} ${NAME} -o MiniRT

bonus : ${LIBFTOBJ} $(OBJB) $(OBJVECT) bonus/main.h  bonus/objects.h libft/libft.h
	@ar rc $(NAME) $(OBJB) ${LIBFTOBJ} $(OBJVECT) $(OBJPARS)
	@${CC} ${FRAMEWORK} ${CFLAGS} ${NAME} -o MiniRT_bonus

clean :
	${RM} ${OBJ} ${OBJB} ${LIBFTOBJ} $(OBJVECT) ${NAME}

fclean : clean
	${RM} MiniRT MiniRT_bonus

re : fclean all

NAME = MiniRT
NAMEB = MiniRT_bonus
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -lmlx -framework appkit -framework openGl
RM = rm -f


PATH_SRC = ./
PATH_OBJ = ./obj/
PATH_OBJB = ./obj_bonus/

# for vect
PATH_VECT = ./vectors/
FILE_VECT_c = vectors.c  vectors2.c vectors3.c

PATH_VECT_OBJ = $(PATH_OBJ)vectors/
FILE_VECT_OBJ = $(FILE_VECT_c:.c=.o)
VECT_OBJ = $(addprefix $(PATH_VECT_OBJ), $(FILE_VECT_OBJ))

#for libft 
PATH_LIBFT = ./libft/
FILE_LIBFT_c = ft_atoi.c         ft_isalnum.c      ft_isdigit.c      ft_lstadd_back.c  ft_lstdelone.c    ft_lstmap.c  \
	ft_memchr.c       ft_memmove.c      ft_putendl_fd.c   ft_split.c        ft_striteri.c     ft_strlcpy.c  \
	ft_strncmp.c      ft_strtrim.c      ft_toupper.c \
	ft_bzero.c        ft_isalpha.c      ft_isprint.c      ft_lstadd_front.c ft_lstiter.c      ft_lstnew.c  \
	ft_memcmp.c       ft_memset.c       ft_putnbr_fd.c    ft_strchr.c       ft_strjoin.c      ft_strlen.c    \
	ft_strnstr.c      ft_substr.c \
	ft_calloc.c       ft_isascii.c      ft_itoa.c         ft_lstclear.c     ft_lstlast.c      ft_lstsize.c    \
	ft_memcpy.c       ft_putchar_fd.c   ft_putstr_fd.c    ft_strdup.c       ft_strlcat.c      ft_strmapi.c  \
	ft_strrchr.c      ft_tolower.c 	ft_strcat.c ft_strcmp.c ft_strncpy.c

PATH_LIBFT_OBJ = $(PATH_OBJ)libft/
FILE_LIBFT_OBJ = $(FILE_LIBFT_c:.c=.o)
LIBFT_OBJ = $(addprefix $(PATH_LIBFT_OBJ), $(FILE_LIBFT_OBJ))

# for parsing 
PATH_PARS = ./parsing/
FILE_PARS_c = parse.c                  parse2.c                 parse3.c             \
    	parse_utils.c            parse_utils2.c           parsing3_manda.c         parsing_mandatory.c     \
	 	parsing_mandatory_norm.c \

PATH_PARS_OBJ = $(PATH_OBJ)parsing/
FILE_PARS_OBJ = $(FILE_PARS_c:.c=.o)
PARS_OBJ = $(addprefix $(PATH_PARS_OBJ), $(FILE_PARS_OBJ))

#FOR MANDA

PATH_MANDA = ./
FILE_MANDA_c = main_mandatory.c \
    color.c   cylinder_intersection.c  cylinder_intersection_norm.c multi_threading.c    ray_tracing.c   sample_pixel.c  supersampel.c \
	camera.c light.c   mlx_things.c    plane_intersection.c        reflect_and_refract.c       sphere_intersection.c  textures.c \
	ray_tracing_manda_norm.c
PATH_MANDA_OBJ = $(PATH_OBJ)
FILE_MANDA_OBJ = $(FILE_MANDA_c:.c=.o)
MANDA_OBJ = $(addprefix $(PATH_MANDA_OBJ), $(FILE_MANDA_OBJ))

ALLOBJ = $(OBJ) $(PARS_OBJ) $(LIBFT_OBJ) $(VECT_OBJ) $(MANDA_OBJ)

HEADERS = ggl_mlx_define.h main.h libft/libft.h

# ------------- bonus ----------

# for vect
PATH_VECTB = ./vectors/
FILE_VECTB_c = vectors.c  vectors2.c vectors3.c

PATH_VECTB_OBJ = $(PATH_OBJB)vectors/
FILE_VECTB_OBJ = $(FILE_VECTB_c:.c=.o)
VECTB_OBJ = $(addprefix $(PATH_VECTB_OBJ), $(FILE_VECTB_OBJ))

#for libft 

PATH_LIBFTB = ./libft/
FILE_LIBFTB_c = ft_atoi.c         ft_isalnum.c      ft_isdigit.c      ft_lstadd_back.c  ft_lstdelone.c    ft_lstmap.c  \
	ft_memchr.c       ft_memmove.c      ft_putendl_fd.c   ft_split.c        ft_striteri.c     ft_strlcpy.c  \
	ft_strncmp.c      ft_strtrim.c      ft_toupper.c \
	ft_bzero.c        ft_isalpha.c      ft_isprint.c      ft_lstadd_front.c ft_lstiter.c      ft_lstnew.c  \
	ft_memcmp.c       ft_memset.c       ft_putnbr_fd.c    ft_strchr.c       ft_strjoin.c      ft_strlen.c    \
	ft_strnstr.c      ft_substr.c \
	ft_calloc.c       ft_isascii.c      ft_itoa.c         ft_lstclear.c     ft_lstlast.c      ft_lstsize.c    \
	ft_memcpy.c       ft_putchar_fd.c   ft_putstr_fd.c    ft_strdup.c       ft_strlcat.c      ft_strmapi.c  \
	ft_strrchr.c      ft_tolower.c 	ft_strcat.c ft_strcmp.c ft_strncpy.c

PATH_LIBFTB_OBJ = $(PATH_OBJB)libft/
FILE_LIBFTB_OBJ = $(FILE_LIBFTB_c:.c=.o)
LIBFTB_OBJ = $(addprefix $(PATH_LIBFTB_OBJ), $(FILE_LIBFTB_OBJ))

# for parsing 

PATH_PARSB = ./parsing/
FILE_PARSB_c = parse.c                  parse2.c                 parse3.c             \
    	parse_utils.c            parse_utils2.c           parsing3_manda.c         parsing_mandatory.c     \
	 	parsing_mandatory_norm.c \

PATH_PARSB_OBJ = $(PATH_OBJB)parsing/
FILE_PARSB_OBJ = $(FILE_PARSB_c:.c=.o)
PARSB_OBJ = $(addprefix $(PATH_PARSB_OBJ), $(FILE_PARSB_OBJ))

#FOR BONUS
PATH_BONUS = ./
FILE_BONUS_c = color.c   cylinder_intersection.c  cylinder_intersection_norm.c   main_bonus.c   multi_threading.c     ray_tracing.c     sample_pixel.c  supersampel.c \
	camera.c  light.c   mlx_things.c    plane_intersection.c        reflect_and_refract.c       sphere_intersection.c  textures.c   ray_tracing_manda_norm.c

PATH_BONUS_OBJ = $(PATH_OBJB)
FILE_BONUS_OBJ = $(FILE_BONUS_c:.c=.o)
BONUS_OBJ = $(addprefix $(PATH_BONUS_OBJ), $(FILE_BONUS_OBJ))

ALLOBJB = $(OBJ) $(PARS_OBJ) $(LIBFT_OBJ) $(VECT_OBJ) $(BONUS_OBJ)

HEADERS = ggl_mlx_define.h main.h libft/libft.h

all : $(NAME)

$(NAME) : $(ALLOBJ) $(HEADERS)
	$(CC) $(ALLOBJ) $(CFLAGS) $(FRAMEWORK) -o $(NAME)

bonus : $(ALLOBJB) $(HEADERS)
	$(CC) $(ALLOBJB) $(CFLAGS) $(FRAMEWORK) -o $(NAMEB)

$(PATH_OBJ)%.o : $(PATH_SRC)%.c $(HEADERS)
	mkdir -p $(PATH_LIBFT_OBJ)
	mkdir -p $(PATH_VECT_OBJ)
	mkdir -p $(PATH_PARS_OBJ)
	mkdir -p $(PATH_MANDA_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJB)%.o : $(PATH_SRC)%.c $(HEADERS)
	mkdir -p $(PATH_LIBFTB_OBJ)
	mkdir -p $(PATH_VECTB_OBJ)
	mkdir -p $(PATH_PARSB_OBJ)
	mkdir -p $(PATH_BONUS_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rfv $(PATH_OBJB) $(PATH_OBJ)

fclean : clean 
	rm -rfv $(NAME) $(NAMEB)

re : fclean all 

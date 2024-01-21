#ifndef MAIN_H
#define MAIN_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "vectors/vectors.h"
#include "objects.h"
#include "parsing/parse.h"
#include <pthread.h>
#include "ggl_mlx_define.h"
# define BUFFER_SIZE 32
#define RESET_COLOR     "\033[0m"
#define BLACK_COLOR     "\033[0;30m"
#define RED_COLOR       "\033[0;31m"
#define GREEN_COLOR     "\033[0;32m"
#define YELLOW_COLOR    "\033[0;33m"
#define BLUE_COLOR      "\033[0;34m"
#define MAGENTA_COLOR   "\033[0;35m"
#define CYAN_COLOR      "\033[0;36m"
#define WHITE_COLOR     "\033[0;37m"
# define SP 0
# define PL 1
# define SQ 2
# define TR 3
# define CY 4
# define CU 5
# define PY 6
# ifdef MACOS
#  define OS_NAME 1
# endif

# ifdef LINUX
#  define OS_NAME 2
# endif

# ifndef NUM_THREADS
#  define NUM_THREADS 4
# endif
# define REFLECTION_LIMIT 3
# define EPSILON 0.00001

typedef struct		s_v3
{
	t_point	o;
	t_point	d;
}					t_v3;

typedef struct s_cam
{
	int				init;
	int				idx;
	t_point			o;
	t_point			nv;
	int				fov;
	void			*img_ptr;
	int				*px_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_camera	*next;
}   t_cam;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_cam *cam;
    t_cam *begin;
}   t_mlx;

typedef struct		s_light
{
	t_point			o;
	double			br;
	int				color;
	struct s_light	*next;
}					t_light;

typedef struct		s_scene
{
	int				res_init;
	int				xres;
	int				yres;
	int				cam_nb;
	t_light			*l;
	int				al_init;
	double			ambient_light;
	int				al_color;
	int				bgr;
}					t_scene;

typedef struct		s_obj
{
	int				flag;
	union u_figures	fig;
	int				color;
	int				specular;
	double			refl_idx;
	double			refr_idx;
	int				texture;
	t_point			normal;
	double			wavelength;
	struct s_figures*next;
}					t_obj;

typedef struct		s_wrapper
{
	t_mlx		mlx;
	t_scene			data;
	t_obj		*lst;
	int				tid;
	int				i;
	int				j;
}					t_wrapper;

typedef struct		s_rss
{
	int		limit;
	int		xres;
	int		yres;
	int		i;
	int		j;
}					t_rss;

typedef struct		s_inter
{
	int				color;
	int				ref_color;
	t_point			normal;
	t_point			p;
	t_point			ref_vec;
}					t_inter;

typedef struct		s_bmp_header
{
	char			type[2];
	unsigned int	size;
	unsigned int	reserved;
	unsigned int	offset;
}					t_bmphead;

typedef struct		s_dib_header
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	colplanes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	img_size;
	int				x_ppm;
	int				y_ppm;
	unsigned int	color_number;
	unsigned int	important_color;
}					t_dibhead;

typedef struct		s_thread
{
	pthread_t		threads[NUM_THREADS];
	t_wrapper		wrapper[NUM_THREADS];
	int				i;
}					t_thread;

typedef struct		s_sq
{
	t_point			half_size;
	t_point			floor;
	t_point			center_to_ip;
}					t_sq;

typedef struct		s_cube
{
	t_obj		sq;
	t_point			center;
	t_point			normal[6];
}					t_cube;

typedef struct		s_pyramid
{
	t_obj		sq;
	t_obj		tr;
	t_point			tr_center;
	t_point			normal[5];
	t_point			corner[4];
}					t_pyr;





t_point		refract_ray(t_point d, t_point normal, t_obj *lst)
void error_message(char *str);
t_point		reflect_ray(t_point ray, t_point normal);

#endif
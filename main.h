#ifndef MAIN_H
#define MAIN_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>
#include "libft/libft.h"
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
# define OS_NAME 1
# endif

# ifdef LINUX
# define OS_NAME 2
# endif

# ifndef NUM_THREADS
#  define NUM_THREADS 4
# endif
# define REFLECTION_LIMIT 3
# define EPSILON 0.00001

typedef struct s_point
{
    double x;
    double y;
    double z;
}   t_point;


typedef struct	s_sphere
{
	t_point	c;
	double	r;
	int		inside;
}				t_sphere;

typedef struct	s_plane
{
	t_point	p;
}				t_plane;

typedef struct	s_square
{
	t_point	c;
	double	side;

}				t_square;

typedef struct	s_cylinder
{
	t_point	c;
	t_point	nv;
	double	r;
	double	h;
	double	dist1;
	double	dist2;
}				t_cylinder;

typedef struct	s_triangle
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
}				t_triangle;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_square	sq;
	t_cylinder	cy;
	t_triangle	tr;
};

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
	struct s_cam	*next;
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
	struct s_obj *next;
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

int			create_file(char *name, int i, int j);
void		create_header(t_scene data, t_bmphead *header, t_dibhead *dib);
void		write_header(int fd, t_bmphead header, t_dibhead dib);
void		write_file(int fd, t_scene data, t_mlx mlx);
void		save_bmp(t_mlx mlx, t_scene data, char *name);
static t_point		set_camera(int n, t_rss rss, t_mlx mlx);
static t_point		look_at(t_point d, t_point cam_nv);
int				calc_ray(int n, t_rss rss, t_wrapper *w);
int		cproduct(int color, double coef);
int		cadd(int color_a, int color_b);
int		color_x_light(int color, double rgb[3]);
int		color_difference(int color1, int color2);
static void		init_cube(t_cube *c, t_obj *lst);
double			cube_intersection(t_point o, t_point d, t_obj *lst);
static void		init_pyramid(t_pyr *p, t_obj *lst);
double			pyramid_intersection(t_point o, t_point d, t_obj *lst);
static int		solve_cylinder(double x[2], t_point o, t_point d, t_obj *lst);
static t_point		calc_cy_normal(double x2[2], t_point  o, t_point d, t_obj  *lst);
static double	cy_intersection(t_point o, t_point d, t_point *normal, t_obj *lst);
static double	caps_intersection(t_point o, t_point d, t_obj *lst);
double			cylinder_intersection(t_point o, t_point d, t_obj *lst);
void	add_coeficient(double (*rgb)[3], double coef, int color);
double	calc_specular(t_v3 ray, t_inter *inter, t_scene data, t_obj *lst);
void	compute_light(t_v3 ray, t_inter *inter, t_scene data, t_obj *lst);
void	calc_normal(t_point p, t_point d, t_point *normal, t_obj *l);
int		is_lit(t_point o, t_point d, t_obj *lst);
void error_message(char *str);
void render_scene(t_wrapper *w);
void		init_mlx(t_mlx *mlx, t_scene *data);
void		message_prompt(int ac);
int			next_cam(int keycode, t_mlx *mlx);
int			close_program(void *param);
static void		*render_thread(void *ptr);
void			rendering(t_wrapper wrapper[NUM_THREADS]);
void			wrapp_data(t_mlx mlx, t_scene data, t_obj *lst,t_wrapper *wrapper);
double			solve_plane(t_point o, t_point d, t_point plane_p, t_point plane_nv);
double			plane_intersection(t_point o, t_point d, t_obj *lst);
double			square_intersection(t_point o, t_point d, t_obj *lst);
static int		p_is_outside(t_point p1, t_point p2, t_point p3, t_point ip);
double			triangle_intersection(t_point o, t_point d, t_obj *lst);
void		try_all_intersections(t_v3 ray, t_obj *lst,
					t_obj *closest_figure, double *closest_intersection);
int			trace_ray(t_point o, t_point d, t_wrapper *w, int depth);
int			average(int color1, int color2);
int			average_supersampled_color(int *color);
t_point		reflect_ray(t_point ray, t_point normal);
t_point		refract_ray(t_point d, t_point normal, t_obj *lst);
int					*sample_pixel(int *edge_color, int last[2], t_rss rss, t_wrapper *w);
static int			*sample_first_column(int *edge_color, int last[2], t_rss rss, t_wrapper *w);
static int			*sample_last_column(int *edge_color, int last[2], t_rss rss, t_wrapper *w);
static int			*sample_centered_pixel(int *edge_color, int last[2], t_rss rss, t_wrapper *w);
static void		solve_sphere(double x[2], t_point o, t_point d, t_obj *lst);
double			sphere_intersection(t_point o, t_point d, t_obj *lst);
static int	checkerboard(t_inter *inter);
static t_point	sinwave(t_inter *inter, t_obj *lst);
static void		define_color(double r, double g, double b, double color[3]);
int				rainbow(t_inter *inter);
void		apply_texture(int texture, t_inter *inter, t_obj *lst);
static int			supersample_first_corner(int *color, int center,t_rss rss, t_wrapper *w);
static int			supersample_second_corner(int *color, int center, t_rss rss, t_wrapper *w);
static int			supersample_third_corner(int *color, int center, t_rss rss, t_wrapper *w);
static int			supersample_fourth_corner(int *color, int center, t_rss rss, t_wrapper *w);
int					supersample(int *color, t_rss rss, t_wrapper *w);
void		graphic_loop(t_mlx mlx, t_scene data);
void		parse_pyramid(t_obj **elem, char **str);
void		parse_cube(t_obj **elem, char **str);
void		parse_cylinder(t_obj **elem, char **str);
void		parse_triangle(t_obj **elem, char **str);
void		parse_square(t_obj **elem, char **str);
void		parse_plane(t_obj **elem, char **str);
void		parse_sphere(t_obj **elem, char **str);
int			parse_color(char **str);
void		in_range(double nb, double min, double max, char *function);
void		ft_addnewlst_back(t_obj **alst);
int			stoi(char **str);
t_point		parse_p3(char **str);
double		stof(char **str);
void		comma(char **str);
void		next(char **str);
char *line(char *str, int fd);
static void		parse2(t_obj **lst, char *str);
static void parse(t_mlx *mlx, t_scene *scene, t_obj **list, char **str);
static void parse_elements(t_mlx *mlx, t_scene *scene, t_obj **list, char *str);
void parse_scene(t_mlx *mlx, t_scene *scene, t_obj **list, char **av);
void		parse_res(t_scene *data, char **str);
void		parse_ambient_light(t_scene *data, char **str);
void		parse_camera(t_mlx *mlx, t_scene *data, char **str);
void		parse_light(t_scene **data, char **str);
t_point		z_axis_rotation(t_point vec, double angle);
t_point		y_axis_rotation(t_point vec, double angle);
t_point		x_axis_rotation(t_point vec, double angle);
double  distance(t_point p1, t_point p2);
t_point		scal_x_vec(double n, t_point p);
double		vcos(t_point a, t_point b);
double		vsin(t_point a, t_point b);
t_point normalize(t_point vector);
double mod(t_point vector);
t_point cross(t_point a, t_point b);
t_point cross(t_point a, t_point b);
t_point vadd(t_point a, t_point b);
t_point vsubstr(t_point a, t_point b);
t_point vector(double x, double y, double z);
double dot(t_point a, t_point b);


#endif

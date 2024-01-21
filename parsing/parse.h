#ifndef PARSE_H
#define PARSE_H


#include "./../main.h"





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
static void parse(t_mlx *mlx, t_scene *scene, t_obj *list, char ***str);
static void parse_elements(t_mlx *mlx, t_scene *scene, t_obj *list, char **str);
void parse_scene(t_mlx *mlx, t_scene *scene, t_obj **list, char **av);
void		parse_res(t_scene *data, char **str);
void		parse_ambient_light(t_scene *data, char **str);
void		parse_camera(t_mlx *mlx, t_scene *data, char **str);
void		parse_light(t_scene **data, char **str);





#endif
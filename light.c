#include "main.h"

void	add_coeficient(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	mask = 255 << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) / 255;
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) / 255;
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) / 255;
}

double	calc_specular(t_v3 ray, t_inter *inter, t_scene data, t_obj *lst)
{
	double	light;
	t_point	direction;
	t_point	p_to_cam;
	t_point	reflected;

	direction = vsubstr(data.l->o, inter->p);
	p_to_cam = vsubstr(ray.o, inter->p);
	reflected = reflect_ray(direction, inter->normal);
	if (dot(reflected, p_to_cam) > 0)
		light = data.l->br * pow(vcos(reflected, p_to_cam), lst->specular);
	else
		light = 0;
	return (light);
}

void	compute_light(t_v3 ray, t_inter *inter, t_scene data, t_obj *lst)
{
	double			light;
	double			rgb[3];
	t_point			direction;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	add_coeficient(&rgb, data.ambient_light, data.al_color);
	while (data.l)
	{
		direction = vsubstr(data.l->o, inter->p);
		if (is_lit(inter->p, direction, lst)
				&& dot(inter->normal, direction) > 0)
		{
			light = data.l->br * vcos(inter->normal, direction);
			add_coeficient(&rgb, light, data.l->color);
		}
		if (lst->specular)
		{
			light = calc_specular(ray, inter, data, lst);
			add_coeficient(&rgb, light, data.l->color);
		}
		data.l = data.l->next;
	}
	inter->color = color_x_light(inter->color, rgb);
}

void	calc_normal(t_point p, t_point d, t_point *normal, t_obj *l)
{
	if (l->flag == SP)
	{
		*normal = normalize(vsubstr(p, l->fig.sp.c));
		if (vcos(d, *normal) > 0)
		{
			*normal = scal_x_vec(-1, *normal);
			l->fig.sp.inside = 1;
		}
		else
			l->fig.sp.inside = 0;
	}
	else
	{
		if (vcos(d, l->normal) > 0)
			*normal = scal_x_vec(-1, l->normal);
		else
			*normal = l->normal;
	}
}

int		is_lit(t_point o, t_point d, t_obj *lst)
{
	double			in;

	while (lst)
	{
		if (lst->flag == SP)
			in = sphere_intersection(o, d, lst);
		else if (lst->flag == PL)
			in = plane_intersection(o, d, lst);
		else if (lst->flag == TR)
			in = triangle_intersection(o, d, lst);
		else if (lst->flag == SQ)
			in = square_intersection(o, d, lst);
		else if (lst->flag == CY)
			in = cylinder_intersection(o, d, lst);
		else if (lst->flag == CU)
			in = cube_intersection(o, d, lst);
		else if (lst->flag == PY)
			in = pyramid_intersection(o, d, lst);
		if (in > EPSILON && in < 1)
			return (0);
		lst = lst->next;
	}
	return (1);
}
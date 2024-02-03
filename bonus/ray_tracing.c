/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:36:32 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/03 16:24:12 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	try_all_intersections(t_v3 ray, t_obj *lst,
					t_obj *closest_figure, double *closest_intersection)
{
	double	dist;

	while (lst)
	{
		if (lst->flag == SP)
			dist = sphere_intersection(ray.o, ray.d, lst);
		else if (lst->flag == PL)
			dist = plane_intersection(ray.o, ray.d, lst);
		else if (lst->flag == TR)
			dist = triangle_intersection(ray.o, ray.d, lst);
		else if (lst->flag == CY)
			dist = cylinder_intersection(ray.o, ray.d, lst);
		if (dist > EPSILON && dist < *closest_intersection)
		{
			*closest_figure = *lst;
			*closest_intersection = dist;
		}
		lst = lst->next;
	}
}

int	trace_ray(t_point o, t_point d, t_wrapper *w, int depth)
{
	t_v3		ray;
	t_obj		cl_fig;
	t_inter		inter;
	double		closest_intersection;
	double		r;

	ray.o = o;
	ray.d = d;
	closest_intersection = INFINITY;
	cl_fig.flag = -1;
	try_all_intersections(ray, w->lst, &cl_fig, &closest_intersection);
	inter.p = vadd(o, scal_x_vec(closest_intersection, d));
	calc_normal(inter.p, d, &(inter.normal), &cl_fig);
	set_color(cl_fig, &inter, w);
	apply_texture(cl_fig.texture, &inter);
	compute_light(ray, &inter, w->data, w->lst);
	set_reflection_params(&cl_fig, &r);
	if (cl_fig.refr_idx > 0)
		inter.color = trace_ray(inter.p,
				refract_ray(d, inter.normal, &cl_fig), w, depth);
	if (r > 0 && depth > 0)
		inter.ref_color = trace_ray(inter.p,
				reflect_ray(scal_x_vec(-1, d), inter.normal), w, depth - 1);
	return (cadd(cproduct(inter.color, 1 - r), cproduct(inter.ref_color, r)));
}

int	average(int color1, int color2)
{
	int		average[3];
	int		mask;
	int		color[2];
	int		i;

	mask = 255;
	ft_memset(average, 0, 3 * sizeof(int));
	color[0] = color1;
	color[1] = color2;
	i = 0;
	while (i < 2)
	{
		average[0] += (color[i] & (mask << 16)) >> 16;
		average[1] += (color[i] & (mask << 8)) >> 8;
		average[2] += color[i] & mask;
		i++;
	}
	average[0] = average[0] / 2;
	average[1] = average[1] / 2;
	average[2] = average[2] / 2;
	return ((average[0] << 16) | (average[1] << 8) | average[2]);
}

int	average_supersampled_color(int *color)
{
	int		ss_color[3];
	int		mask;
	int		n;

	ft_memset(ss_color, 0, sizeof(int) * 3);
	mask = 255;
	n = 0;
	while (n < 4)
	{
		ss_color[0] += (color[n] & (mask << 16)) >> 16;
		ss_color[1] += (color[n] & (mask << 8)) >> 8;
		ss_color[2] += color[n] & mask;
		n++;
	}
	ss_color[0] = ss_color[0] / 4;
	ss_color[1] = ss_color[1] / 4;
	ss_color[2] = ss_color[2] / 4;
	free(color);
	return ((ss_color[0] << 16) | (ss_color[1] << 8) | ss_color[2]);
}

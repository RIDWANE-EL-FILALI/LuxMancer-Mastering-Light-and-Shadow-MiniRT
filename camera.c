/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:16:00 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/07 15:14:32 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point	set_camera(int n, t_rss rss, t_mlx mlx)
{
	double	img_asp_ratio;
	double	correct_fov;
	double	x_offset;
	double	y_offset;
	t_point	p;

	x_offset = ((n % 3) * 0.5);
	y_offset = ((n / 3) * 0.5);
	img_asp_ratio = (double)(rss.xres) / (double)(rss.yres);
	correct_fov = tan((mlx.cam->fov * M_PI / 180) / 2);
	p.x = ((2 * ((rss.i + x_offset) / rss.xres)) - 1) \
			* img_asp_ratio * correct_fov;
	p.y = (1 - (2 * ((rss.j + y_offset) / rss.yres))) * correct_fov;
	p.x *= -1;
	p.z = 1;
	return (p);
}

t_point	look_at(t_point d, t_point cam_nv)
{
	t_point	x_axis;
	t_point	y_axis;
	t_point	z_axis;
	t_point	tmp;
	t_point	rotated;

	tmp = vector(0, 1, 0);
	z_axis = cam_nv;
	if (cam_nv.y == 1 || cam_nv.y == -1)
	{
		if (cam_nv.y == 1)
			x_axis = (t_point){1, 0, 0};
		else
			x_axis = (t_point){-1, 0, 0};
	}
	else
		x_axis = cross(tmp, z_axis);
	y_axis = cross(z_axis, x_axis);
	rotated.x = d.x * x_axis.x + d.y * y_axis.x + d.z * z_axis.x;
	rotated.y = d.x * x_axis.y + d.y * y_axis.y + d.z * z_axis.y;
	rotated.z = d.x * x_axis.z + d.y * y_axis.z + d.z * z_axis.z;
	return (rotated);
}

int	calc_ray(int n, t_rss rss, t_wrapper *w)
{
	t_point	d;
	int		color;

	d = set_camera(n, rss, w->mlx);
	d = look_at(d, w->mlx.cam->nv);
	color = trace_ray(w->mlx.cam->o, d, w, REFLECTION_LIMIT);
	return (color);
}

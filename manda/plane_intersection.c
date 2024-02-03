/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:50:12 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/03 15:48:08 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	solve_plane(t_point o, t_point d, t_point plane_p, t_point plane_nv)
{
	double	x;
	double	denom;

	denom = dot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot(plane_nv, vsubstr(plane_p, o))) / denom;
	if (x > 0)
		return (x);
	return (INFINITY);
}

double	plane_intersection(t_point o, t_point d, t_obj *lst)
{
	return (solve_plane(o, d, lst->fig.pl.p, lst->normal));
}

int	p_is_outside(t_point p1, t_point p2, t_point p3, t_point ip)
{
	t_point	v1;
	t_point	v2;
	t_point	vp;

	v1 = vsubstr(p2, p1);
	v2 = vsubstr(p3, p1);
	vp = vsubstr(ip, p1);
	if (vcos(cross(v1, v2), cross(v1, vp)) < 0)
		return (1);
	return (0);
}

double	triangle_intersection(t_point o, t_point d, t_obj *lst)
{
	double	id;
	t_point	ip;

	id = solve_plane(o, d, lst->fig.tr.p1, lst->normal);
	ip = vadd(o, scal_x_vec(id, d));
	if (p_is_outside(lst->fig.tr.p1, lst->fig.tr.p2, lst->fig.tr.p3, ip))
		return (INFINITY);
	if (p_is_outside(lst->fig.tr.p2, lst->fig.tr.p3, lst->fig.tr.p1, ip))
		return (INFINITY);
	if (p_is_outside(lst->fig.tr.p3, lst->fig.tr.p1, lst->fig.tr.p2, ip))
		return (INFINITY);
	return (id);
}

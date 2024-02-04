/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:50:12 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/04 18:05:04 by mghalmi          ###   ########.fr       */
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

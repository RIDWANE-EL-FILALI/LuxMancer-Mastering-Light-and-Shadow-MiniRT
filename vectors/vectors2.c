/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:54:46 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/07 19:10:09 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double	mod(t_point vector)
{
	return (sqrt(dot(vector, vector)));
}

t_point	normalize(t_point vector)
{
	t_point	nv;
	double	mod;

	mod = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	nv.x = vector.x / mod;
	nv.y = vector.y / mod;
	nv.z = vector.z / mod;
	return (nv);
}

double	vsin(t_point a, t_point b)
{
	return (sqrt(1 - pow(vcos(a, b), 2)));
}

double	vcos(t_point a, t_point b)
{
	return (dot(a, b) / (mod(a) * mod(b)));
}

t_point	scal_x_vec(double n, t_point p)
{
	t_point	v;

	v.x = n * p.x;
	v.y = n * p.y;
	v.z = n * p.z;
	return (v);
}

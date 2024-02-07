/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:54:01 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/07 19:10:07 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_point	vector(double x, double y, double z)
{
	t_point	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_point	vsubstr(t_point a, t_point b)
{
	t_point	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

t_point	vadd(t_point a, t_point b)
{
	t_point	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_point	cross(t_point a, t_point b)
{
	t_point	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	dot(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

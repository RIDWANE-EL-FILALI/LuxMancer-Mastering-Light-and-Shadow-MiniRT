/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:49:23 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/28 10:50:03 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "main.h"

typedef struct s_sphere
{
	t_point	c;
	double	r;
	int		inside;
}			t_sphere;

typedef struct s_plane
{
	t_point	p;
}			t_plane;

typedef struct s_square
{
	t_point	c;
	double	side;

}			t_square;

typedef struct s_cylinder
{
	t_point	c;
	t_point	nv;
	double	r;
	double	h;
	double	dist1;
	double	dist2;
}			t_cylinder;

typedef struct s_triangle
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
}			t_triangle;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_square	sq;
	t_cylinder	cy;
	t_triangle	tr;
};

#endif
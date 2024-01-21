#ifndef OBJECTS_H
#define OBJECTS_H

#include "main.h"
#include "vectors/vectors.h"

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


#endif
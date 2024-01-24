#include "main.h"

void		solve_sphere(double x[2], t_point o, t_point d, t_obj *lst)
{
	double	disc;
	t_point	oc;
	double	k[3];

	oc = vsubstr(o, lst->fig.sp.c);
	k[0] = dot(d, d);
	k[1] = 2 * dot(d, oc);
	k[2] = dot(oc, oc) - lst->fig.sp.r * lst->fig.sp.r;
	disc = k[1] * k[1] - (4 * k[0] * k[2]);
	if (disc < 0)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return ;
	}
	x[0] = (-k[1] + sqrt(disc)) / (2 * k[0]);
	x[1] = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

double			sphere_intersection(t_point o, t_point d, t_obj *lst)
{
	double	closest;
	double	x[2];
	t_point	ip1;
	t_point	ip2;

	closest = INFINITY;
	solve_sphere(x, o, d, lst);
	if (x[0] > EPSILON && x[0] < INFINITY)
		closest = x[0];
	if (x[1] > EPSILON && x[1] < INFINITY)
		if (x[1] < x[0])
			closest =  x[1];
	if (lst->texture != 4)
		return (closest);
	ip1 = vadd(o, scal_x_vec(x[0], d));
	ip2 = vadd(o, scal_x_vec(x[1], d));
	if (ip1.y >= lst->fig.sp.c.y && ip2.y >= lst->fig.sp.c.y)
	{
		if (x[0] < x[1])
			return (x[0]);
		return (x[1]);
	}
	else if (ip1.y >= lst->fig.sp.c.y)
		return (x[0]);
	else if (ip2.y >= lst->fig.sp.c.y)
		return (x[1]);
	return (INFINITY);
}

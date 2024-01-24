#include "main.h"

int		solve_cylinder(double x[2], t_point o, t_point d, t_obj *lst)
{
	t_point	v;
	t_point	u;
	double	a;
	double	b;
	double	c;

	v = scal_x_vec(dot(d, lst->fig.cy.nv), lst->fig.cy.nv);
	v = vsubstr(d, v);
	u = scal_x_vec(dot(vsubstr(o, lst->fig.cy.c), lst->fig.cy.nv),
													lst->fig.cy.nv);
	u = vsubstr(vsubstr(o, lst->fig.cy.c), u);
	a = dot(v, v);
	b = 2 * dot(v, u);
	c = dot(u, u) - pow(lst->fig.cy.r, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

t_point		calc_cy_normal(double x2[2], t_point  o, t_point d, t_obj  *lst)
{
	double	dist;
	double	x;

	if ((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
				&& x2[0] > EPSILON) && (lst->fig.cy.dist2 >= 0
				&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[1] > EPSILON))
	{
		if (x2[0] < x2[1])
			dist = lst->fig.cy.dist1;
		else
			dist = lst->fig.cy.dist2;
		if (x2[0] < x2[1])
			x = x2[0];
		else
			x = x2[1];
	}
	else if (lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
														&& x2[0] > EPSILON)
	{
		dist = lst->fig.cy.dist1;
		x = x2[0];
	}
	else
	{
		dist = lst->fig.cy.dist2;
		x = x2[1];
	}
	x2[0] = x;
	return (normalize(vsubstr(vsubstr(scal_x_vec(x, d),
			scal_x_vec(dist, lst->fig.cy.nv)), vsubstr(lst->fig.cy.c, o))));
}

double	cy_intersection(t_point o, t_point d, t_point *normal, t_obj *lst)
{
	double	x2[2];

	if (solve_cylinder(x2, o, d, lst) == 0)
		return (INFINITY);
	lst->fig.cy.dist1 = dot(lst->fig.cy.nv, vsubstr(scal_x_vec(x2[0], d),
												vsubstr(lst->fig.cy.c, o)));
	lst->fig.cy.dist2 = dot(lst->fig.cy.nv, vsubstr(scal_x_vec(x2[1], d),
												vsubstr(lst->fig.cy.c, o)));
	if (!((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
					&& x2[0] > EPSILON) || (lst->fig.cy.dist2 >= 0
					&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, o, d, lst);
	return (x2[0]);
}

double	caps_intersection(t_point o, t_point d, t_obj *lst)
{
	double	id1;
	double	id2;
	t_point	ip1;
	t_point	ip2;
	t_point	c2;

	c2 = vadd(lst->fig.cy.c, scal_x_vec(lst->fig.cy.h, lst->fig.cy.nv));
	id1 = solve_plane(o, d, lst->fig.cy.c, lst->fig.cy.nv);
	id2 = solve_plane(o, d, c2, lst->fig.cy.nv);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = vadd(o, scal_x_vec(id1, d));
		ip2 = vadd(o, scal_x_vec(id2, d));
		if ((id1 < INFINITY && distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
				&& (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r))
			{
				if (id1 < id2)
					return (id1);
				else
					return (id2);
			}
		else if (id1 < INFINITY
						&& distance(ip1, lst->fig.cy.c) <= lst->fig.cy.r)
			return (id1);
		else if (id2 < INFINITY && distance(ip2, c2) <= lst->fig.cy.r)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}

double			cylinder_intersection(t_point o, t_point d, t_obj *lst)
{
	double	cylinder_inter;
	double	caps_inter;
	t_point	cy_normal;

	cylinder_inter = cy_intersection(o, d, &cy_normal, lst);
	if (lst->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = caps_intersection(o, d, lst);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			lst->normal = cy_normal;
			return (cylinder_inter);
		}
		lst->normal = lst->fig.cy.nv;
		return (caps_inter);
	}
	return (INFINITY);
}
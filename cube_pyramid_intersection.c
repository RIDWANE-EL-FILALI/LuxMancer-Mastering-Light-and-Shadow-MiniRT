#include "main.h"

void		init_cube(t_cube *c, t_obj *lst)
{
	c->normal[0] = (t_point) {1, 0, 0};
	c->normal[1] = (t_point) {-1, 0, 0};
	c->normal[2] = (t_point) {0, 1, 0};
	c->normal[3] = (t_point) {0, -1, 0};
	c->normal[4] = (t_point) {0, 0, 1};
	c->normal[5] = (t_point) {0, 0, -1};
	c->center = lst->fig.sq.c;
	c->sq.fig.sq.side = lst->fig.sq.side;
}

double			cube_intersection(t_point o, t_point d, t_obj *lst)
{
	t_cube		c;
	t_point		cl_normal;
	double		cl_inter;
	double		inter;
	int			i;

	init_cube(&c, lst);
	cl_inter = INFINITY;
	i = 0;
	while (i < 6)
	{
		c.sq.fig.sq.c = vadd(c.center,
							scal_x_vec(lst->fig.sq.side / 2, c.normal[i]));
		c.sq.normal = c.normal[i];
		inter = square_intersection(o, d, &(c.sq));
		if (inter > EPSILON && inter < cl_inter)
		{
			cl_inter = inter;
			cl_normal = c.sq.normal;
		}
		i++;
	}
	lst->normal = cl_normal;
	return (cl_inter);
}

void		init_pyramid(t_pyr *p, t_obj *lst)
{
	int	i;

	p->normal[0] = (t_point) {1, 0, 0};
	p->normal[1] = (t_point) {0, 0, 1};
	p->normal[2] = (t_point) {-1, 0, 0};
	p->normal[3] = (t_point) {0, 0, -1};
	p->normal[4] = (t_point) {1, 0, 0};
	p->tr_center = vadd(lst->fig.sq.c,
					scal_x_vec(lst->fig.sq.side, (t_point){0, 1, 0}));
	p->sq.fig.sq.side = lst->fig.sq.side;
	p->sq.fig.sq.c = lst->fig.sq.c;
	p->sq.normal = (t_point) {0, -1, 0};
	i = 0;
	while (i < 4)
	{
		p->corner[i] = vadd(lst->fig.sq.c,
						scal_x_vec(lst->fig.sq.side / 2, p->normal[i]));
		p->corner[i] = vadd(p->corner[i],
						scal_x_vec(lst->fig.sq.side / 2, p->normal[i + 1]));
		i++;
	}
	p->tr.fig.tr.p3 = p->tr_center;
}

double			pyramid_intersection(t_point o, t_point d, t_obj *lst)
{
	t_pyr		p;
	t_point		cl_normal;
	double		cl_inter;
	double		inter;
	int			i;

	init_pyramid(&p, lst);
	cl_inter = INFINITY;
	i = 0;
	while (i < 4)
	{
		p.tr.fig.tr.p1 = p.corner[i];
		if (i < 3)
			p.tr.fig.tr.p2 = p.corner[i + 1];
		else
			p.tr.fig.tr.p2 = p.corner[0];
		p.tr.normal = cross(vsubstr(p.tr.fig.tr.p3, p.tr.fig.tr.p1),
							vsubstr(p.tr.fig.tr.p2, p.tr.fig.tr.p1));
		inter = triangle_intersection(o, d, &(p.tr));
		if (inter > EPSILON && inter < cl_inter)
		{
			cl_inter = inter;
			cl_normal = p.tr.normal;
		}
		i++;
	}
	lst->normal = cl_normal;
	return (cl_inter);
}
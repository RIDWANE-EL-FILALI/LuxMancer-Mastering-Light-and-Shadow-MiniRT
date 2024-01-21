#include "parse.h"

void		parse_sphere(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = SP;
	next(str);
	lst->fig.sp.c = parse_p3(str);
	lst->fig.sp.r = stof(str) / 2;
	in_range(lst->fig.sp.r, 0, INFINITY, "sphere");
	lst->specular = stoi(str);
	in_range(lst->specular, 0, INFINITY, "sphere");
	lst->refl_idx = stof(str);
	in_range(lst->refl_idx, 0, 1, "sphere");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "sphere");
	lst->texture = stoi(str);
	in_range(lst->texture, 0, 5, "sphere");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}

void		parse_plane(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = PL;
	next(str);
	lst->fig.pl.p = parse_p3(str);
	lst->normal = normalize(parse_p3(str));
	lst->specular = stoi(str);
	in_range(lst->specular, 0, INFINITY, "plane");
	lst->refl_idx = stof(str);
	in_range(lst->refl_idx, 0, 1, "plane");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "plane");
	lst->texture = stoi(str);
	in_range(lst->texture, 0, 5, "plane");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}

void		parse_square(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = SQ;
	next(str);
	lst->fig.sq.c = parse_p3(str);
	lst->normal = normalize(parse_p3(str));
	lst->fig.sq.side = stof(str);
	in_range(lst->fig.sq.side, 0, INFINITY, "square");
	lst->specular = stoi(str);
	in_range(lst->specular, 0, INFINITY, "square");
	lst->refl_idx = stof(str);
	in_range(lst->refl_idx, 0, 1, "square");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "square");
	lst->texture = stoi(str);
	in_range(lst->texture, 0, 5, "square");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}

void		parse_triangle(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = TR;
	next(str);
	lst->fig.tr.p1 = parse_p3(str);
	lst->fig.tr.p2 = parse_p3(str);
	lst->fig.tr.p3 = parse_p3(str);
	lst->normal = cross(vsubstr(lst->fig.tr.p3, lst->fig.tr.p1),
			vsubstr(lst->fig.tr.p2, lst->fig.tr.p1));
	lst->specular = stoi(str);
	in_range(lst->specular, 0, INFINITY, "triangle");
	next(str);
	lst->refl_idx = stof(str);
	in_range(lst->refl_idx, 0, 1, "triangle");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "triangle");
	lst->texture = stoi(str);
	in_range(lst->texture, 0, 5, "triangle");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}

void		parse_cylinder(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = CY;
	next(str);
	lst->fig.cy.c = parse_p3(str);
	lst->fig.cy.nv = normalize(parse_p3(str));
	lst->fig.cy.r = stof(str) / 2;
	in_range(lst->fig.cy.r, 0, INFINITY, "cylinder");
	lst->fig.cy.h = stof(str);
	in_range(lst->fig.cy.h, 0, INFINITY, "cylinder");
	lst->specular = stoi(str);
	in_range(lst->specular, 0, INFINITY, "cylinder");
	lst->refl_idx = stof(str);
	in_range(lst->refl_idx, 0, 1, "cylinder");
	lst->refr_idx = stof(str);
	in_range(lst->refr_idx, 0, INFINITY, "cylinder");
	lst->texture = stoi(str);
	in_range(lst->texture, 0, 5, "cylinder");
	if (lst->texture == 2)
		lst->wavelength = stof(str);
	lst->color = parse_color(str);
}
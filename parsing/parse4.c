#include "../main.h"

void		parse_cube(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = CU;
	next(str);
	lst->fig.sq.c = parse_p3(str);
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

void		parse_pyramid(t_obj **elem, char **str)
{
	t_obj	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = PY;
	next(str);
	lst->fig.sq.c = parse_p3(str);
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

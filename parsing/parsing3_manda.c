/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_manda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:52:46 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/08 13:46:26 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parse_cylinder_manda(t_obj **elem, char **str)
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
	lst->texture = 0;
	lst->color = parse_color(str);
}

void	parse_sphere_manda(t_obj **elem, char **str)
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
	lst->texture = 0;
	lst->color = parse_color(str);
}

void	parse_plane_manda(t_obj **elem, char **str)
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
	lst->texture = 0;
	lst->color = parse_color(str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_norm.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:15:52 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/27 15:36:00 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	check_dist(double x2[2], t_obj *lst)
{
	double	dist;

	if (x2[0] < x2[1])
		dist = lst->fig.cy.dist1;
	else
		dist = lst->fig.cy.dist2;
	return (dist);
}

double	check_x(double x2[2])
{
	double	x;

	if (x2[0] < x2[1])
		x = x2[0];
	else
		x = x2[1];
	return (x);
}

double	select_closest(double id1, double id2)
{
	if (id1 < id2)
		return (id1);
	else
		return (id2);
}

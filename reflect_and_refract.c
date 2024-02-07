/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_and_refract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:38:04 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/28 11:38:38 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point	reflect_ray(t_point ray, t_point normal)
{
	return (vsubstr(scal_x_vec(2 * dot(normal, ray), normal), ray));
}

t_point	refract_ray(t_point d, t_point normal, t_obj *lst)
{
	double	cosi;
	double	etai;
	double	etat;
	double	eta;
	double	k;

	cosi = dot(d, normal);
	etai = 1;
	etat = lst->refr_idx;
	if (lst->fig.sp.inside == 1)
	{
		k = etai;
		etai = etat;
		etat = k;
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		return (reflect_ray(scal_x_vec(-1, d), normal));
	return (vadd(scal_x_vec(eta, d), scal_x_vec(eta * cosi - sqrt(k), normal)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:01:01 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/29 13:01:03 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_reflection_params(t_obj *cl_fig, double *r)
{
	if (cl_fig->flag != -1)
	{
		cl_fig->refr_idx = cl_fig->refr_idx;
		*r = cl_fig->refl_idx;
	}
	else
	{
		cl_fig->refr_idx = 0;
		*r = 0;
	}
}

void	set_color(t_obj cl_fig, t_inter *inter, t_wrapper *w)
{
	if (cl_fig.flag != -1)
		inter->color = cl_fig.color;
	else
		inter->color = w->data.bgr;
}

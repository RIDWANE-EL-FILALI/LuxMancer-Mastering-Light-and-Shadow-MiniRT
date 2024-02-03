/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_manda_norm.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:22:48 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/03 17:30:19 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_color(t_obj cl_fig, t_inter *inter, t_wrapper *w)
{
	if (cl_fig.flag != -1)
		inter->color = cl_fig.color;
	else
		inter->color = w->data.bgr;
}

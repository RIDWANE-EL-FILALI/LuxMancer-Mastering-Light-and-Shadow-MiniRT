/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:17:41 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/27 13:19:06 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	cproduct(int color, double coef)
{
	int	mask;
	int	r;
	int	g;
	int	b;

	mask = 255;
	r = coef * ((color & (mask << 16)) >> 16);
	g = coef * ((color & (mask << 8)) >> 8);
	b = coef * (color & mask);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	cadd(int color_a, int color_b)
{
	int	mask;
	int	r;
	int	g;
	int	b;

	mask = 255;
	r = ((color_a & (mask << 16)) + (color_b & (mask << 16))) & (mask << 16);
	g = ((color_a & (mask << 8)) + (color_b & (mask << 8))) & (mask << 8);
	b = ((color_a & mask) + (color_b & mask)) & mask;
	return (r | g | b);
}

int	color_x_light(int color, double rgb[3])
{
	unsigned int	mask;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	mask = 255 << 16;
	r = rgb[0] * ((color & mask) >> 16);
	mask >>= 8;
	g = rgb[1] * ((color & mask) >> 8);
	mask >>= 8;
	b = rgb[2] * (color & mask);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	color_difference(int color1, int color2)
{
	int	mask;
	int	r[2];
	int	g[2];
	int	b[2];
	int	distance_exp2;

	mask = 255;
	r[0] = (color1 & (mask << 16)) >> 16;
	g[0] = (color1 & (mask << 8)) >> 8;
	b[0] = color1 & mask;
	r[1] = (color2 & (mask << 16)) >> 16;
	g[1] = (color2 & (mask << 8)) >> 8;
	b[1] = color2 & mask;
	distance_exp2 = pow((r[1] - r[0]), 2) + pow((g[1] - g[0]), 2) \
				+ pow((b[1] - b[0]), 2);
	return (distance_exp2 > 1000);
}

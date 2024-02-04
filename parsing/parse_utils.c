/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:34:14 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/04 18:07:16 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*line(char *str, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	char	*ptr;
	int		retrn;

	retrn = read(fd, buff, BUFFER_SIZE);
	while (retrn > 0)
	{
		ptr = str;
		buff[retrn] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
			return (NULL);
		free(ptr);
		retrn = read(fd, buff, BUFFER_SIZE);
	}
	str = ft_strjoin(str, "\n");
	return (str);
}

void	next(char **str)
{
	while (**str == 32 || **str == 9)
		(*str)++;
}

void	comma(char **str)
{
	if (**str != ',')
		error_message("parameters bad formatted\n");
	(*str)++;
}

double	stof(char **str)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		w = w * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	d = 0.0;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	next(str);
	return (d * neg);
}

t_point	parse_p3(char **str)
{
	t_point	p;

	p.x = stof(str);
	comma(str);
	p.y = stof(str);
	comma(str);
	p.z = stof(str);
	next(str);
	return (p);
}

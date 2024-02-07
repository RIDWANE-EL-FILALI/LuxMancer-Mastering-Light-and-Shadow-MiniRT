/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creater_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:13:52 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/27 13:14:04 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_fd(char *bmpname)
{
	int	fd;

	fd = 0;
	fd = open(bmpname, O_WRONLY | O_CREAT | O_TRUNC, \
													S_IRUSR | S_IWUSR);
	if (!(fd > 0))
		error_message("in do_the_bmp_thing() while creating file");
	return (fd);
}

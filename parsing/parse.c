/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:41:36 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/07 17:43:49 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	choise(t_mlx *mlx, t_scene *scene, t_obj **list, char **str)
{
	char	*ret;

	ret = *str;
	if (*ret == 'R' && *(ret++))
		parse_res(scene, &ret);
	else if (*ret == 'A' && *(ret++))
		parse_ambient_light(scene, &ret);
	else if (*ret == 'C' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_camera(mlx, scene, &ret);
	else if (*ret == 'c' && *(ret + 1) == 'y' && *(ret++) && *(ret++))
		parse_cylinder(list, &ret);
	else if (*ret == 'L' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_light(&scene, &ret);
	else if (*ret == 's' && *(ret + 1) == 'p' && *(ret++) && *(ret++))
		parse_sphere(list, &ret);
	else if (*ret == 'p' && *(ret + 1) == 'l' && *(ret++) && *(ret++))
		parse_plane(list, &ret);
	else if (*ret == 't' && *(ret + 1) == 'r' && *(ret++) && *(ret++))
		parse_triangle(list, &ret);
	if (*ret != '\n')
		error_message("invalide param\n");
	*str = ret;
}

void	parse_elements(t_mlx *mlx, t_scene *scene, t_obj **list, char *str)
{
	scene->res_init = 0;
	scene->al_init = 0;
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			choise(mlx, scene, list, &str);
		str++;
	}
	if (scene->res_init == 0 || scene->al_init == 0 || mlx->cam == NULL)
		error_message("Error : not enought elements to render a scene\n");
}

void	parse_scene(t_mlx *mlx, t_scene *scene, t_obj **list, char **av)
{
	char	*str;
	int		fd;

	*list = NULL;
	scene->l = NULL;
	mlx->cam = NULL;
	write(1, "Iniciating parcing ...\n", 23);
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		error_message("Error in allocating memory\n");
	fd = open(av[1], 0);
	if (fd == -1)
		error_message("Error openning the file given\n");
	str = line(str, fd);
	parse_elements(mlx, scene, list, str);
	free(str);
}

void	parse_res(t_scene *data, char **str)
{
	if (data->res_init > 0)
		error_message("(R) can only be declared once in the scene\n");
	else
		data->res_init = 1;
	next(str);
	data->xres = stoi(str);
	in_range(data->xres, 1, INFINITY, "resolution");
	data->yres = stoi(str);
	in_range(data->yres, 1, INFINITY, "resolution");
}

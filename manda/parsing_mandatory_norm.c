/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mandatory_norm.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:50:55 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/28 17:50:58 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parse_light_manda(t_scene **data, char **str)
{
	t_light	*elem;
	t_light	*list;
	t_light	*begin;
	int		l;

	l = 0;
	begin = (*data)->l;
	list = (*data)->l;
	elem = malloc(sizeof(t_light));
	if (!elem)
		error_message("Error malloc failure in parse light\n");
	elem->next = NULL;
	add_light(elem, &list);
	parse_light_nomr(str, list, begin, data);
	while (begin)
	{
		l++;
		begin = begin->next;
	}
	if (l > 1)
		error_message("Error only one light allowed\n");
}

void	parse_mandatory(t_mlx *mlx, t_scene *scene, t_obj **list, char **str)
{
	char	*ret;

	ret = *str;
	if (*ret == 'R' && *(ret++))
		parse_res(scene, &ret);
	else if (*ret == 'A' && *(ret++))
		parse_ambient_light(scene, &ret);
	else if (*ret == 'C' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_camera_manda(mlx, scene, &ret);
	else if (*ret == 'c' && *(ret + 1) == 'y' && *(ret++) && *(ret++))
		parse_cylinder_manda(list, &ret);
	else if (*ret == 'L' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_light_manda(&scene, &ret);
	else if (*ret == 's' && *(ret + 1) == 'p' && *(ret++) && *(ret++))
		parse_sphere_manda(list, &ret);
	else if (*ret == 'p' && *(ret + 1) == 'l' && *(ret++) && *(ret++))
		parse_plane_manda(list, &ret);
	*str = ret;
}

void	parse_elements_manda(t_mlx *mlx, t_scene *scene, \
				t_obj **list, char *str)
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
			parse_mandatory(mlx, scene, list, &str);
		str++;
	}
	if (scene->res_init == 0 || scene->al_init == 0 || mlx->cam == NULL)
		error_message("not enought elements to render a scene \n");
}

void	parse_scene_manda(t_mlx *mlx, t_scene *scene, t_obj **list, char **av)
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
	parse_elements_manda(mlx, scene, list, str);
	free(str);
}

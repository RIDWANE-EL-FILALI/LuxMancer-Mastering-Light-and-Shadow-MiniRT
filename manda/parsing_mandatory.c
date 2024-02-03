/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mandatory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:06:41 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/03 18:09:05 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cam	*create_camera(t_mlx *mlx)
{
	t_cam	*elem;

	elem = malloc(sizeof(t_cam));
	if (!elem)
		error_message("Error malloc failure in camera\n");
	elem->next = NULL;
	if (mlx->cam)
		elem->idx = mlx->cam->idx + 1;
	else
		elem->idx = 1;
	return (elem);
}

void	add_camera_to_list(t_cam *elem, t_mlx *mlx)
{
	t_cam	*begin;

	begin = mlx->cam;
	if (mlx->cam)
	{
		while (mlx->cam->next)
			mlx->cam = mlx->cam->next;
		mlx->cam->next = elem;
	}
	else
		mlx->cam = elem;
	if (begin)
		mlx->cam = begin;
}

void	parse_camera_manda(t_mlx *mlx, t_scene *data, char **str)
{
	t_cam	*elem;

	elem = create_camera(mlx);
	add_camera_to_list(elem, mlx);
	next(str);
	data->cam_nb = elem->idx;
	elem->o = parse_p3(str);
	elem->nv = normalize(parse_p3(str));
	elem->fov = stoi(str);
	in_range(elem->fov, 0, 180, "camera");
}

void	parse_light_nomr(char **str, t_light *list,
				t_light	*begin, t_scene **data)
{
	next(str);
	list->o = parse_p3(str);
	list->br = stof(str);
	in_range(list->br, 0, 1, "light");
	list->color = parse_color(str);
	if (begin)
		(*data)->l = begin;
	else
		(*data)->l = list;
}

void	add_light(t_light *elem, t_light **list)
{
	if ((*list))
	{
		while ((*list)->next)
			(*list) = (*list)->next;
		(*list)->next = elem;
		(*list) = (*list)->next;
	}
	else
		(*list) = elem;
}

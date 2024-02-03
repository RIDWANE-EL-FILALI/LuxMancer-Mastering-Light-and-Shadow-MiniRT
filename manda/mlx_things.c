/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:46:41 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/03 18:06:33 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_mlx(t_mlx *mlx, t_scene *data)
{
	t_cam	*cam_begin;

	mlx->mlx = mlx_init();
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr, \
			&mlx->cam->bits_per_pixel, &mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}

void	message_prompt(int ac)
{
	int		t;

	t = NUM_THREADS;
	if (ac == 2)
	{
		if (NUM_THREADS == 1)
			printf(GREEN_COLOR "\nScene successfully rendered with 1 thread, " \
						RESET_COLOR);
		else
			printf(GREEN_COLOR \
					"\nScene successfully rendered with %d threads, " \
					RESET_COLOR, t);
		printf("press ESC at any momnet to close the program.\n");
	}
}

int	close_it(int keycode, t_mlx *mlx)
{
	(void)mlx;
	if (keycode == ESC_KEY)
		exit(0);
	return (0);
}

void	graphic_loop(t_mlx mlx, t_scene data)
{
	mlx.win = mlx_new_window(mlx.mlx, data.xres, data.yres, \
															"miniRT");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, close_it, &mlx);
	mlx_loop(mlx.mlx);
}

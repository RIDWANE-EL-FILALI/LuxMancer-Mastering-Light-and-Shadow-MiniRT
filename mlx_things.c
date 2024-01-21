#include "main.h"

void		init_mlx(t_mlx *mlx, t_scene *data)
{
	t_cam	*cam_begin;
	int			x_displayres;
	int			y_displayres;

	mlx->mlx = mlx_init();
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr,
			&mlx->cam->bits_per_pixel, &mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}

void		message_prompt(int ac)
{
	int		t;

	t = NUM_THREADS;
	if (ac == 2)
	{
		if (NUM_THREADS == 1)
			printf(GREEN_COLOR "\nScene successfully rendered with 1 thread, " RESET_COLOR);
		else
			printf(GREEN_COLOR "\nScene successfully rendered with %d threads, " RESET_COLOR, t);
		printf("press ESC at any momnet to close the program.\n");
		printf("If the scene has several cameras, ");
		printf("press space to change between them\n\n");
	}
	else
	{
		printf(GREEN_COLOR "\nScene successfully saved to BMP\n" RESET_COLOR);
		printf("The file has been saved into the \"images\" directory\n\n");
		exit(EXIT_SUCCESS);
	}
}

int			next_cam(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode != SP_KEY)
		return (0);
	if (mlx->cam->next)
	{
		mlx->cam = mlx->cam->next;
		mlx_put_image_to_window(
				mlx->mlx, mlx->win, mlx->cam->img_ptr, 0, 0);
	}
	else
	{
		mlx->cam = mlx->begin;
		mlx_put_image_to_window(
				mlx->mlx, mlx->win, mlx->cam->img_ptr, 0, 0);
	}
	return (1);
}


int			close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

void		graphic_loop(t_mlx mlx, t_scene data)
{
	mlx.win = mlx_new_window(mlx.mlx, data.xres, data.yres,
															"miniRT");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, 0);
	mlx_hook(mlx.win, KEYPRESS, KEYPRESSMASK, next_cam, &mlx);
	mlx_loop(mlx.mlx);
}

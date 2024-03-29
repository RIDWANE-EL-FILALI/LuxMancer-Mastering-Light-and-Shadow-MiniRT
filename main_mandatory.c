/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:37:28 by mghalmi           #+#    #+#             */
/*   Updated: 2024/02/08 15:03:00 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	error_message(char *str)
{
	printf(RED_COLOR "%s" RESET_COLOR, str);
	exit(1);
}

int	calc_pixel_color(int *edge_color, int last[2], t_wrapper *w)
{
	t_rss	rss;
	int		*color;

	rss.limit = 3;
	rss.xres = w->data.xres;
	rss.yres = w->data.yres;
	rss.i = w->i;
	rss.j = w->j;
	w->data.bgr = 0x202020;
	color = sample_pixel(edge_color, last, rss, w);
	if (color_difference(color[0], color[3])
		|| color_difference(color[1], color[2]))
		return (supersample(color, rss, w));
	return (average_supersampled_color(color));
}

void	last_thread_print_last(t_wrapper **w)
{
	if ((*w)->tid == NUM_THREADS - 1)
	{
		printf("\rRendering scene... (cam %d/%d) [100%%]\n", \
				(*w)->mlx.cam->idx, (*w)->data.cam_nb);
		return ;
	}
}

void	render_scene(t_wrapper **w)
{
	int	*edge_color;
	int	last[3];
	int	color;
	int	n;

	edge_color = malloc(sizeof(int) * ((*w)->data.xres + 2));
	if (!edge_color)
		error_message("malloc error");
	n = (*w)->data.yres / NUM_THREADS;
	(*w)->j = n * (*w)->tid;
	while ((*w)->j < (n * ((*w)->tid + 1)))
	{
		(*w)->i = 0;
		while ((*w)->i < (*w)->data.xres)
		{
			color = calc_pixel_color(edge_color, last, (*w));
			(*w)->mlx.cam->px_img[(*w)->j * (*w)->data.xres \
				+ (*w)->i++] = color;
		}
		(*w)->j++;
	}
	last_thread_print_last(w);
	free(edge_color);
}

int	main(int ac, char **av)
{
	t_wrapper	wrapper[NUM_THREADS];
	t_mlx		mlx;
	t_scene		scene;
	t_obj		*lst;

	if (ac < 2 || ac > 3)
		error_message("To run ./miniRT scenes/The scene \n");
	parse_scene_manda(&mlx, &scene, &lst, av);
	init_mlx(&mlx, &scene);
	wrapp_data(mlx, scene, lst, wrapper);
	rendering(wrapper);
	message_prompt(ac);
	graphic_loop(mlx, scene);
	return (0);
}

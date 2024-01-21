#include "main.h"

void error_message(char *str)
{
    printf(RED_COLOR "%s" RESET_COLOR, str);
    exit(1);
}

int			calc_pixel_color(int *edge_color, int last[2], t_wrapper *w)
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

void render_scene(t_wrapper *w)
{
    int edge_color[w->data.xres + 2];
    int last[3];
    int color;
    int n;

    n = w->data.yres / NUM_THREADS;
	w->j = n * w->tid;
	while (w->j < (n * (w->tid + 1)))
	{
		w->i = 0;
		while (w->i < w->data.xres)
		{
			color = calc_pixel_color(edge_color, last, w);
			w->mlx.cam->px_img[w->j * w->data.xres + w->i] = color;
			w->i++;
		}
		if (w->tid == NUM_THREADS - 1)
			printf("\rRendering scene... (cam %d/%d) [%d%%]",
			w->mlx.cam->idx, w->data.cam_nb, 100 * (w->j % n) / n);
		w->j++;
	}
	if (w->tid == NUM_THREADS - 1)
		printf("\rRendering scene... (cam %d/%d) [100%%]\n",
											w->mlx.cam->idx, w->data.cam_nb);
}

int main(int ac, char **av)
{
    t_wrapper	wrapper[NUM_THREADS];
    t_mlx mlx;
    t_scene scene;
    t_obj *lst;

    if (ac < 2 || ac > 3)
        error_message("To run this program make sure you have a .rt file well structured and run it like ./miniRT scenes/The scene \n");
    if (ac == 3 && ft_strcmp(av[2], "--save"))
        error_message("invalid arguments\n");
    parse_scene(&mlx, &scene, &lst, av);
    init_mlx(&mlx, &scene);
    wrapp_data(mlx, scene, lst, wrapper);
    rendering(wrapper);
    if (ac == 3)
        save_bmp(mlx, scene, av[1]);
    message_prompt(ac);
    graphic_loop(mlx, scene);
    return (0);
}


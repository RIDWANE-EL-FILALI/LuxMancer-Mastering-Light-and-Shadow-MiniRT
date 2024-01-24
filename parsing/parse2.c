#include "../main.h"

void		parse_res(t_scene *data, char **str)
{
	if (data->res_init > 0)
		error_message("Resolution (R) can only be declared once in the scene\n");
	else
		data->res_init = 1;
	next(str);
	data->xres = stoi(str);
	in_range(data->xres, 1, INFINITY, "resolution");
	data->yres = stoi(str);
	in_range(data->yres, 1, INFINITY, "resolution");
}

void		parse_ambient_light(t_scene *data, char **str)
{
	if (data->al_init > 0)
		error_message("Ambient lightning (A) can only be declared once in the scene\n");
	else
		data->al_init = 1;
	next(str);
	data->ambient_light = stof(str);
	in_range(data->ambient_light, 0, 1, "ambient lightning");
	data->al_color = parse_color(str);
}

void		parse_camera(t_mlx *mlx, t_scene *data, char **str)
{
	t_cam	*elem;
	t_cam	*begin;
	int			prev_idx;

	prev_idx = 0;
	begin = mlx->cam;
	elem = malloc(sizeof(t_cam));
	if (!elem)
		error_message("Error malloc failure in camera\n");
	elem->next = NULL;
	if (mlx->cam)
	{
		while (mlx->cam->next)
			mlx->cam = mlx->cam->next;
		prev_idx = mlx->cam->idx;
		mlx->cam->next = elem;
	}
	else
		mlx->cam = elem;
	next(str);
	elem->idx = prev_idx + 1;
	data->cam_nb = elem->idx;
	elem->o = parse_p3(str);
	elem->nv = normalize(parse_p3(str));
	elem->fov = stoi(str);
	in_range(elem->fov, 0, 180, "camera");
	if (begin)
		mlx->cam = begin;
	else
		mlx->cam = elem;
}

void		parse_light(t_scene **data, char **str)
{
	t_light	*elem;
	t_light	*list;
	t_light *begin;

	begin = (*data)->l;
	list = (*data)->l;
	elem = malloc(sizeof(t_light));
	if (!elem)
		error_message("Error malloc failure in parse light\n");
	elem->next = NULL;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elem;
		list = list->next;
	}
	else
		list = elem;
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

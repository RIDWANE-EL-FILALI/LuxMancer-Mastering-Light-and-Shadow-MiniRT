#include "../main.h"

void		parse_camera_manda(t_mlx *mlx, t_scene *data, char **str)
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
    if (prev_idx >= 1)
        error_message("Error only one camera allowed\n");
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

void		parse_light_manda(t_scene **data, char **str)
{
	t_light	*elem;
	t_light	*list;
	t_light *begin;
    int l;

    l = 0;
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
    while (begin)
    {
        l++;
        begin = begin->next;
    }
    if (l > 1)
        error_message("Error only one light allowed\n");
}

void parse_mandatory(t_mlx *mlx, t_scene *scene, t_obj **list, char **str)
{
    char *ret;

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
		parse_plane(list, &ret);
	*str = ret;
}

void parse_elements_manda(t_mlx *mlx, t_scene *scene, t_obj **list, char *str)
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
        error_message("Error in the map : not enought elements to render a scene \n");
}

void parse_scene_manda(t_mlx *mlx, t_scene *scene, t_obj **list, char **av)
{
    char *str;
    int fd;


    *list = NULL;
    scene->l = NULL;
    mlx->cam = NULL;
    write(1, "Iniciating parcing ...\n", 23);
    str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
        error_message("Error in allocating memory\n");
    if ((fd = open(av[1], 0)) == -1)
        error_message("Error openning the file given\n");
    str = line(str, fd);
    parse_elements_manda(mlx, scene, list, str);
    free(str);
}

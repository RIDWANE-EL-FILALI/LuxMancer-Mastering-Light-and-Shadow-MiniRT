#include "parse.h"

static void		parse2(t_obj **lst, char *str)
{
	if (*str == 'p' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_pyramid(lst, &str);
	else if (*str == 't' && *(str + 1) == 'r' && *(str++) && *(str++))
		parse_triangle(lst, &str);
}


static void parse(t_mlx *mlx, t_scene *scene, t_obj **list, char **str)
{
    char *ret;

    ret = *str;
    if (*ret == 'R' && *(ret++))
        parse_res(scene, &ret);
    else if (*ret == 'A' && *(ret++))
        parse_ambient_light(scene, &ret);
	else if (*ret == 'c' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_camera(mlx, scene, &ret);
	else if (*ret == 'c' && *(ret + 1) == 'y' && *(ret++) && *(ret++))
		parse_cylinder(list, &ret);
	else if (*ret == 'c' && *(ret + 1) == 'u' && *(ret++) && *(ret++))
		parse_cube(list, &ret);
	else if (*ret == 'l' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
		parse_light(&scene, &ret);
	else if (*ret == 's' && *(ret + 1) == 'p' && *(ret++) && *(ret++))
		parse_sphere(list, &ret);
	else if (*ret == 's' && *(ret + 1) == 'q' && *(ret++) && *(ret++))
		parse_square(list, &ret);
	else if (*ret == 'p' && *(ret + 1) == 'l' && *(ret++) && *(ret++))
		parse_plane(list, &ret);
	parse2(list , ret);
	*str = ret;
}

static void parse_elements(t_mlx *mlx, t_scene *scene, t_obj **list, char *str)
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
            parse(mlx, scene, list, &str);
        str++;
    }
    if (scene->res_init == 0 || scene->al_init == 0 || mlx->cam == NULL)
        error_message("Error in the map : not enought elements to render a scene \n");
}

void parse_scene(t_mlx *mlx, t_scene *scene, t_obj **list, char **av)
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
    parse_elements(mlx, scene, list, str);
    free(str);
}
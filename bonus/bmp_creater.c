/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creater.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:57:22 by mghalmi           #+#    #+#             */
/*   Updated: 2024/01/27 13:13:50 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	create_file(char *name, int i, int j)
{
	char	*bmpname;
	int		path;
	int		fd;

	path = 0;
	bmpname = (char *)malloc(ft_strlen(name) + 8);
	if (!bmpname)
		error_message("erroro creating file");
	while (name[i])
		if (name[i++] == '/')
			path++;
	i = 0;
	while (path && name[i])
		if (name[i++] == '/')
			path--;
	ft_strcat(bmpname, "images/");
	j = 7;
	while (name[i] && name[i] != '.')
		bmpname[j++] = name[i++];
	bmpname[j] = '\0';
	ft_strcat(bmpname, ".bmp");
	fd = check_fd(bmpname);
	free(bmpname);
	return (fd);
}

void	create_header(t_scene data, t_bmphead *header, t_dibhead *dib)
{
	header->type[0] = 0x42;
	header->type[1] = 0x4D;
	header->size = (data.xres * data.yres * 4) + 54;
	header->reserved = 0x00000000;
	header->offset = 0x36;
	dib->size = 40;
	dib->width = data.xres;
	dib->height = -data.yres;
	dib->colplanes = 1;
	dib->bpp = 32;
	dib->compression = 0;
	dib->img_size = (data.xres * data.yres * 4);
	dib->x_ppm = 2835;
	dib->y_ppm = 2835;
	dib->color_number = 0;
	dib->important_color = 0;
}

void	write_header(int fd, t_bmphead header, t_dibhead dib)
{
	write(fd, &header.type, 2);
	write(fd, &header.size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &dib.size, 4);
	write(fd, &dib.width, 4);
	write(fd, &dib.height, 4);
	write(fd, &dib.colplanes, 2);
	write(fd, &dib.bpp, 2);
	write(fd, &dib.compression, 4);
	write(fd, &dib.img_size, 4);
	write(fd, &dib.x_ppm, 4);
	write(fd, &dib.y_ppm, 4);
	write(fd, &dib.color_number, 4);
	write(fd, &dib.important_color, 4);
}

void	write_file(int fd, t_scene data, t_mlx mlx)
{
	char	*pixel_array;
	int		image_size;
	int		i;
	int		j;

	pixel_array = (char *)malloc(mlx.cam->size_line * data.yres);
	if (!pixel_array)
		error_message("error write a file");
	image_size = data.xres * data.yres;
	i = 0;
	j = 0;
	while (i < image_size)
	{
		pixel_array[j++] = mlx.cam->px_img[i] & 255;
		pixel_array[j++] = (mlx.cam->px_img[i] & 255 << 8) >> 8;
		pixel_array[j++] = (mlx.cam->px_img[i] & 255 << 16) >> 16;
		pixel_array[j++] = 0;
		i++;
	}
	write(fd, pixel_array, mlx.cam->size_line * data.yres);
	free(pixel_array);
}

void	save_bmp(t_mlx mlx, t_scene data, char *name)
{
	t_bmphead	header;
	t_dibhead	dib;
	int			fd;
	int			i;
	int			j;

	i = 0;
	j = 0;
	fd = create_file(name, i, j);
	create_header(data, &header, &dib);
	write_header(fd, header, dib);
	write_file(fd, data, mlx);
	close(fd);
}
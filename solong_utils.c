#include "solong.h"

// this function to heck the transparnsy of the pixel
int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

void	init_image(void *mlx, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		perror("Error: Failed to load image\n");
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}
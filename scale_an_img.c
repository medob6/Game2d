#include <solong.h>

void	scale_image(t_image *src, t_image *dest, float scale_factor)
{
	char *src_data;
	char *dest_data;

	int x, y;
	int src_x, src_y;
	src_data = mlx_get_data_addr(src->img, &src->bpp, &src->line_len,
			&src->endian);
	dest_data = mlx_get_data_addr(dest->img, &dest->bpp, &dest->line_len,
			&dest->endian);
	for (y = 0; y < dest->h; y++)
	{
		for (x = 0; x < dest->w; x++)
		{
			src_x = x / scale_factor;
			src_y = y / scale_factor;
			memcpy(&dest_data[(y * dest->line_len) + (x * (dest->bpp / 8))],
				&src_data[(src_y * src->line_len) + (src_x * (src->bpp / 8))],
				(src->bpp / 8));
		}
	}
}
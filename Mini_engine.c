// here i should create a fucntion that take two pictures  background and a charater and it will
// make character moving on the background

// first let's include mlx

#include "solong.h"

unsigned int	get_color(t_image img, int x, int y)
{
	int	offset;

	if (x < 0 || x >= img.w || y < 0 || y >= img.h)
		return (0);
	offset = (y * img.line_len) + (x * (img.bpp / 8));
	return (*(unsigned int *)(img.addr + offset));
}
void	my_mlx_pixel_put(t_image fram, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= TILE_SIZE || y < 0 || y >= TILE_SIZE)
		return ;
	dst = fram.addr + (y * fram.line_len + x * 4);
	*(unsigned int *)dst = color;
}

void	compose_frams(t_game *game,t_image fram ,int move_fram, int action_y, t_image img)
{
	unsigned int	color;
	unsigned int	bg_color;
	int				src_y;
	int				src_x;

	int x, y;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			bg_color = get_color(game->floor, x, y);
			src_y = action_y * TILE_SIZE + y;
			src_x = move_fram * TILE_SIZE + x;
			color = get_color(img, src_x, src_y);
			if (get_t(color) == 255)
				my_mlx_pixel_put(fram, x, y, bg_color);
			else
				my_mlx_pixel_put(fram, x, y, color);
			x++;
		}
		y++;
	}
}



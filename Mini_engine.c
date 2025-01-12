// here i should create a fucntion that take two pictures  background and a charater and it will
// make character moving on the background wherever his position in the map
#include "solong.h"

void	my_mlx_pixel_put(t_image fram, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = fram.addr + (y * fram.line_len + x * 4);
	*(unsigned int *)dst = color;
}
unsigned int	get_color(t_image img, int x, int y)
{
	int	offset;

	if (x < 0 || x >= img.w || y < 0 || y >= img.h)
		return (0);
	offset = (y * img.line_len) + (x * (img.bpp / 8));
	return (*(unsigned int *)(img.addr + offset));
}

void	get_bg_color(t_game *game, unsigned int *bg_color, int x, int y)
{
	if (game->player.action == 'r')
		*bg_color = get_color(game->background, game->player.x * 64 + x
				+ game->player.move_offset, (game->player.y) * 64 + y);
	else if (game->player.action == 'd')
		*bg_color = get_color(game->background, game->player.x * 64 + x,
				(game->player.y) * 64 + y + game->player.move_offset);
	else if (game->player.action == 'u')
		*bg_color = get_color(game->background, game->player.x * 64 + x,
				(game->player.y) * 64 + y - game->player.move_offset);
	else if (game->player.action == 'l')
		*bg_color = get_color(game->background, game->player.x * 64 + x
				- game->player.move_offset, (game->player.y) * 64 + y);
	else
		*bg_color = get_color(game->background, game->player.x * 64 + x,
				(game->player.y) * 64 + y);
	return ;
}

void	compose_frames(t_game *game, t_image fram, int move_fram, int action_y,
		t_image img)
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
			get_bg_color(game, &bg_color, x, y);
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

void	compose_frames_coin(t_game *game, t_image fram, int move_fram,
		int action_y, t_image img)
{
	unsigned int color;
	unsigned int bg_color;
	int src_y;
	int src_x;

	int x, y;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			bg_color = get_color(game->background, game->coin.x * 64 + x,
					game->coin.y * 64 + y);
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
void	compose_frames_exit(t_game *game, t_image fram, int move_fram,
		int action_y, t_image img)
{
	unsigned int color;
	unsigned int bg_color;
	int src_y;
	int src_x;

	int x, y;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			bg_color = get_color(game->background, game->exit.x * 64 + x,
					game->exit.y * 64 + y);
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
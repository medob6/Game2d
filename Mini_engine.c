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

	// if (x < 0 || x >= img.w || y < 0 || y >= img.h)
	// 	return (0);
	offset = (y * img.line_len) + (x * (img.bpp / 8));
	return (*(unsigned int *)(img.addr + offset));
}

void	get_bg_color(t_game *game, t_player *player, unsigned int *bg_color,
		int x, int y)
{
	if (player->action == 'r')
		*bg_color = get_color(game->background, player->x * TILE_SIZE + x
				+ player->move_offset, (player->y) * TILE_SIZE + y);
	else if (player->action == 'd')
		*bg_color = get_color(game->background, player->x * TILE_SIZE + x,
				(player->y) * TILE_SIZE + y + player->move_offset);
	else if (player->action == 'u')
		*bg_color = get_color(game->background, player->x * TILE_SIZE + x,
				(player->y) * TILE_SIZE + y - player->move_offset);
	else if (player->action == 'l')
		*bg_color = get_color(game->background, player->x * TILE_SIZE + x
				- player->move_offset, (player->y) * TILE_SIZE + y);
	else
		*bg_color = get_color(game->background, player->x * TILE_SIZE + x,
				(player->y) * TILE_SIZE + y);
}

void	compose_frames(t_game *game, t_player *player, int action_y)
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
			get_bg_color(game, player, &bg_color, x, y);
			src_y = action_y * TILE_SIZE + y;
			src_x = player->fram_nbr * TILE_SIZE + x;
			color = get_color(player->img, src_x, src_y);
			if (get_t(color) == 255)
				my_mlx_pixel_put(player->fram, x, y, bg_color);
			else
				my_mlx_pixel_put(player->fram, x, y, color);
			x++;
		}
		y++;
	}
}
// compose_frames_coin(game, game->coin.fram,
//	game->coin.fram_nbr,0,game->coin.img);
// void	compose_frames_coin(t_game *game, t_image fram, int move_fram,
// 		int action_y, t_image img)
// {
// 	unsigned int	color;
// 	unsigned int	bg_color;
// 	int				src_y;
// 	int				src_x;

// 	int x, y;
// 	y = 0;
// 	while (y < TILE_SIZE)
// 	{
// 		x = 0;
// 		while (x < TILE_SIZE)
// 		{
// 			bg_color = get_color(game->background, game->coin.x * TILE_SIZE + x,game->coin.y * TILE_SIZE + y);
// 			src_y = y;
// 			src_x = move_fram * TILE_SIZE + x;
// 			color = get_color(img, src_x, src_y);
// 			if (get_t(color) == 255)
// 				my_mlx_pixel_put(fram, x, y, bg_color);
// 			else
// 				my_mlx_pixel_put(fram, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }
void	compose_frames_coin(t_game *game, t_image fram, int move_fram,
		int action_y, t_image img, int coin_x, int coin_y)
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
			// Use coin_x and coin_y instead of game->coin.x and game->coin.y
			bg_color = get_color(game->background, coin_x * TILE_SIZE + x, coin_y * TILE_SIZE + y);
			src_y = y;
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
			bg_color = get_color(game->background, game->exit.y * TILE_SIZE + x,
					game->exit.x * TILE_SIZE + y);
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
void	chose_frames_floor(t_game *game, t_floor *floor)
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
			bg_color = get_color(game->wall, x, y);
			src_y = y;
			src_x = floor->fram_nbr * TILE_SIZE + x;
			color = get_color(floor->img, src_x, src_y);
			if (get_t(color) == 255)
				my_mlx_pixel_put(floor->fram, x, y, bg_color);
			else
				my_mlx_pixel_put(floor->fram, x, y, color);
			x++;
		}
		y++;
	}
}

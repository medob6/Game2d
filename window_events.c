#include "solong.h"

void	render_tile(t_game *game, t_image *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * TILE_SIZE, y
		* TILE_SIZE);
}

void	clear_fram(t_image fram)
{
	int	x;
	int	y;

	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			my_mlx_pixel_put(fram, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}
void	animate_player(t_game *game)
{
	game->frames_delay++;
	if (game->frames_delay >= 80)
	{
		game->frames_delay = 0;
		game->player.fram_nbr++;
		if (game->player.fram_nbr == 6)
			game->player.fram_nbr = 0;
		if (game->player.action == 'r')
			game->player.move_offset += TILE_SIZE / 12;
	}
	clear_fram(game->player.fram);
	if (game->player.action == 'r')
	{
		compose_frams(game, game->player.fram, game->player.fram_nbr, 1,
			game->player.img);
		if (game->player.move_offset >= TILE_SIZE)
		{
			game->player.move_offset = 0;
			game->player.action = 0;
			// if (check_next_position())
			game->player.x++;
		}
		else
		{
			render_tile(game, &game->floor, game->player.x, game->player.y);
			mlx_put_image_to_window(game->mlx, game->win, game->player.fram.img,
				(game->player.x * TILE_SIZE) + game->player.move_offset,
				game->player.y * TILE_SIZE);
			return ;
		}
	}
	else
	{
		compose_frams(game, game->player.fram, game->player.fram_nbr, 0,
			game->player.img);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player.fram.img,
		game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);
}

void	animate_collectible(t_game *game, int x, int y)
{
	clear_fram(game->coin.fram);
	compose_frams(game, game->coin.fram, 0, 0, game->coin.img);
	render_tile(game, &game->coin.fram, x, y);
}
void	animate_exit(t_game *game, int x, int y)
{
	clear_fram(game->exit.fram);
	compose_frams(game, game->exit.fram, 0, 0, game->exit.img);
	render_tile(game, &game->exit.fram, x, y);
}

// int		check_next_position(t_game game)
// {
// 	if (game->map.map[new_y][new_x] != '1')
// 	{
// 		if (game->map.map[new_y][new_x] == 'C')
// 		{
// 			game->coins++;
// 			game->map.map[new_y][new_x] = '0';
// 		}
// 		if (game->map.map[new_y][new_x] == 'E'
// 			&& game->coins == game->coins_total)
// 		{
// 			ft_printf("You won in %d moves!\n", ++game->moves);
// 			exit(0);
// 		}
// 		if (game->map.map[game->player_y][game->player_x] == 'P')
// 			game->map.map[game->player_y][game->player_x] = '0';
// 		if (game->map.map[new_y][new_x] == 'E')
// 			return (0);
// 		game->moves++;
// 		ft_printf("Moves: %d\n", game->moves);
// 	}
// }

// void animate_boombardement()
// {

// }

void	render_map(t_game *game)
{
	char	tile;

	int x, y;
	y = 0;
	while (y < game->map.map_h)
	{
		x = 0;
		while (x < game->map.map_w)
		{
			tile = game->map.map[y][x];
			if (tile == '0')
				render_tile(game, &game->floor, x, y);
			else if (tile == '1')
				render_tile(game, &game->wall, x, y);
			// here i must add a function that put a defirrent background based on the initial put of backgrounds
			else if (tile == 'C')
				animate_collectible(game, x, y);
			else if (tile == 'E')
				animate_exit(game, x, y);
			x++;
		}
		y++;
	}
	animate_player(game);
}

int	handle_input(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	// intead of checking player position each time i should ,
	// call functions that animate that movment then check if valid movment and update player position
	new_x = game->player.x;
	new_y = game->player.y;
	if (key == 65307)
		exit(0);
	else if (key == 119)
		new_y--;
	else if (key == 115)
		new_y++;
	else if (key == 97)
		new_x--;
	else if (key == 100)
	{
		game->player.action = 'r';
		// animate_player(game);
	}
	else
		return (0);
	if (game->map.map[new_y][new_x] != '1')
	{
		if (game->map.map[new_y][new_x] == 'C')
		{
			game->coin.collected++;
			game->map.map[new_y][new_x] = '0';
		}
		if (game->map.map[new_y][new_x] == 'E'
			&& game->coin.collected == game->coin.total)
		{
			// here instead of just pritn you won must put an animated won for some time then exit
			ft_printf("You won in %d moves!\n", ++game->player.moves);
			exit(0);
		}
		if (game->map.map[game->player.y][game->player.x] == 'P')
			game->map.map[game->player.y][game->player.x] = '0';
		if (game->map.map[new_y][new_x] == 'E')
			return (0);
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.moves++;
		ft_printf("Moves: %d\n", game->player.moves);
	}
	return (0);
}

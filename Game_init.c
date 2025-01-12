#include "solong.h"

int	handle_close(void *game)
{
	(void)game;
	// render_window_closing();
	ft_printf("Window closed.\n");
	exit(0);
	return (0);
}
void	initialize_game_resources(t_game *game)
{
	init_image(game->mlx, &game->player.img, "textures/player.xpm");
	init_image(game->mlx, &game->wall, "textures/floor1.xpm");
	init_image(game->mlx, &game->floor, "textures/floor2.xpm");
	init_image(game->mlx, &game->coin.img, "textures/coinsprit.xpm");
	init_image(game->mlx, &game->exit.img, "textures/door.xpm");
	return ;
}
void	init_background(t_game *game)
{
	game->background.w = game->map.map_w * TILE_SIZE;
	game->background.h = game->map.map_h * TILE_SIZE;
	game->background.img = mlx_new_image(game->mlx, game->background.w,
			game->background.h);
	game->background.addr = mlx_get_data_addr(game->background.img,
			&game->background.bpp, &game->background.line_len,
			&game->background.endian);
}
void	init_frams(t_game *game)
{
	game->player.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->player.fram.addr = mlx_get_data_addr(game->player.fram.img,
			&game->player.fram.bpp, &game->player.fram.line_len,
			&game->player.fram.endian);
	game->coin.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->coin.fram.addr = mlx_get_data_addr(game->coin.fram.img,
			&game->coin.fram.bpp, &game->coin.fram.line_len,
			&game->coin.fram.endian);
	game->exit.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->exit.fram.addr = mlx_get_data_addr(game->exit.fram.img,
			&game->exit.fram.bpp, &game->exit.fram.line_len,
			&game->exit.fram.endian);
	game->d_wall.farm.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->d_wall.farm.addr = mlx_get_data_addr(game->d_wall.farm.img,
			&game->d_wall.farm.bpp, &game->d_wall.farm.line_len,
			&game->d_wall.farm.endian);
	init_background(game);
}

void	render_tile_to_image(t_image buffer, t_image image, int x_p, int y_p)
{
	int	color;

	int x, y;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			color = get_color(image, x, y);
			if (!get_t(color))
				my_mlx_pixel_put(buffer, x_p * TILE_SIZE + x, y_p * TILE_SIZE
					+ y, color);
			x++;
		}
		y++;
	}
}

void	create_background_buffer(t_game *game)
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
			render_tile_to_image(game->background, game->floor, x, y);
			if (tile == '1')
				render_tile_to_image(game->background, game->wall, x, y);
			// else if (tile == 'E')
			// 	render_tile_to_image(game->background, game->exit.img, x, y);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	if (game->rerender_map)
	{
		create_background_buffer(game);
		mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0,
			0);
		game->rerender_map = 0;
	}
	// Animate entities
	animate_collectibles(game);
	// animate_exit(game);
	// animate_player(game);
	// game->frame_count++;
	// // if (game->frame_count % 8000 == 0)
	// 	animate_collectibles(game);
	// if (game->frame_count % 5000 == 0)
	// 	animate_exit(game);
	// if (game->frame_count % 6000 == 0)
	// 	animate_player(game);
	return (0);
}
int	main(int ac, char **av)
{
	t_game game;

	init_game(&game);
	initial_check(ac, check_map(&game, av[1]), game.map.error_msg);
	store_coin_positions(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (write(1, "Error initializing MLX\n", 23));
	game.win = mlx_new_window(game.mlx, game.map.map_w * TILE_SIZE,
			game.map.map_h * TILE_SIZE, "so_long");
	if (!game.win)
		return (perror("Error creating window\n"), 1);
	init_frams(&game);
	initialize_game_resources(&game);
	create_background_buffer(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.background.img, 0, 0);
	mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
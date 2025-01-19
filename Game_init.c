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
	init_image(game->mlx, &game->player.img, "textures/hero_sprites.xpm");
	init_image(game->mlx, &game->wall, "textures/Water.xpm");
	init_image(game->mlx, &game->floor.img, "textures/floor_sprite.xpm");
	init_image(game->mlx, &game->coin.img, "textures/coin_sprite.xpm");
	init_image(game->mlx, &game->d_wall.img, "textures/final_door.xpm");
	init_image(game->mlx, &game->winer, "textures/win_sprite.xpm");
	init_image(game->mlx, &game->player.dead, "textures/death_sprite.xpm");
	init_image(game->mlx, &game->loser, "textures/lose_sprite.xpm");
	init_image(game->mlx, &game->waves.img, "textures/waves_sprite.xpm");
	init_image(game->mlx, &game->enemy.img, "textures/enemy_sprites.xpm");
	init_image(game->mlx, &game->exit.img, "textures/Door.xpm");
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
	game->enemy.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->enemy.fram.addr = mlx_get_data_addr(game->enemy.fram.img,
			&game->enemy.fram.bpp, &game->enemy.fram.line_len,
			&game->enemy.fram.endian);
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
	game->floor.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->floor.fram.addr = mlx_get_data_addr(game->floor.fram.img,
			&game->floor.fram.bpp, &game->floor.fram.line_len,
			&game->floor.fram.endian);
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

int	chose_fram_nbr(t_map *map, int x, int y)
{
	unsigned char	binary;

	binary = 0;
	// Check right
	if (x + 1 < map->map_w && map->map[y][x + 1] == '1')
		binary |= 1;
	// Check up
	if (y - 1 >= 0 && map->map[y - 1][x] == '1')
		binary |= (1 << 1);
	// Check left
	if (x - 1 >= 0 && map->map[y][x - 1] == '1')
		binary |= (1 << 2);
	// Check down
	if (y + 1 < map->map_h && map->map[y + 1][x] == '1')
		binary |= (1 << 3);
	// printf("in index: x: %d y: %d we have tile: %d\n", x, y, binary);
	return (binary);
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
			game->floor.fram_nbr = chose_fram_nbr(&game->map, x, y);
			chose_frames_floor(game, &game->floor); // creted succefully
			// it does not add to the background
			render_tile_to_image(game->background, game->floor.fram, x, y);
			if (tile == '1')
				render_tile_to_image(game->background, game->wall, x, y);
			else if (tile == 'E')
			{
				render_tile_to_image(game->background, game->exit.img, x, y);
			}
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	clock_t	last_time;
	clock_t	curr_time;

	last_time = clock();
	if (game->rerender_map)
	{
		// create_background_buffer(game);
		mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0,
			0);
		game->rerender_map = 0;
	}
	curr_time = clock() - last_time;
	while ((double)curr_time / CLOCKS_PER_SEC < game->dt)
		curr_time = clock() - last_time;
	animate_collectibles(game);
	animate_exit(game);
	animate_player(game);
	animate_enemy(game);
	game->frame_count = 0;
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
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
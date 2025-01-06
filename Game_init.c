#include "solong.h"

int	handle_close(void *game)
{
	(void)game;
	// render_window_closing();
	printf("Window closed.\n");
	exit(0);
	return (0);
}
void	initialize_game_resorces(t_game *game)
{
	// change to chose a rand floor each time
	// i should have a collection of images that have multipel states of resores like colected and moving and effects and many more
	// all of this images have size 64 / 64 but i will fix that
	// should i use a struct to stor all player moves or just onne img
	init_image(game->mlx, &game->player.img, "textures/player.xpm");
	init_image(game->mlx, &game->wall, "textures/boarder.xpm");
	// init_image(game->mlx, &game->d_wall.img, "textures/d_wall.xpm");
	init_image(game->mlx, &game->floor, "textures/floor.xpm");
	init_image(game->mlx, &game->coin.img, "textures/collectible.xpm");
	init_image(game->mlx, &game->exit.img, "textures/exit.xpm");
	return ;
}

void	init_frams(t_game *game)
{
	// Initialize frame for the player
	game->player.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->player.fram.addr = mlx_get_data_addr(game->player.fram.img,
			&game->player.fram.bpp, &game->player.fram.line_len,
			&game->player.fram.endian);
	// Initialize frame for coins
	game->coin.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->coin.fram.addr = mlx_get_data_addr(game->coin.fram.img,
			&game->coin.fram.bpp, &game->coin.fram.line_len,
			&game->coin.fram.endian);
	// Initialize frame for the exit
	game->exit.fram.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->exit.fram.addr = mlx_get_data_addr(game->exit.fram.img,
			&game->exit.fram.bpp, &game->exit.fram.line_len,
			&game->exit.fram.endian);
	// Initialize frame for destructible walls (if needed)
	game->d_wall.farm.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	game->d_wall.farm.addr = mlx_get_data_addr(game->d_wall.farm.img,
			&game->d_wall.farm.bpp, &game->d_wall.farm.line_len,
			&game->d_wall.farm.endian);
	// Additional frames can be initialized similarly if required in the future
}
void	render_tile_to_image(t_image *buffer, t_image *fram, int x_p, int x_y)
{
	// here i should draw the image of size 64 x 64 tile size at the place
	int x,y;
	y = 0;
	while(y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			m
			x++;
		}
		y++;
	}
}
void	render_tile_to_buffer(t_image *buffer, t_game *game, int x, int y)
{
	char	tile;

	tile = game->map.map[y][x];
	if (tile == '0')
		render_tile_to_image(buffer, &game->floor, x, y);
	else if (tile == '1')
		render_tile_to_image(buffer, &game->wall, x, y);
	else if (tile == 'C')
		render_tile_to_image(buffer, &game->coin.img, x, y);
	else if (tile == 'E')
		render_tile_to_image(buffer, &game->exit.img, x, y);
}

void	create_background_buffer(t_game *game)
{
	int x, y;
	game->background.img = mlx_new_image(game->mlx, game->map.map_w * TILE_SIZE,
			game->map.map_h * TILE_SIZE);
	game->background.addr = mlx_get_data_addr(game->background.img,
			&game->background.bpp, &game->background.line_len,
			&game->background.endian);
	for (y = 0; y < game->map.map_h; y++)
	{
		for (x = 0; x < game->map.map_w; x++)
			render_tile_to_buffer(&game->background, game, x, y);
	}
}

int	game_loop(t_game *game)
{
	static int	frame_counter = 0;

	// Render the pre-rendered background
	mlx_put_image_to_window(game->mlx, game->win, game->background.img, 0, 0);
	// Handle animations every 80 frames
	if (++frame_counter % 80 == 0)
	{
		animate_player(game);
		animate_collectibles(game);
		animate_exit(game);
	}
	// Render player
	render_player(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game);
	initial_check(ac, check_map(&game, av[1]), game.map.error_msg);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (write(1, "Error initializing MLX\n", 23));
	game.win = mlx_new_window(game.mlx, game.map.map_w * TILE_SIZE,
			game.map.map_h * TILE_SIZE, "so_long");
	if (!game.win)
		return (perror("Error creating window\n"), 1);
	init_frams(&game);
	initialize_game_resources(&game);
	// Pre-render the static background
	create_background_buffer(&game);
	// Hook into the game loop and input handling
	mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
	mlx_key_hook(game.win, handle_input, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
// int	main(int ac, char **av)
// {
// 	t_game	game;

// 	init_game(&game);
// 	initial_check(ac, check_map(&game, av[1]), game.map.error_msg);
// 	game.mlx = mlx_init();
// 	if (!game.mlx)
// 		return (write(1, "Error initializing MLX\n", 23));
// 	game.win = mlx_new_window(game.mlx, game.map.map_w * TILE_SIZE,
// 			game.map.map_h * TILE_SIZE, "so_long");
// 	if (!game.win)
// 		return (fprintf(stderr, "Error creating window\n"), 1);
// 	init_frams(&game);
// 	// render_map(&game);
// 	initialize_game_resorces(&game);
// 	mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
// 	mlx_key_hook(game.win, handle_input, &game);
// 	mlx_hook(game.win, 17, 0, handle_close, &game);
// 	mlx_loop(game.mlx);
// 	// mlx_destroy_image(game.mlx, game.player.img);
// 	// mlx_destroy_image(game.mlx, game.fram.img);
// 	// mlx_destroy_window(game.mlx, game.win);
// 	return (0);
// }
// compile using :  cc -o window Game_init.c -L/path/to/mlx -lmlx -lX11 -lXext
//-lXrandr -lm -lpng && ./window
#include "solong.h"

// Rendering Functions

// These functions handle rendering elements on the screen.

void	render_tile(t_game *game, t_image *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * TILE_SIZE, y
		* TILE_SIZE);
}

static void	render_player_with_offset(t_game *game, int offset_x, int offset_y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->player.fram.img,
		(game->player.x * TILE_SIZE) + offset_x, (game->player.y * TILE_SIZE)
		+ offset_y);
}

void	render_all_coins(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->coin.total)
	{
		if (game->coins_x_y[i].exist == 1)
		{
			game->coin.x = game->coins_x_y[i].x;
			game->coin.y = game->coins_x_y[i].y;
			compose_frames_coin(game, game->coin.fram, game->coin.fram_nbr, 0,
				game->coin.img);
			render_tile(game, &game->coin.fram, game->coins_x_y[i].x,
				game->coins_x_y[i].y);
		}
		i++;
	}
}

// Player Movement and Animation

// These functions manage player actions and animations.

void	animate_player_frame(t_game *game)
{
	// game->frames_delay = 0;
	game->player.fram_nbr++;
	if (game->player.fram_nbr >= 6)
		game->player.fram_nbr = 0;
	if (ft_strchr("rlud", game->player.action) && game->player.action != 0)
		game->player.move_offset += TILE_SIZE / STEPS;
}

static void	reset_player_movement(t_game *game)
{
	game->player.move_offset = 0;
	game->player.action = 0;
}

static void	update_player_position(t_game *game, int dx, int dy)
{
	game->player.x += dx;
	game->player.y += dy;
	reset_player_movement(game);
}

void	animate_player(t_game *game)
{
	animate_player_frame(game);
	if (game->player.action == 'r')
		handle_movement(game, 1, 0, 1);
	else if (game->player.action == 'l')
		handle_movement(game, -1, 0, 1);
	else if (game->player.action == 'u')
		handle_movement(game, 0, -1, 1);
	else if (game->player.action == 'd')
		handle_movement(game, 0, 1, 1);
	else
	{
		compose_frames(game, game->player.fram, game->player.fram_nbr, 0,
			game->player.img);
		render_player_with_offset(game, 0, 0);
	}
}

// Coin Management

// These functions handle coin rendering, animation, and removal.

void	animate_coin_frame(t_game *game)
{
	// game->frames_delay = 0;
	game->coin.fram_nbr++;
	if (game->coin.fram_nbr >= 7)
		game->coin.fram_nbr = 1;
}

void	remove_coins_x_y(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->coin.total)
	{
		if (game->coins_x_y[i].x == x && game->coins_x_y[i].y == y)
		{
			game->coins_x_y[i].exist = 0;
		}
		i++;
	}
}
#define COIN_FRAME_DELAY 7000

static int	should_update_frame(int *counter, int delay)
{
	(*counter)++;
	if (*counter >= delay)
	{
		*counter = 0;
		return (1);
	}
	return (0);
}
void	animate_collectibles(t_game *game)
{
	if (should_update_frame(&game->frame_count, COIN_FRAME_DELAY))
	{
		game->coin.fram_nbr = (game->coin.fram_nbr + 1) % 7;
		render_all_coins(game);
	}
}
// void	animate_collectibles(t_game *game)
// {
// 	animate_coin_frame(game);
// 	game->coin.fram_nbr = (game->coin.fram_nbr + 1) % 7;
// 	render_all_coins(game);
// }

// Game Logic

// These functions manage game states, input handling, and player interaction.

int	check_next_position(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map.map[new_y][new_x];
	if (tile == '1')
		return (0);
	if (game->player.move_offset >= (TILE_SIZE / STEPS) * 10 && tile == 'C')
	{
		game->rerender_map = 0;
		game->coin.collected++;
		remove_coins_x_y(game, new_x, new_y);
		game->map.map[new_y][new_x] = '0';
	}
	return (1);
}

int	check_win(t_game *game, int next_x, int next_y)
{
	if (game->map.map[next_y][next_x] == 'E'
		&& game->coin.collected == game->coin.total)
		return (1);
	return (0);
}

void	handle_movement(t_game *game, int dx, int dy, int sprite)
{
	int	n;

	n = sprite;
	if (check_win(game, game->player.x + dx, game->player.y + dy))
	{
		if (game->player.move_offset >= (TILE_SIZE / STEPS * 10))
		{
			ft_printf("You won in %d moves!\n", ++game->player.moves);
			exit(0);
		}
		n = 1;
	}
	if (!check_next_position(game, game->player.x + dx, game->player.y + dy))
	{
		reset_player_movement(game);
	}
	if (game->map.map[game->player.y + dy][game->player.x + dx] == 'C'
		&& (game->player.move_offset >= (TILE_SIZE / STEPS * 5)))
		n = 1;
	else
		n = sprite;
	compose_frames(game, game->player.fram, game->player.fram_nbr, n,
		game->player.img);
	if (game->player.move_offset >= TILE_SIZE)
		update_player_position(game, dx, dy);
	else
		render_player_with_offset(game, dx * game->player.move_offset, dy
			* game->player.move_offset);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->player.action != 0 && check_next_position(game, new_x, new_y))
	{
		game->player.moves++;
		ft_printf("Moves: %d\n", game->player.moves);
	}
}

// Input Handling

// These functions process player input and control game actions.

int	handle_input(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	if (game->player.action != 0)
		return (1);
	new_x = game->player.x;
	new_y = game->player.y;
	if (key == KEY_ESCAPE)
		exit(0);
	if (key == KEY_UP || key == ARROW_UP)
	{
		game->player.action = 'u';
		new_y--;
	}
	else if (key == KEY_DOWN || key == ARROW_DOWN)
	{
		game->player.action = 'd';
		new_y++;
	}
	else if (key == KEY_LEFT || key == ARROW_LEFT)
	{
		game->player.action = 'l';
		new_x--;
	}
	else if (key == KEY_RIGHT || key == ARROW_RIGHT)
	{
		game->player.action = 'r';
		new_x++;
	}
	else
		return (0);
	move_player(game, new_x, new_y);
	return (0);
}

// Exit Animation

// Handles the animation for the game exit. ,
// only if coins all collected then exit is slowly opening then player go to it
void	animate_exit_frame(t_game *game)
{
	// game->frames_delay = 0;
	game->exit.fram_nbr++;
	if (game->exit.fram_nbr >= 3)
		return ;
}
void	animate_exit(t_game *game)
{
	if (game->coin.collected == game->coin.total)
	{
		animate_exit_frame(game);
		game->exit.fram_nbr++;
		if (game->exit.fram_nbr >= 4)
			game->exit.fram_nbr = 4;
	}
	compose_frames_exit(game, game->exit.fram, 0, game->exit.fram_nbr,
		game->exit.img);
	render_tile(game, &game->exit.fram, game->exit.y, game->exit.x);
}
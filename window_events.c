#include "solong.h"

// Rendering Functio
// }
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
static void	render_enemy_with_offset(t_game *game, int offset_x, int offset_y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->enemy.fram.img,
		(game->enemy.x * TILE_SIZE) + offset_x, (game->enemy.y * TILE_SIZE)
		+ offset_y);
}

t_image	create_empty_frame(t_game *game, int width, int height)
{
	t_image	frame;

	frame.img = mlx_new_image(game->mlx, width, height);
	if (!frame.img)
		perror("Error creating frame image"), exit(1);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len,
			&frame.endian);
	frame.w = width;
	frame.h = height;
	return (frame);
}
void	destroy_frame(t_game *game, t_image *frame)
{
	if (frame->img)
		mlx_destroy_image(game->mlx, frame->img);
}

void	render_all_coins(t_game *game)
{
	int		i;
	int		coin_x;
	int		coin_y;
	t_image	coin_frame;

	i = 0;
	while (i < game->coin.total)
	{
		if (game->coins_x_y[i].exist == 1)
		{
			coin_x = game->coins_x_y[i].x;
			coin_y = game->coins_x_y[i].y;
			coin_frame = create_empty_frame(game, TILE_SIZE, TILE_SIZE);
			compose_frames_coin(game, coin_frame, game->coin.fram_nbr, 0,
				game->coin.img, coin_x, coin_y);
			mlx_put_image_to_window(game->mlx, game->win, coin_frame.img, coin_x
				* TILE_SIZE, coin_y * TILE_SIZE);
			destroy_frame(game, &coin_frame);
		}
		i++;
	}
}

// Player Movement and Animation

// These functions manage player actions and animations.

static void	reset_player_movement(t_player *player)
{
	player->move_offset = 0;
	player->action = 0;
}

static void	update_player_position(t_player *player, int dx, int dy)
{
	player->x += dx;
	player->y += dy;
	reset_player_movement(player);
}
void	animate_player_frame(t_game *game)
{
	game->player.speed++;
	if (game->player.speed % 1 == 0)
	{
		game->player.fram_nbr++;
		if (game->player.fram_nbr >= 6)
			game->player.fram_nbr = 0;
		if (ft_strchr("rlud", game->player.action) && game->player.action != 0)
			game->player.move_offset += TILE_SIZE / STEPS;
	}
}
void	animate_player(t_game *game)
{
	static	sprite = 0;

	animate_player_frame(game);
	if (game->player.action == 'r')
	{
		sprite = 1;
		handle_movement(game, 1, 0, sprite);
	}
	else if (game->player.action == 'l')
	{
		sprite = 4;
		handle_movement(game, -1, 0, sprite);
	}
	else if (game->player.action == 'u')
	{
		if (sprite == 0)
			sprite = 1;
		handle_movement(game, 0, -1, sprite);
	}
	else if (game->player.action == 'd')
	{
		if (sprite == 0)
			sprite = 1;
		handle_movement(game, 0, 1, sprite);
	}
	else if (game->player.action == 0)
	{
		if (sprite == 4)
			compose_frames(game, &game->player, 3);
		else
			compose_frames(game, &game->player, 0);
		render_player_with_offset(game, 0, 0);
	}
	// check_collision_and_exit(game);
}

// Coin Management

// These functions handle coin rendering, animation, and removal.

void	animate_coin_frame(t_game *game)
{
	game->coin.speed++;
	if (game->coin.speed % 3 == 0)
		game->coin.fram_nbr = (game->coin.fram_nbr + 1) % 5;
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

void	animate_collectibles(t_game *game)
{
	animate_coin_frame(game);
	render_all_coins(game);
}

// Game Logic

// These functions manage game states, input handling, and player interaction.

int	check_next_position(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map.map[new_y][new_x];
	if (tile == '1' || (tile == 'E' && (game->exit.fram_nbr < 4)))
		return (0);
	if (game->player.move_offset >= (TILE_SIZE / STEPS) * 4 && tile == 'C')
	{
		// here istead of rerandering map i should rerender the tile where it was
		game->rerender_map = 1;
		game->coin.collected++;
		remove_coins_x_y(game, new_x, new_y);
		game->map.map[new_y][new_x] = '0';
	}
	return (1);
}
int	check_next_position_enemy(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map.map[new_y][new_x];
	if (tile == '1' || (tile == 'E'))
		return (0);
	return (1);
}

int	check_win(t_game *game, int next_x, int next_y)
{
	if (game->map.map[next_y][next_x] == 'E'
		&& game->coin.collected == game->coin.total)
		return (1);
	return (0);
}
void	hit_or_die(t_game *game, int dx, int dy, int sprite)
{
	int	n;

	n = 7;
	if (abs(game->enemy.y - game->player.y) <= 2 && game->enemy.x
		- game->player.x == 0)
	{
		n = 6;
		game->enemy_sprite = 5 * (sprite == 4) + 2 * (sprite == 1);
	}
	else if (abs(game->enemy.x - game->player.x) <= 2 && game->enemy.y
		- game->player.y == 0)
		game->enemy_sprite = 5 * (sprite == 4) + 2 * (sprite == 1);
	else
		game->enemy_sprite = sprite;
	if ((game->enemy.y + dy == game->player.y && game->enemy.x
			+ dx == game->player.x) && (game->enemy.move_offset >= (TILE_SIZE
				/ STEPS)))
	{
		game->enemy_sprite = 5 * (sprite == 4) + 2 * (sprite == 1);
		if (game->enemy.y + dy == game->player.y && game->enemy.x
			+ dx == game->player.x && game->enemy.move_offset >= (TILE_SIZE
				/ STEPS * 10))
		{
			game->end_game = 1;
		}
	}
}
void	handle_movement_enemy(t_game *game, int dx, int dy, int sprite)
{
	if (!check_next_position_enemy(game, game->enemy.x + dx, game->enemy.y
			+ dy))
	{
		reset_player_movement(&game->enemy);
	}
	hit_or_die(game, dx, dy, sprite);
	compose_frames(game, &game->enemy, game->enemy_sprite);
	if (game->enemy.move_offset >= TILE_SIZE)
		update_player_position(&game->enemy, dx, dy);
	else
		render_enemy_with_offset(game, dx * game->enemy.move_offset, dy
			* game->enemy.move_offset);
}

void	handle_movement(t_game *game, int dx, int dy, int sprite)
{
	int	n;

	n = sprite;
	if (check_win(game, game->player.x + dx, game->player.y + dy))
	{
		if (game->player.move_offset >= (TILE_SIZE / STEPS * 12))
		{
			game->player.moves++;
			game->end_game = 2;
			// ft_printf("You won in %d moves!\n", );
			// exit(0);
		}
	}
	if (game->player.y + dy == game->enemy.y && game->player.x
		+ dx == game->enemy.x && (game->player.move_offset >= (TILE_SIZE
				/ STEPS)))
	{
		if (game->player.move_offset >= (TILE_SIZE / STEPS * 6))
		{
			game->end_game = 1;
			// mlx_clear_window(game->mlx, game->win);
			// mlx_put_image_to_window(game->mlx, game->win, game->loser.img,
			// 	game->map.map_w * TILE_SIZE / 2 - game->loser.w / 2,
			// 	game->map.map_h * TILE_SIZE / 2 - game->loser.h / 2);
			// usleep(3000);
			printf("you died");
			// exit(0);
		}
	}
	if (!check_next_position(game, game->player.x + dx, game->player.y + dy))
	{
		reset_player_movement(&game->player);
	}
	if (game->map.map[game->player.y + dy][game->player.x + dx] == 'C'
		&& (game->player.move_offset >= (TILE_SIZE / STEPS)))
		n = 5 * (sprite == 4) + 2 * (sprite == 1);
	compose_frames(game, &game->player, n);
	if (game->player.move_offset >= TILE_SIZE)
		update_player_position(&game->player, dx, dy);
	else
		render_player_with_offset(game, dx * game->player.move_offset, dy
			* game->player.move_offset);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->player.action != 0 && check_next_position(game, new_x, new_y))
	{
		game->player.moves++;
		// ft_printf("Moves: %d\n", game->player.moves);
		// mlx_clear_window(game->mlx, game->win);
		render_tile(game, &game->wall, 0, 0);
		mlx_string_put(game->mlx, game->win, TILE_SIZE / 2, TILE_SIZE / 2,
			0xFF0000, ft_strjoin("Moves: ", ft_itoa(game->player.moves)));
		// the problem is when i put the new string it overide the older number
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
void	animate_enemy_frame(t_game *game)
{
	game->enemy.speed++;
	if (game->enemy.speed % 1 == 0)
	{
		game->enemy.fram_nbr++;
		if (game->enemy.fram_nbr >= 6)
			game->enemy.fram_nbr = 0;
		if (ft_strchr("rlud", game->enemy.action) && game->enemy.action != 0)
			game->enemy.move_offset += TILE_SIZE / 16;
	}
}

void	give_enemy_an_action(t_game *game)
{
	int			dx;
	int			dy;
	int			action;
	static int	has_seen_player;

	dx = game->player.x - game->enemy.x;
	dy = game->player.y - game->enemy.y;
	if (abs(dx) <= 2 && abs(dy) <= 2)
	{
		has_seen_player = 1;
	}
	if (has_seen_player)
	{
		if (abs(dx) > abs(dy))
		{
			if (dx > 0 && check_next_position(game, game->enemy.x + 1,
					game->enemy.y))
				game->enemy.action = 'r';
			else if (dx < 0 && check_next_position(game, game->enemy.x - 1,
					game->enemy.y))
				game->enemy.action = 'l';
		}
		else
		{
			if (dy > 0 && check_next_position(game, game->enemy.x, game->enemy.y
					+ 1))
				game->enemy.action = 'd';
			else if (dy < 0 && check_next_position(game, game->enemy.x,
					game->enemy.y - 1))
				game->enemy.action = 'u';
		}
	}
	else
	{
		action = rand() % 4;
		if (action == 0 && check_next_position_enemy(game, game->enemy.x + 1,
				game->enemy.y))
			game->enemy.action = 'r';
		else if (action == 1 && check_next_position_enemy(game, game->enemy.x
				- 1, game->enemy.y))
			game->enemy.action = 'l';
		else if (action == 2 && check_next_position_enemy(game, game->enemy.x,
				game->enemy.y - 1))
			game->enemy.action = 'u';
		else if (action == 3 && check_next_position_enemy(game, game->enemy.x,
				game->enemy.y + 1))
			game->enemy.action = 'd';
		else
			game->enemy.action = 'd';
	}
}

void	animate_enemy(t_game *game)
{
	animate_enemy_frame(game);
	if (game->enemy.action == 0)
		give_enemy_an_action(game);
	if (game->enemy.action == 'r')
	{
		game->enemy_sprite = 1;
		handle_movement_enemy(game, 1, 0, game->enemy_sprite);
	}
	else if (game->enemy.action == 'l')
	{
		game->enemy_sprite = 4;
		handle_movement_enemy(game, -1, 0, game->enemy_sprite);
	}
	else if (game->enemy.action == 'u')
	{
		if (game->enemy_sprite == 0)
			game->enemy_sprite = 1;
		handle_movement_enemy(game, 0, -1, game->enemy_sprite);
	}
	else if (game->enemy.action == 'd')
	{
		if (game->enemy_sprite == 0)
			game->enemy_sprite = 1;
		handle_movement_enemy(game, 0, 1, game->enemy_sprite);
	}
	else
	{
		compose_frames(game, &game->enemy, 0);
		render_enemy_with_offset(game, 0, 0);
	}
}

// Exit Animation

// Handles the animation for the game exit. ,
// only if coins all collected then exit is slowly opening then player go to it
void	animate_exit_frame(t_game *game)
{
	if (game->coin.collected == game->coin.total)
	{
		game->exit.speed++;
		if (game->exit.fram_nbr == 2)
		{
			if (game->exit.speed % 12 == 0)
			{
				game->exit.fram_nbr++;
				game->exit.speed = 0;
			}
		}
		else
		{
			if (game->exit.speed % 1 == 0)
			{
				if (game->exit.fram_nbr < 7)
				{
					game->exit.fram_nbr++;
					game->exit.speed = 0;
				}
			}
		}
	}
}

void	animate_exit(t_game *game)
{
	animate_exit_frame(game);
	compose_frames_exit(game, game->exit.fram, game->exit.fram_nbr, 0,
		game->exit.img);
	if (game->coin.collected == game->coin.total)
		render_tile_to_image(game->background, game->exit.fram, game->exit.y,
			game->exit.x);
	render_tile(game, &game->exit.fram, game->exit.y, game->exit.x);
}
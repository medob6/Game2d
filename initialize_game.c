#include "solong.h"

static void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->img.img = NULL;
	player->moves = 0;
	player->fram_nbr = 0;
	player->action = 0;
	player->fram.img = NULL;
	player->move_offset = 0;
	player->speed = 0;
}
static void	init_enemy(t_player *enemy)
{
	enemy->x = 0;
	enemy->y = 0;
	enemy->img.img = NULL;
	enemy->moves = 0;
	enemy->fram_nbr = 0;
	enemy->action = 0;
	enemy->fram.img = NULL;
	enemy->move_offset = 0;
	enemy->speed = 0;
}

static void	init_coin(t_coin *coin)
{
	coin->img.img = NULL;
	coin->fram_nbr = 0;
	coin->collected = 0;
	coin->total = 0;
	coin->fram.img = NULL;
	coin->speed = 0;
}

static void	init_exit(t_exit *exit)
{
	exit->img.img = NULL;
	exit->fram.img = NULL;
	exit->action = NULL;
	exit->fram_nbr = 0;
	exit->x = 0;
	exit->y = 0;
	exit->speed = 0;
}

static void	init_d_wall(t_d_wall *d_wall)
{
	d_wall->img.img = NULL;
	d_wall->farm.img = NULL;
	d_wall->d_wall_farm_nbr = 0;
}

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_h = 0;
	map->map_w = 0;
	map->error_msg = NULL;
	map->map_back_data = NULL;
}
static void	init_floor(t_floor *floor)
{
	floor->img.img = NULL;
	floor->fram.img = NULL;
	floor->fram_nbr = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_player(&game->player);
	init_enemy(&game->enemy);
	init_coin(&game->coin);
	init_exit(&game->exit);
	init_d_wall(&game->d_wall);
	init_floor(&game->floor);
	game->wall.img = NULL;
	game->dt = 1.0f / 15;
	init_map(&game->map);
	game->frame_count = 0;
	game->enemy_sprite = 1;
}

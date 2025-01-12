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
}

static void	init_coin(t_coin *coin)
{
	coin->img.img = NULL;
	coin->fram_nbr = 0;
	coin->collected = 0;
	coin->total = 0;
	coin->fram.img = NULL;
}

static void	init_exit(t_exit *exit)
{
	exit->img.img = NULL;
	exit->fram.img = NULL;
	exit->action = NULL;
	exit->fram_nbr = 0;
	exit->x = 0;
	exit->y = 0;
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

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_player(&game->player);
	init_coin(&game->coin);
	init_exit(&game->exit);
	init_d_wall(&game->d_wall);
	game->wall.img = NULL;
	game->floor.img = NULL;
	init_map(&game->map);
	game->frame_count = 0;
}

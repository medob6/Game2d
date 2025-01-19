// here i must code enemy code

// #include "solong.h"

// void	animate_enemy(t_game *game)
// {
// 	// here i must code code to animate enemy movments and check colision
// 	//+ if player  is dead must show dead player window
// 	animate_player_frame(game);
// 	if (game->enemy.action == 'r')
// 		handle_movement(game, 1, 0, 1);
// 	else if (game->enemy.action == 'l')
// 		handle_movement(game, -1, 0, 1);
// 	else if (game->enemy.action == 'u')
// 		handle_movement(game, 0, -1, 1);
// 	else if (game->enemy.action == 'd')
// 		handle_movement(game, 0, 1, 1);
// 	else
// 	{
// 		compose_frames(game, game->enemy.fram, game->enemy.fram_nbr, 0,
// 			game->enemy.img);
// 		render_player_with_offset(game, 0, 0);
// 	}
// 	return ;
// }
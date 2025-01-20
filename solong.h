#ifndef SOLONG_H
# define SOLONG_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

// Constants
# define TILE_SIZE 150
# define MIN_MAP_HEIGHT 3
# define MIN_MAP_WIDTH 3
# define MIN_MAP_SIZE 18
# define STEPS 12

// Key Codes
# define KEY_ESCAPE 65307
# define KEY_UP 119    // 'w'
# define KEY_DOWN 115  // 's'
# define KEY_LEFT 97   // 'a'
# define KEY_RIGHT 100 // 'd'
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363


// Struct Definitions
typedef struct s_image
{
	void			*img;
	char			*addr;
	int				w;
	int				h;
	int				bpp;
	int				line_len;
	int				endian;
}					t_image;

typedef struct s_map
{
	char			**map;
	int				map_w;
	int				map_h;
	char			*error_msg;
	char			**map_back_data;
}					t_map;

typedef struct s_player
{
	int				x;
	int				y;
	t_image			img;
	t_image			dead;
	unsigned int	moves;
	int				fram_nbr;
	char			action;
	t_image			fram;
	int				move_offset;
	int				speed;
}					t_player;

typedef struct s_exit
{
	t_image			img;
	t_image			fram;
	char			*action;
	int				x;
	int				y;
	int				fram_nbr;
	int				speed;
}					t_exit;

typedef struct s_coin
{
	t_image			img;
	int				fram_nbr;
	int				collected;
	int				x;
	int				y;
	int				total;
	t_image			fram;
	int				speed;
}					t_coin;

typedef struct s_d_wall
{
	t_image			img;
	t_image			farm;
	int				d_wall_farm_nbr;
}					t_d_wall;
typedef struct s_cordinant
{
	int				x;
	int				y;
	int				exist;
}					t_cordinant;
typedef struct s_floor
{
	t_image			img;
	t_image			fram;
	int				fram_nbr;
}					t_floor;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_player		enemy;
	t_coin			coin;
	t_exit			exit;
	t_d_wall		d_wall;
	t_image			wall;
	t_image			winer;
	t_image			loser;
	t_floor			floor;
	t_image			background;
	t_map			map;
	int				frame_count;
	int				rerender_map;
	float			dt;
	t_cordinant		*coins_x_y;
	t_cordinant		*enemy_x_y;
	int				enemy_sprite;
	int end_game;

}					t_game;

typedef struct s_flood
{
	char			**map;
	int				*coins_left;
	int				*exit_reachble;
}					t_flood;

// Function Prototypes

// Utilities
int	get_t(int trgb); // transparenssy

// Error Handling
void				initial_check(int args, int map_check, char *error);

// Map Control
int					check_map(t_game *game, char *path);

// Image Initialization
void				init_game(t_game *game);
void				init_image(void *mlx, t_image *img, char *path);
int					handle_input(int key, t_game *game);

// Animation and Motion
void				compose_frames(t_game *game, t_player *player,
						int action_y);
void				my_mlx_pixel_put(t_image fram, int x, int y, int color);
unsigned int		get_color(t_image img, int x, int y);
void				init_frams(t_game *game);
void				animate_player(t_game *game);
void				animate_enemy(t_game *game);
void				create_background_buffer(t_game *game);
void				animate_collectibles(t_game *game);
// void				compose_frames_coin(t_game *game, t_image fram,
// 						int move_fram, int action_y, t_image img);
void				compose_frames_coin(t_game *game, t_image fram,
						int move_fram, int action_y, t_image img, int coin_x,
						int coin_y);
void				compose_frames_exit(t_game *game, t_image fram,
						int move_fram, int action_y, t_image img);

// Coin Management
int					store_coin_positions(t_game *game);
// Exit Managment
void				animate_exit(t_game *game);

// Movement Handling
void				handle_movement(t_game *game, int dx, int dy, int sprite);
void				chose_frames_floor(t_game *game, t_floor *floor);
int					chose_fram_nbr(t_map *map, int x, int y);


#endif

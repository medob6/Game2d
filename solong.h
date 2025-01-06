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
# include <unistd.h>

# define TILE_SIZE 64
# define PLAYER_SPEED 4
# define MIN_MAP_HEIGHT 3
# define MIN_MAP_WIDTH 3
# define MIN_MAP_SIZE 18

// a banch of structs that that identfy path of a background
// i should have 4 background ok
# define green_grass Path_to_grass
# define yellow_grass Path_to_yellow_grass
# define harsh_green_grass Path_to_hgreen_grass
# define Rocky_land Path_to_rocky_land

// all this 4 backgrounds images must be in one image

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

// here add a struct for player , exit ,
// collictebels bisecly all things that need a backgroung or moving

typedef struct s_player
{
	int				x;
	int				y;
	t_image			img;
	unsigned int	moves;
	int				fram_nbr;
	char			action;
	t_image			fram;
	int				move_offset;

}					t_player;

// exit action open in animated way ,

typedef struct s_exit
{
	t_image			img;
	t_image			fram;
	char			*action;
	int				x;
	int				y;
	int				fram_nbr;
}					t_exit;

typedef struct s_coin
{
	t_image			img;
	int				fram_nbr;
	int				collected;
	int				total;
	t_image			fram;
}					t_coin;

typedef struct s_d_wall
{
	t_image			img;
	t_image			farm;
	int				d_wall_farm_nbr;
}					t_d_wall;
typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_coin			coin;
	t_exit			exit;
	t_d_wall		d_wall;
	t_image			wall;
	t_image			floor;
	t_image			background;
	t_map			map;
	int				frames_delay;
}					t_game;

struct				s_flood
{
	char			**map;
	int				*coins_left;
	int				*exit_reachble;
};

// mlx color utiles
int					get_t(int trgb);

// checks for errors
void				initial_check(int args, int map_check, char *error);

// map control functions
void				render_map(t_game *game);
int					check_map(t_game *game, char *path);

// image initializiation funcs
void				init_game(t_game *game);
void				init_image(void *mlx, t_image *img, char *path);
int					handle_input(int key, t_game *game);

// animation and motion
void				compose_frams(t_game *game, t_image fram, int movment_fram,
						int action_y, t_image img);
void				my_mlx_pixel_put(t_image fram, int x, int y, int color);
unsigned int		get_color(t_image img, int x, int y);
void				init_frams(t_game *game);
// void			animate_texture(t_game *game, char *act);
void				animate_player(t_game *game);
void				render_player(t_game *game);

#endif

// the goal of today is to creat a perfect game for non bonus
// smothe animation and error checking norminnette and all thing must be graet ok ;
// background  warping checking the back ground that must be put to the back of player
// save backgrounds positions
// add more structs and more good practices

// today must finish the playing part

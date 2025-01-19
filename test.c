#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCALE_FACTOR 3.5

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	src;
	t_image	dest;
}			t_game;

void	scale_image(t_image *src, t_image *dest, float scale_factor)
{
	char	*src_data;
	char	*dest_data;

	int x, y;
	int src_x, src_y;
	src_data = mlx_get_data_addr(src->img, &src->bpp, &src->line_len,
			&src->endian);
	dest_data = mlx_get_data_addr(dest->img, &dest->bpp, &dest->line_len,
			&dest->endian);
	for (y = 0; y < dest->height; y++)
	{
		for (x = 0; x < dest->width; x++)
		{
			src_x = x / scale_factor;
			src_y = y / scale_factor;
			memcpy(&dest_data[(y * dest->line_len) + (x * (dest->bpp / 8))],
				&src_data[(src_y * src->line_len) + (src_x * (src->bpp / 8))],
				(src->bpp / 8));
		}
	}
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
	{
		fprintf(stderr, "Error initializing MLX\n");
		return (1);
	}
	// Load the source image
	game.src.img = mlx_xpm_file_to_image(game.mlx, "textures/win_sprite.xpm",
			&game.src.width, &game.src.height);
	if (!game.src.img)
	{
		fprintf(stderr, "Error loading image\n");
		return (1);
	}
	// Create a window to display the image
	game.win = mlx_new_window(game.mlx, game.src.width * SCALE_FACTOR,
			game.src.height * SCALE_FACTOR, "Scaled Image");
	// Create the destination (scaled) image
	game.dest.img = mlx_new_image(game.mlx, game.src.width * SCALE_FACTOR,
			game.src.height * SCALE_FACTOR);
	if (!game.dest.img)
	{
		fprintf(stderr, "Error creating destination image\n");
		return (1);
	}
	game.dest.width = game.src.width * SCALE_FACTOR;
	game.dest.height = game.src.height * SCALE_FACTOR;
	// Scale the image
	scale_image(&game.src, &game.dest, SCALE_FACTOR);
	// Display the scaled image in the window
	mlx_put_image_to_window(game.mlx, game.win, game.dest.img, 0, 0);
	// Start the MLX loop
	mlx_loop(game.mlx);
	// Free resources (not reachable but important in a complete program)
	mlx_destroy_image(game.mlx, game.src.img);
	mlx_destroy_image(game.mlx, game.dest.img);
	mlx_destroy_window(game.mlx, game.win);
	return (0);
}

// i should use this scaling algo to wom game interface
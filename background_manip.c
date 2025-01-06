#include "solong.h"

// Function to shift the background image horizontally by 'step' pixels
t_image	make_new_background(t_game game, t_image back_ground, int step)
{
	t_image	fram;
	int		row;
	int		col;
	int		new_col;
	int		color;

	// Create a new image with the same dimensions as the background
	fram.img = mlx_new_image(game.mlx, back_ground.w, back_ground.h);
	fram.addr = mlx_get_data_addr(fram.img, &fram.bpp, &fram.line_len,
			&fram.endian);
	row = 0;
	while (row < back_ground.h)
	{
		col = 0;
		while (col < back_ground.w)
		{
			// Calculate the new column index with proper wrapping
			new_col = (col + step) % back_ground.w; // 0 + 5 % 64 = 5
			if (new_col < 0)
				new_col += back_ground.w; // Handle negative wrapping
			// Get the color from the original image and put it in the new image
			color = get_color(back_ground, new_col, row);
			my_mlx_pixel_put(&fram, col, row, color);
			col++;
		}
		row++;
	}
	return (fram);
}

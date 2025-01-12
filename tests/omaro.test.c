#include <math.h>
#include <mlx.h>
#include <stdlib.h>

#define WIN_W 1000
#define WIN_H 1000

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	double	zoom_factor;
	double	offset_x;
	double	offset_y;
	t_img	img;
}			t_data;

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	clear_image(t_img *img)
{
	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			put_pixel(img, x, y, 0x000000); // Black background
		}
	}
}

void	draw_scene(t_data *data)
{
	double	transformed_x;
	double	transformed_y;

	clear_image(&data->img);
	for (int y = 0; y < WIN_H; y++)
	{
		for (int x = 0; x < WIN_W; x++)
		{
			// Transform coordinates
			transformed_x = (x - data->offset_x) / data->zoom_factor;
			transformed_y = (y - data->offset_y) / data->zoom_factor;
			// Draw a shape (e.g., circle)
			if ((transformed_x - WIN_W / 2) * (transformed_x - WIN_W / 2) + (transformed_y - WIN_H / 2) * (transformed_y - WIN_H / 2) <= 100 * 100)
			{
				put_pixel(&data->img, x, y, 0x00FF0000); // Red color
			}
		}
	}
	// Display image in the window
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	mouse_zoom(int button, int x, int y, t_data *data)
{//10.10
	double	prev_zoom;

	prev_zoom = data->zoom_factor;
	if (button == 4)
	{ // Scroll up (zoom in)
		data->zoom_factor *= 1.1;
	}
	else if (button == 5)
	{ // Scroll down (zoom out)
		data->zoom_factor /= 1.1;
	}
	// Adjust offsets to keep mouse position constant during zoom
	data->offset_x = x + (data->offset_x - x) * (data->zoom_factor / prev_zoom);
	data->offset_y =  y + (data->offset_y - y) * (data->zoom_factor / prev_zoom);
	draw_scene(data);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_data data;

	data.zoom_factor = 1.0;
	data.offset_x = 0;
	data.offset_y = 0;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "Mouse Zoom");

	// Initialize image buffer
	data.img.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	// Initial draw
	draw_scene(&data);

	// Hooks
	mlx_hook(data.win, 17, 0, close_window, &data); // Close window
	mlx_mouse_hook(data.win, mouse_zoom, &data);    // Mouse zoom

	mlx_loop(data.mlx);
	return (0);
}
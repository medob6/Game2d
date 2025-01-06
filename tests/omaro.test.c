#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#define wi_w 1000
#define wi_h 1000

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
	void	*params[2];
	int		redius;
	t_img	img;
}			t_data;
int	put(t_data *data, int x, int y, int color)
{
	unsigned int	*change_val;

	if (x < 0 || y < 0 || x > wi_w || wi_h < y)
		return (0);
	change_val = (unsigned int *)(data->img.addr + ((y * data->img.line_len)
				+ (x * ((data->img.bpp) / 8))));
	*change_val = color;
	return (0);
}
int	draw_cer(t_data *data)
{
	double		i;
	int			x;
	int			y;
	double		o;
	int			r;
	static int	color = 0x00000000;

	i = 0;
	x = 0;
	y = 0;
	o = 0;
	while (y < wi_h)
	{
		while (x < wi_w)
		{
			put(data, x, y, 0x00000000);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
	r = data->redius;
	while (r > 0)
	{
		while (i < 360)
		{
			o = (i * M_PI) / 180;
			x = cos(o) * r + wi_w / 2;
			y = sin(o) * r + wi_h / 2;
			put(data, x, y, color++);
			i += 0.1;
		}
		i = 0;
		r--;
	}
	mlx_put_image_to_window(data->params[0], data->params[1], data->img.img, 0,
		0);
	return (0);
}
int	destroy(int code, t_data *data)
{
	if (code == 65307)
	{
		mlx_destroy_window(data->params[0], data->params[1]);
		exit(0);
	}
	return (0);
}
int	zoom(int code, int x, int y, t_data *data)
{
	if (code == 4)
		data->redius += 10;
	else if (code == 5)
		data->redius -= 10;
	return (0);
}
int	close_win(t_data *data)
{
	mlx_destroy_window(data->params[0], data->params[1]);
	exit(0);
	return (0);
}
int	main(void)
{
	t_data	data;

	data.redius = 100;
	data.params[0] = mlx_init();
	data.params[1] = mlx_new_window(data.params[0], wi_w, wi_h, "Omar");
	data.img.img = mlx_new_image(data.params[0], wi_w, wi_h);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_key_hook(data.params[1], destroy, &data);
	mlx_hook(data.params[1], 17, 0, close_win, &data);
	mlx_mouse_hook(data.params[1], zoom, &data);
	mlx_loop_hook(data.params[0], draw_cer, &data);
	mlx_loop(data.params[0]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:14:00 by mbousset          #+#    #+#             */
/*   Updated: 2025/01/12 10:43:42 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	calculate_map_h(char *path)
{
	char	*line;
	int		height;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	validate_enclosed_line(char *line, int w)
{
	return (line[0] == '1' && line[w - 1] == '1');
}

int	check_border(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01CEP", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*validate_map_item(t_game *game, char item, int *yx, int *items)
{
	if (item == 'P')
	{
		game->player.y = yx[0];
		game->player.x = yx[1];
		items[0]++;
	}
	else if (item == 'E')
	{
		game->exit.x = yx[0];
		game->exit.y = yx[1];
		items[1]++;
	}
	else if (item == 'C')
	{
		game->coin.total++;
		items[2]++;
	}
	else if (item == '0')
		items[3]++;
	else if (item != '1')
		return ("Invalid item in the map");
	return (NULL);
}

static char	*check_item_counts(int *items)
{
	if (items[0] != 1)
		return ("Can't have more or less than one player on the map. Are you Drank");
	if (items[1] != 1)
		return ("Can't have more or less than one exit. This isn't a maze for the lost!");
	if (items[2] == 0)
		return ("You need at least one coin to play. You're broke!");
	if (items[3] == 0)
		return ("Not enough space for the game");
	return (NULL);
}

char	*check_map_c_p_e(t_game *game)
{
	int		items[4] = {0, 0, 0, 0};
	char	*error;
	int		yx[2];

	yx[0] = 0;
	while (yx[0] < game->map.map_h)
	{
		yx[1] = 0;
		while (yx[1] < game->map.map_w)
		{
			error = validate_map_item(game, game->map.map[yx[0]][yx[1]], yx,
					items);
			if (error)
				return (error);
			yx[1]++;
		}
		yx[0]++;
	}
	return (check_item_counts(items));
}

char	**duplicate_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * height);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	flood_fill(t_flood *map_data, int x, int y)
{
	if (x < 0 || y < 0 || map_data->map[y] == NULL
		|| map_data->map[y][x] == '\0')
		return (0);
	if (map_data->map[y][x] == '1' || map_data->map[y][x] == 'V')
		return (0);
	if (map_data->map[y][x] == 'E')
	{
		*map_data->exit_reachble = 1;
		return (0);
	}
	if (map_data->map[y][x] == 'C')
	{
		(*map_data->coins_left)--;
	}
	map_data->map[y][x] = 'V';
	flood_fill(map_data, x + 1, y);
	flood_fill(map_data, x - 1, y);
	flood_fill(map_data, x, y + 1);
	flood_fill(map_data, x, y - 1);
	return (*map_data->coins_left == 0 && *map_data->exit_reachble);
}

int	store_coin_positions(t_game *game)
{
	int x, y, count;
	game->coins_x_y = malloc(game->coin.total * sizeof(t_cordinant));
	if (!game->coins_x_y)
		return (0);
	count = 0;
	y = 0;
	while (y < game->map.map_h)
	{
		x = 0;
		while (x < game->map.map_w)
		{
			if (game->map.map[y][x] == 'C')
			{
				game->coins_x_y[count].x = x;
				game->coins_x_y[count].y = y;
				game->coins_x_y[count].exist = 1;
				count++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_solvable(t_game *game)
{
	char	**copy;
	int		result;
	int		exit_reachable;
	int		coins_left;
	t_flood	floodfill_chek;

	exit_reachable = 0;
	coins_left = game->coin.total;
	copy = duplicate_map(game->map.map, game->map.map_h);
	if (!copy)
		return (0);
	floodfill_chek = (t_flood){copy, &coins_left, &exit_reachable};
	result = flood_fill(&floodfill_chek, game->player.x, game->player.y);
	free_map(copy, game->map.map_h);
	return (result);
}

static int	handle_map_error(t_game *game, char **map, char *msg, int i)
{
	if (map)
		free_map(map, i);
	game->map.error_msg = msg;
	return (0);
}

static int	validate_line_length(char *line, int width)
{
	return (ft_strlen(line) - (line[ft_strlen(line)
			- 1] == '\n') == (unsigned long)width);
}

static int	validate_map_line(char **map, char *line, t_game *game, int i)
{
	int	width;

	width = game->map.map_w;
	if (!line || (i == game->map.map_h - 1 && !check_border(line))
		|| !validate_line_length(line, width) || !validate_enclosed_line(line,
			width) || !check_line(line))
		return (handle_map_error(game, map, "Invalid map line", i));
	map[i] = line;
	return (1);
}

static int	read_map_lines(char **map, int fd, t_game *game)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	if (!line || !check_border(line))
		return (handle_map_error(game, map, "Invalid top border", 0));
	map[0] = line;
	game->map.map_w = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
	i = 1;
	while (i < game->map.map_h)
	{
		line = get_next_line(fd);
		if (!validate_map_line(map, line, game, i))
			return (0);
		i++;
	}
	map[game->map.map_h] = NULL;
	return (1);
}

static int	final_map_checks(t_game *game, char **map)
{
	char	*error_msg;

	game->map.map = map;
	error_msg = check_map_c_p_e(game);
	if (error_msg)
		return (handle_map_error(game, map, error_msg, game->map.map_h));
	if (!check_map_solvable(game))
		return (handle_map_error(game, map, "This map is unsolvable",
				game->map.map_h));
	return (1);
}

int	check_map(t_game *game, char *path)
{
	char	**map;
	int		fd;

	game->map.map_h = calculate_map_h(path);
	if (game->map.map_h <= 0)
		return (game->map.error_msg = "Empty map", 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (game->map.error_msg = "Invalid map path", 0);
	map = malloc(sizeof(char *) * (game->map.map_h + 1));
	if (!map)
		return (game->map.error_msg = "Memory allocation failed", 0);
	if (!read_map_lines(map, fd, game))
		return (0);
	close(fd);
	return (final_map_checks(game, map));
}
// int	main(int ac, char **av)
// {
// 	t_game	game;

// 	if (ac != 2)
// 	{
// 		printf("Error: Invalid number of arguments\n");
// 		return (1);
// 	}
// 	ft_bzero(&game, sizeof(t_game));
// 	if (!check_map(&game, av[1]))
// 	{
// 		printf("Error: %s\n", game.map.error_msg);
// 		return (1);
// 	}
// 	printf("Your map is great!\n");
// 	free_map(game.map.map, game.map.map_h);
// 	return (0);
// }

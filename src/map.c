/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:14:20 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/08 20:03:24 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	has_valid_extension(const char *filename, const char *extension)
{
	const char	*dot;

	if (!filename || !extension)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	return (ft_strncmp(dot + 1, extension, ft_strlen(dot + 1)) == 0);
}

static int	parse_dimensions(int fd, t_map *map)
{
	int		i;
	char	*trimmed;
	char	**x_tokens;

	while (1)
	{
		if (get_next_trimmed(&trimmed, fd, " \t\n") != 0)
			break ;
		x_tokens = ft_split(trimmed, ' ');
		free(trimmed);
		if (!x_tokens)
			return (close(fd), 0);
		i = 0;
		while (x_tokens[i])
			i++;
		free_tokens(x_tokens);
		if (map->x_dim == 0)
			map->x_dim = i;
		else if (i != map->x_dim)
			return (close(fd), 0);
		map->y_dim++;
	}
	lseek(fd, 0, SEEK_SET);
	return (1);
}

static t_point3D	*process_x_tokens(char **tokens, int x_dim, int y)
{
	int			x;
	t_point3D	*x_points;
	char		**token_x;

	x_points = ft_calloc(x_dim, sizeof(t_point3D));
	if (!x_points)
		return (NULL);
	x = -1;
	while (tokens[++x] && x < x_dim)
	{
		token_x = ft_split(tokens[x], ',');
		if (!token_x)
			return (free(x_points), NULL);
		if (token_x[1] && is_hex_color(token_x[1]))
			x_points[x] = (t_point3D){(float)x, (float)y, ft_atoi(token_x[0]),
				ft_strtol(token_x[1], NULL, 16)};
		else
			x_points[x] = (t_point3D){(float)x, (float)y, ft_atoi(token_x[0]),
				0xFFFFFF};
		free_tokens(token_x);
	}
	return (x_points);
}

static int	allocate_grid(int fd, t_map *map)
{
	int		y;
	char	*line;
	char	**x_tokens;

	map->grid = ft_calloc(map->y_dim, sizeof(t_point3D *));
	if (!map->grid)
		return (0);
	y = -1;
	while (++y < map->y_dim)
	{
		line = get_next_line(fd);
		if (!line)
			return (cleanup_grid(map->grid, y), 0);
		x_tokens = ft_split(line, ' ');
		free(line);
		if (!x_tokens)
			return (cleanup_grid(map->grid, y), 0);
		map->grid[y] = process_x_tokens(x_tokens, map->x_dim, y);
		free_tokens(x_tokens);
		if (!map->grid[y])
			return (cleanup_grid(map->grid, y), 0);
	}
	return (1);
}

t_map	*create_map(const char *filename)
{
	int		fd;
	t_map	*map;

	if (!has_valid_extension(filename, "fdf"))
		return (error("Map Initialization", "File is missing or inaccessible.",
				NULL), NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(map), error("Map Initialization", "Failed to open file.",
				NULL), NULL);
	if (!parse_dimensions(fd, map))
		return (close(fd), free(map), error("Map Initialization",
				"Invalid dimensions.", NULL), NULL);
	if (!allocate_grid(fd, map))
		return (close(fd), free(map), error("Map Initialization",
				"Failed to allocate grid.", NULL), NULL);
	close(fd);
	return (map);
}

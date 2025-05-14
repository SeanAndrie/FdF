/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:54:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:33:20 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_z_coordinate(t_point2D *coord, char **token_x,
		t_point3D **x_points, int z)
{
	if (token_x[1] && is_hex_color(token_x[1]))
		(*x_points)[coord->x] = (t_point3D){(float)coord->x, (float)coord->y, z,
			ft_strtol(token_x[1], NULL, 16)};
	else
		(*x_points)[coord->x] = (t_point3D){(float)coord->x, (float)coord->y, z,
			0xFFFFFF};
	free_tokens(token_x);
}

int	is_hex_color(const char *token)
{
	return (token && (!ft_strncmp(token, "0x", 2) || !ft_strncmp(token, "0X",
				2)));
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	cleanup_grid(t_point3D **grid, int x_alloc)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < x_alloc)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

int	get_next_trimmed(char **trimmed, int fd, char *charset)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	*trimmed = ft_strtrim(line, charset);
	free(line);
	if (!*trimmed)
		return (-1);
	return (0);
}

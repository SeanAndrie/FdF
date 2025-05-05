/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:54:21 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/05 01:03:54 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_hex_color(const char *token)
{
	return (token && (!ft_strncmp(token, "0x", 2) || !ft_strncmp(token, "0X",
				2)));
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

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

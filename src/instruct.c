/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:46:06 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/14 13:32:38 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	keyboard_instruct(t_mlx_data *mlx, int *y, int line_height)
{
	mlx_string_put(mlx->connection, mlx->window, 20, *y, TEXT_COLOR,
		"Keyboard:");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"Esc: Quit");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"i/p/o: Switch Projection");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"Shift + Arrows: Rotate");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"Arrows: Adjust Z Scale");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"W/A/S/D: Move");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"+/-: Zoom");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"1/2/3: Ortho Modes (if active)");
}

static void	mouse_instruct(t_mlx_data *mlx, int *y, int line_height)
{
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 20, *y, TEXT_COLOR, "Mouse:");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"Left-Click + Drag: Pan");
	*y += line_height;
	mlx_string_put(mlx->connection, mlx->window, 40, *y, TEXT_COLOR,
		"Scroll: Zoom");
	*y += line_height;
}

void	render_instruct(t_mlx_data *mlx, int line_height)
{
	int	y;

	y = 20;
	mlx_string_put(mlx->connection, mlx->window, 30, y, TEXT_COLOR,
		"=== Controls (R to Reset) ===");
	mouse_instruct(mlx, &y, line_height);
	y += line_height;
	keyboard_instruct(mlx, &y, line_height);
}

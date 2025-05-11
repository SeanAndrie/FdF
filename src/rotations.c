/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:17 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/12 01:55:57 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void apply_ortho_variations(int keycode, t_mlx_data *mlx)
{   
    if (keycode == XK_1)
        mlx->config.rotations = (t_point3D){0, 0, 0, 0xFF};
    else if (keycode == XK_2)
        mlx->config.rotations = (t_point3D){90.0f, 0, 0, 0xFF};
    else if (keycode == XK_3)
        mlx->config.rotations = (t_point3D){90.0f, 0, -90.0f, 0xFF};
    redraw(mlx);
}

void    rotate_x(t_point3D *point, float angle)
{
    float y;
    float rad;

    y = point->y;
    rad = angle * M_PI / 180.0f;
    point->y = y * cos(rad) - point->z * sin(rad);
    point->z = y * sin(rad) + point->z * cos(rad);
}

void    rotate_y(t_point3D *point, float angle)
{
    float x;
    float rad;

    x = point->x;
    rad = angle * M_PI / 180.0f;
    point->x = x * cos(rad) + point->z * sin(rad);
    point->z = -x * sin(rad) + point->z *cos(rad);
}

void    rotate_z(t_point3D *point, float angle)
{
    float x;
    float rad;
    
    x = point->x;
    rad = angle * M_PI / 180.0f;
    point->x = x * cos(rad) - point->y * sin(rad);
    point->y = x * sin(rad) + point->y * cos(rad);
}

void    rotate_point(t_point3D *point, t_point3D angles)
{
    rotate_z(point, angles.z);
    rotate_y(point, angles.y);
    rotate_x(point, angles.x);
}

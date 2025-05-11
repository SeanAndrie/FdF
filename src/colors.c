/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:54:55 by sgadinga          #+#    #+#             */
/*   Updated: 2025/05/10 07:08:30 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_image(t_image *img, int width, int height, unsigned int color)
{
	size_t 					i;
	size_t 					bytes;
	volatile unsigned int	*p;

	i = 0;
	bytes = width * height * (img->bpp / 8);
	p = (unsigned int *)img->addr;
	while (i < bytes/sizeof(unsigned int))
	{
		p[i]   = color; p[i+1] = color; p[i+2] = color; p[i+3] = color;
        p[i+4] = color; p[i+5] = color; p[i+6] = color; p[i+7] = color;
		i += 8;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color_param(int trgb, t_color param)
{
	return ((trgb >> param) & 0xFF);
}

t_rgb	int_to_rgb(int n)
{
	t_rgb	rgb;

	rgb.r = get_color_param(n, R);
	rgb.g = get_color_param(n, G);
	rgb.b = get_color_param(n, B);
	return (rgb);
}

float	calculate_interpolation(t_point2D *curr, t_point2D *start,
		t_point2D *end)
{
	t_point2D	delta;

	delta.x = end->x - start->x;
	delta.y = end->y - start->y;
	if (abs(delta.x) > abs(delta.y))
	{
		if (delta.x != 0)
			return ((float)(curr->x - start->x) / delta.x);
	}
	else
	{
		if (delta.y != 0)
			return ((float)(curr->y - start->y) / delta.y);
	}
	return (0.0f);
}

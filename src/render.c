/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 09:28:40 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	put_pixel(t_frac *f, int x, int y, int color)
{
	char	*p;

	p = f->buf + y * f->line + x * (f->bpp / 8);
	*(int *)p = color;
}

static double	map_r(t_frac *f, int x)
{
	double	r;

	r = f->min_r + (f->max_r - f->min_r)
		* ((double)x / (WIDTH - 1));
	return (r);
}

static double	map_i(t_frac *f, int y)
{
	double	i;

	i = f->max_i + (f->min_i - f->max_i)
		* ((double)y / (HEIGHT - 1));
	return (i);
}

void	render(t_frac *f)
{
	int		x;
	int		y;
	int		n;
	t_cpx	z;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (f->set == MANDELBROT)
				n = iter_mandel(map_r(f, x), map_i(f, y), &z, f->max_iter);
			else
				n = iter_julia(f, map_r(f, x), map_i(f, y), &z);
			put_pixel(f, x, y, get_color(f, n, z.r, z.i));
			x++;
		}
		y++;
	}
}

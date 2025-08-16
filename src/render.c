/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 13:54:38 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	put_pixel(t_frac *f, int x, int y, int color)
{
	char	*p;

	p = f->buf + y * f->line + x * (f->bpp / 8);
	*(int *)p = color;
}

/* map_r:
Maps a horizontal pixel coordinate x (0..WIDTH-1) to its
corresponding real-axis value in the complex plane based on
the current view window [min_r..max_r]. Uses linear interpolation
so the leftmost pixel maps to min_r and the rightmost pixel maps
to max_r.
*/
static double	map_r(t_frac *f, int x)
{
	double	r;

	r = f->min_r + (f->max_r - f->min_r)
		* ((double)x / (WIDTH - 1));
	return (r);
}

/* map_i:
Maps a vertical pixel coordinate y (0..HEIGHT-1) to its
corresponding imaginary-axis value in the complex plane based
on the current view window [min_i..max_i]. Uses linear interpolation
with inverted direction so the top pixel maps to max_i and the
bottom pixel maps to min_i, matching screen coordinates.
*/
static double	map_i(t_frac *f, int y)
{
	double	i;

	i = f->max_i + (f->min_i - f->max_i)
		* ((double)y / (HEIGHT - 1));
	return (i);
}

/*
Iterates over every pixel in the window, maps its (x,y) coordinates to
the corresponding point in the complex plane, computes the number of
iterations before escape for the selected fractal set, converts that
result to a color, and writes it into the image buffer.
*/
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

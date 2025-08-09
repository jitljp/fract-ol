/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 14:03:48 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	put_pixel(t_frac *f, int x, int y, int color)
{
	char	*p;

	p = f->buf + y * f->line + x * (f->bpp / 8);
	*(int *)p = color;
}

static int	iter_mandel(double cr, double ci, t_cpx *z, int max_iter)
{
	int		n;
	double	tmp;
	double	zr2;
	double	zi2;

	n = 0;
	z->r = 0.0;
	z->i = 0.0;
	zr2 = 0.0;
	zi2 = 0.0;
	while (n < max_iter && (zr2 + zi2) <= 4.0)
	{
		tmp = z->r * z->r - z->i * z->i + cr;
		z->i = 2.0 * z->r * z->i + ci;
		z->r = tmp;
		zr2 = z->r * z->r;
		zi2 = z->i * z->i;
		n++;
	}
	return (n);
}

int	iter_julia(t_frac *f, double zr, double zi, t_cpx *z)
{
	int		n;
	double	tmp;
	double	zr2;
	double	zi2;

	n = 0;
	z->r = zr;
	z->i = zi;
	zr2 = zr * zr;
	zi2 = zi * zi;
	while (n < f->max_iter && (zr2 + zi2) <= 4.0)
	{
		tmp = z->r * z->r - z->i * z->i + f->cr;
		z->i = 2.0 * z->r * z->i + f->ci;
		z->r = tmp;
		zr2 = z->r * z->r;
		zi2 = z->i * z->i;
		n++;
	}
	return (n);
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

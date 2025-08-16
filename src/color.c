/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:23 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/16 11:53:40 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
get_color:
	Map raw iteration count n to an RGB color with a cosine palette.
	- If n >= max_iter, return black (inside the set).
	- Else, compute a hue angle from n and f->shift, then build RGB.
	No smoothing and no modulo stripes are used here.
*/
int	get_color(t_frac *f, int n)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (n >= f->max_iter)
		return (0x000000);
	t = ((double)(n * 3) + (double)f->shift) * 0.01745329252;
	r = (int)((0.5 + 0.5 * cos(t)) * 255.0);
	g = (int)((0.5 + 0.5 * cos(t + 2.094395102)) * 255.0);
	b = (int)((0.5 + 0.5 * cos(t + 4.188790205)) * 255.0);
	return ((r << 16) | (g << 8) | b);
}

int	mix_colors(int a, int b, double t)
{
	int		res;
	int		av;
	int		bv;
	int		t8;

	res = 0;
	t8 = (int)(t * 256.0);
	av = (a >> 16) & 255;
	bv = (b >> 16) & 255;
	res |= ((av + (((bv - av) * t8) >> 8)) << 16);
	av = (a >> 8) & 255;
	bv = (b >> 8) & 255;
	res |= ((av + (((bv - av) * t8) >> 8)) << 8);
	av = a & 255;
	bv = b & 255;
	res |= (av + (((bv - av) * t8) >> 8));
	return (res);
}

void	color_shift(t_frac *f)
{
	f->shift = (f->shift + 10) % 360;
}

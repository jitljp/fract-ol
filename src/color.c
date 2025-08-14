/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:23 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 09:26:09 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* mu:
*	Smooth iteration count for deep gradients.
*/
static double	mu(double zr, double zi, int n)
{
	double	r2;
	double	m;

	r2 = zr * zr + zi * zi;
	if (r2 < 1e-10)
		return ((double)n);
	m = (double)n + 1.0 - (log(log(sqrt(r2))) / log(2.0));
	if (m < 0.0)
		m = 0.0;
	return (m);
}

/* wheel_color:
*	Smooth rainbow using cosine palette and a degree-like shift.
*/
static int	wheel_color(double m, int shift)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (m + (double)shift) * 0.01745329252;
	r = (int)((0.5 + 0.5 * cos(t + 0.0)) * 255.0);
	g = (int)((0.5 + 0.5 * cos(t + 2.094395102)) * 255.0);
	b = (int)((0.5 + 0.5 * cos(t + 4.188790205)) * 255.0);
	return ((r << 16) | (g << 8) | b);
}

/* get_color:
*	Return RGB for a pixel from n and (zr,zi).
*/
int	get_color(t_frac *f, int n, double zr, double zi)
{
	double	m;

	if (n >= f->max_iter)
		return (0x000000);
	m = mu(zr, zi, n);
	return (wheel_color(m * 3.0, f->shift));
}

/* mix_colors:
*	Linear blend between two RGB colors. t in [0,1].
*/
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

/* color_shift:
*	Rotate the palette (bonus: color range shift).
*/
void	color_shift(t_frac *f)
{
	f->shift = (f->shift + 10) % 360;
}

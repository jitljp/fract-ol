/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:23 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:12:15 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* set_base_color:
*	Update mono base color safely.
*/
void	set_base_color(t_frac *f, int color)
{
	f->base_color = color;
	if (f->base_color == 0x000000)
		f->base_color = 0x333333;
}

/* mu:
*	Smooth iteration count for deep gradients.
*/
static double	mu(double zr, double zi, int n)
{
	double	r2;
	double	m;

	r2 = zr * zr + zi * zi;
	m = (double)n + 1.0 - (log(log(sqrt(r2))) / log(2.0));
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

	if (n >= MAX_ITERS)
		return (0x000000);
	m = mu(zr, zi, n);
	if (f->palette_mode == 0)
		return (wheel_color(m * 6.0, f->shift));
	if (f->palette_mode == 1)
		return (color_mono(m, f->base_color));
	return (color_multi(m));
}

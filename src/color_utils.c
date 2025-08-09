/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:20 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:17:00 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

/* color_mono:
*	Base color to white ramp (pleasant, simple).
*/
int	color_mono(double m, int base)
{
	double	t;

	if (m < 0.0)
		t = 0.0;
	else if (m > 60.0)
		t = 1.0;
	else
		t = m / 60.0;
	return (mix_colors(base, 0xFFFFFF, t));
}

/* color_multi:
*	Fixed 4-stop ramp: black -> blue -> orange -> white.
*/
int	color_multi(double m)
{
	const int	c[4] = {0x000000, 0x1f77b4, 0xff7f0e, 0xffffff};
	double				t;

	if (m < 0.0)
		t = 0.0;
	else if (m > 60.0)
		t = 1.0;
	else
		t = m / 60.0;
	if (t < 0.33)
		return (mix_colors(c[0], c[1], t / 0.33));
	if (t < 0.66)
		return (mix_colors(c[1], c[2], (t - 0.33) / 0.33));
	return (mix_colors(c[2], c[3], (t - 0.66) / 0.34));
}

/* color_shift:
*	Rotate the palette (bonus: color range shift).
*/
void	color_shift(t_frac *f)
{
	f->shift = (f->shift + 10) % 360;
}

/* next_palette:
*	Cycle palette mode: wheel -> mono -> multi.
*/
void	next_palette(t_frac *f)
{
	f->palette_mode = (f->palette_mode + 1) % 3;
}

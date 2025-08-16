/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:49:23 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/16 13:24:01 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Convert the iteration count of a pixel into an RGB color.
If the point never escapes (n >= max_iter), the pixel is black.
Otherwise, compute a phase value t = (n*3 + shift) * π/180,
which advances steadily with n and can be rotated by shift.
This phase t is passed into cosine waves that oscillate smoothly
between 0 and 255.
Red uses cos(t) with no offset
Green uses cos(t + 2π/3)) (shifted 120 degrees)
Blue uses cos(t + 4π/3)) (shifted by 240 degrees)
*/
int	get_color(t_frac *f, int n)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (n >= f->max_iter)
		return (0x000000);
	t = ((double)(n * 3) + (double)f->shift) * 0.015;
	r = (int)((0.5 + (0.5 * cos(t))) * 255.0);
	g = (int)((0.5 + (0.5 * cos(t + 2.094395102))) * 255.0);
	b = (int)((0.5 + (0.5 * cos(t + 4.188790205))) * 255.0);
	return ((r << 16) | (g << 8) | b);
}

/*
Increment the global color phase by 10 degrees.
f->shift stores a hue offset in degrees, used in get_color()
  to rotate the RGB cosine waves that generate the palette.
Each call adds 10, then wraps around with % 360 so the value
  always stays between 0 and 359.
Effect: cycles the fractal’s colors smoothly without changing
  the fractal itself, creating the “color range shift” bonus.
*/
void	color_shift(t_frac *f)
{
	f->shift = (f->shift + 10) % 360;
}

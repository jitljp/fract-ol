/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:28:22 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/16 12:00:48 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Create a new image buffer using MiniLibX and store its pointer in f->img.
Also retrieve the image's raw pixel buffer address, bits per pixel,
line length (stride), and endian setting, storing them in the t_frac struct.
Returns 0 on success or an error code if image creation
	or buffer retrieval fails.
*/
int	init_img(t_frac *f)
{
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		return (msg("Image creation error.", 1));
	f->buf = mlx_get_data_addr(f->img, &f->bpp, &f->line_bytes, &f->endian);
	if (!f->buf)
		return (msg("Buffer address error.", 1));
	return (0);
}

void	reinit_img(t_frac *f)
{
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	f->img = NULL;
	f->buf = NULL;
	init_img(f);
}

/*
Perform the Mandelbrot iteration for a single complex coordinate (cr, ci).
Starts with z = 0 and repeatedly applies z = z^2 + c, stopping when either
the magnitude of z exceeds 2 (|z|^2 > 4) or the maximum iteration count is
reached. Returns the number of iterations performed, which is later used
to determine pixel color: high counts indicate points near or inside the set,
while low counts indicate points that quickly escape.
*/
int	iter_mandel(double cr, double ci, int max_iter)
{
	int		n;
	double	zr;
	double	zi;
	double	tmp;

	n = 0;
	zr = 0.0;
	zi = 0.0;
	while (n < max_iter && ((zr * zr) + (zi * zi)) <= 4.0)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = tmp;
		n++;
	}
	return (n);
}

/*
Compute the iteration count for one point in the Julia set.
- Input: fractal context f (with Julia constant cr + ci*i),
  pixel coordinates mapped into complex plane (zr, zi),
  and a complex struct z for temporary storage.
- Process: repeatedly apply z = z^2 + c until either
  (a) the point escapes (|z| > 2, i.e. zr^2+zi^2 > 4),
  or (b) the maximum iteration budget is reached.
- Output: the number of iterations taken before escape,
  used later to determine the pixel’s color.
*/
int	iter_julia(t_frac *f, double zr, double zi)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < f->max_iter && ((zr * zr) + (zi * zi)) <= 4.0)
	{
		tmp = zr * zr - zi * zi + f->cr;
		zi = 2.0 * zr * zi + f->ci;
		zr = tmp;
		n++;
	}
	return (n);
}

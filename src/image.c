/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:28:22 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 13:17:07 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Create a new image buffer using MiniLibX and store its pointer in f->img.
Also retrieve the image's raw pixel buffer address, bits per pixel,
line length (stride), and endian setting, storing them in the t_frac struct.
Returns 0 on success or an error code if image creation or buffer retrieval fails.
*/
int	init_img(t_frac *f)
{
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		return (msg("Image creation error.", 1));
	f->buf = mlx_get_data_addr(f->img, &f->bpp, &f->line, &f->endian);
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

int	iter_mandel(double cr, double ci, t_cpx *z, int max_iter)
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

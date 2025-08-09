/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:28:22 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:28:32 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	init_img(t_frac *f)
{
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		return (msg("Image creation error.", "", 1));
	f->buf = mlx_get_data_addr(f->img, &f->bpp, &f->line, &f->endian);
	if (!f->buf)
		return (msg("Buffer address error.", "", 1));
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

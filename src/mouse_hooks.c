/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:29:05 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 09:31:12 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	zoom_at(t_frac *f, int x, int y, double z)
{
	double	mx;
	double	my;
	double	new_w;
	double	new_h;

	mx = f->min_r + (f->max_r - f->min_r) * ((double)x / (WIDTH - 1));
	my = f->max_i + (f->min_i - f->max_i) * ((double)y / (HEIGHT - 1));
	new_w = (f->max_r - f->min_r) * z;
	new_h = (f->min_i - f->max_i) * z;
	f->min_r = mx - (mx - f->min_r) * z;
	f->max_r = f->min_r + new_w;
	f->max_i = my - (my - f->max_i) * z;
	f->min_i = f->max_i + new_h;
	update_iters(f);
}

int	on_mouse(int button, int x, int y, t_frac *f)
{
	if (button == MOUSE_UP)
	{
		zoom_at(f, x, y, 0.9);
		present(f);
	}
	if (button == MOUSE_DOWN)
	{
		zoom_at(f, x, y, 1.0 / 0.9);
		present(f);
	}
	return (0);
}

int	close_btn(t_frac *f)
{
	clean_and_exit(0, f);
	return (0);
}

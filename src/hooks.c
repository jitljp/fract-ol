/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:35 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:36:36 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	present(t_frac *f)
{
	render(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

static void	pan(t_frac *f, int dx, int dy)
{
	double	dr;
	double	di;

	dr = (f->max_r - f->min_r) * 0.1;
	di = (f->min_i - f->max_i) * 0.1;
	f->min_r += dx * dr;
	f->max_r += dx * dr;
	f->min_i += dy * di;
	f->max_i += dy * di;
}

int	on_key(int key, t_frac *f)
{
	if (key == KEY_ESC)
		clean_and_exit(0, f);
	if (key == KEY_C)
	{
		color_shift(f);
		present(f);
	}
	if (key == KEY_P)
	{
		next_palette(f);
		present(f);
	}
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
	{
		if (key == KEY_LEFT)
			pan(f, -1, 0);
		if (key == KEY_RIGHT)
			pan(f, 1, 0);
		if (key == KEY_UP)
			pan(f, 0, -1);
		if (key == KEY_DOWN)
			pan(f, 0, 1);
		present(f);
	}
	return (0);
}

static void	zoom_at(t_frac *f, int x, int y, double z)
{
	double	mx;
	double	my;
	double	w;
	double	h;

	mx = f->min_r + (f->max_r - f->min_r) * ((double)x / (WIDTH - 1));
	my = f->max_i + (f->min_i - f->max_i) * ((double)y / (HEIGHT - 1));
	w = (f->max_r - f->min_r) * z;
	h = (f->min_i - f->max_i) * z;
	f->min_r = mx - w * ( (mx - f->min_r) / (f->max_r - f->min_r) );
	f->max_r = f->min_r + w;
	f->max_i = my - h * ( (my - f->max_i) / (f->min_i - f->max_i) );
	f->min_i = f->max_i + h;
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

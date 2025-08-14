/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:35 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 09:31:46 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	present(t_frac *f)
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

static void	handle_arrow_keys(int key, t_frac *f)
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

static void	handle_iteration_keys(int key, t_frac *f)
{
	if (key == KEY_PLUS)
	{
		f->iter_bias += 25;
		update_iters(f);
		present(f);
	}
	if (key == KEY_MINUS)
	{
		f->iter_bias -= 25;
		update_iters(f);
		present(f);
	}
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
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		handle_arrow_keys(key, f);
	if (key == KEY_PLUS || key == KEY_MINUS)
		handle_iteration_keys(key, f);
	return (0);
}

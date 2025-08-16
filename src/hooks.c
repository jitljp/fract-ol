/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:36:35 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/16 13:43:01 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Redraw and display the fractal.
Calls render() to fill the image buffer, then blits it
to the window at (0,0) using MiniLibX.
*/
void	push_image(t_frac *f)
{
	render(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

/*
Pan the viewport on the complex plane.
dx,dy = direction multipliers (-1,0,1).
Shifts the min/max boundaries by 10% of the
current width/height to move the view smoothly.
*/
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

/*
Handle arrow key presses.
LEFT/RIGHT move viewport horizontally,
UP/DOWN move vertically.
Calls pan() with proper direction and
then redraws via push_image().
*/
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
	push_image(f);
}

/*
Handle iteration count adjustment.
PLUS increases iter_bias (+25),
MINUS decreases it (-25).
Recalculates max_iter with update_iters()
and redraws to reflect new detail level.
*/
static void	handle_iteration_keys(int key, t_frac *f)
{
	if (key == KEY_PLUS)
	{
		f->iter_bias += 25;
		update_iters(f);
		push_image(f);
	}
	if (key == KEY_MINUS)
	{
		f->iter_bias -= 25;
		update_iters(f);
		push_image(f);
	}
}

/*
Keyboard event handler.
Triggered by MiniLibX when a key is pressed, with the keycode
and the fractal state passed as arguments.
- ESC: exit cleanly and free resources
- C: shift the color palette and redraw
- Arrow keys: pan the viewport by 10% in the given direction
- +/-: adjust iteration count (detail level) and redraw
Always returns 0 to satisfy the MiniLibX hook signature.
*/
int	on_key(int key, t_frac *f)
{
	if (key == KEY_ESC)
		clean_and_exit(0, f);
	if (key == KEY_C)
	{
		color_shift(f);
		push_image(f);
	}
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
		handle_arrow_keys(key, f);
	if (key == KEY_PLUS || key == KEY_MINUS)
		handle_iteration_keys(key, f);
	return (0);
}

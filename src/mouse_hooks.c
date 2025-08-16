/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:29:05 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/16 14:08:06 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Zoom the fractal view in or out, centered on the mouse position.
- (x, y): pixel coordinates of the mouse cursor in the window.
- zoom: scale factor (<1 zooms in, >1 zooms out).
The function maps (x, y) into complex-plane coordinates (mouse_x, mouse_y),
then rescales the current rectangle [min_r..max_r, min_i..max_i] around that
point so the cursor stays fixed during zoom. Finally, it calls update_iters()
to adjust iteration count based on the new zoom level.
*/
static void	zoom_at(t_frac *f, int x, int y, double zoom)
{
	double	mouse_x;
	double	mouse_y;
	double	new_w;
	double	new_h;

	mouse_x = f->min_r + (f->max_r - f->min_r) * ((double)x / (WIDTH - 1));
	mouse_y = f->max_i + (f->min_i - f->max_i) * ((double)y / (HEIGHT - 1));
	new_w = (f->max_r - f->min_r) * zoom;
	new_h = (f->min_i - f->max_i) * zoom;
	f->min_r = mouse_x - (mouse_x - f->min_r) * zoom;
	f->max_r = f->min_r + new_w;
	f->max_i = mouse_y - (mouse_y - f->max_i) * zoom;
	f->min_i = f->max_i + new_h;
	update_iters(f);
}

/*
Mouse event handler for zooming.
Triggered by MiniLibX when a mouse button/wheel event occurs
inside the fractal window. Receives:
- button: which mouse button was pressed (4=scroll up, 5=scroll down),
- x, y: cursor coordinates in the window at event time,
- f: fractal state/context.
If scroll up: zooms in (scale 0.9) centered on cursor position.
If scroll down: zooms out (scale 1/0.9) centered on cursor.
After adjusting the viewport, calls push_image() to redraw.
Always returns 0 to match MLX’s expected hook signature.
*/
int	on_mouse(int button, int x, int y, t_frac *f)
{
	if (button == MOUSE_UP)
	{
		zoom_at(f, x, y, 0.9);
		push_image(f);
	}
	if (button == MOUSE_DOWN)
	{
		zoom_at(f, x, y, 1.0 / 0.9);
		push_image(f);
	}
	return (0);
}

/*
Called when the window close button (x) is pressed.
Cleans and exits the program.
Must return due to how MiniLibX defines its hook functions:
	int func(void *param);
*/
int	close_btn(t_frac *f)
{
	clean_and_exit(0, f);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:56:59 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 12:42:47 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Initialize t_frac to a clean, known state.
Nulls MLX/window/image pointers and buffer; zeroes numeric fields; sets
safe defaults (e.g., max_iter) and a sentinel (set = -1) before parsing.
Enables safe early exits via clean_and_exit(...) and avoids using
uninitialized fields later in the program.
*/
void	clean_init(t_frac *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->buf = NULL;
	f->bpp = 0;
	f->line = 0;
	f->endian = 0;
	f->set = -1;
	f->min_r = 0;
	f->max_r = 0;
	f->min_i = 0;
	f->max_i = 0;
	f->cr = 0;
	f->ci = 0;
	f->shift = 0;
	f->max_iter = 100;
	f->iter_bias = 0;
}

/*
Adjust iteration budget based on zoom.
- base_w = canonical width
- zoom = base_w / current_width; 1 at start, >1 when zoomed
- mi (max iterations) = 100 + 15*log2(zoom+1) + user bias
	then clamped (min 50, max 5000)
Log2 makes iterations grow gently: each 2x zoom = +15 iterations
*/
void	update_iters(t_frac *f)
{
	double	base_w;
	double	zoom;
	int		mi;

	base_w = 4.0;
	zoom = base_w / (f->max_r - f->min_r);
	mi = 100 + (int)(15.0 * log2(zoom + 1.0));
	mi += f->iter_bias;
	if (mi < 50)
		mi = 50;
	if (mi > 5000)
		mi = 5000;
	f->max_iter = mi;
}

/*
Choose a sensible starting viewpoint on the complex plane,
and set (min_r, max_r, min_i, max_i),
preserving the window aspet ratio (HEIGHT/WIDTH)
*/
void	init_complex_plane(t_frac *f)
{
	double	center_r;
	double	center_i;
	double	width;
	double	height;

	center_r = 0.0;
	center_i = 0.0;
	width = 4.0;
	height = width * HEIGHT / WIDTH;
	f->min_r = center_r - width / 2.0;
	f->max_r = center_r + width / 2.0;
	f->max_i = center_i + height / 2.0;
	f->min_i = center_i - height / 2.0;
}

/*
Bootstrap the graphics context and initial fractal state.
1) mlx_init()
	Connect to MLX (graphics backend)
2) mlx_new_window()
	Create the main window with given WIDTH and HEIGHT
3) init_complex_plane()
	Initialize the complex-plane bounds to match the chosen set
	and preserve aspect ratio.
4) update_iters()
	Initialize the iteration budget based on current view/zoom.
On any failure prints an error and exits via clean_and_exit().
*/
void	init(t_frac *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		clean_and_exit(msg("MLX connection error.", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!f->win)
		clean_and_exit(msg("MLX window creation error.", 1), f);
	init_complex_plane(f);
	update_iters(f);
}

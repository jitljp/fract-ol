/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:48:52 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 10:19:25 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

/* window */
# define WIDTH 800
# define HEIGHT 600

/* iteration */
# define MAX_ITERS 200

/* sets */
# define MANDELBROT 1
# define JULIA 2

/* keys (X11) */
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_C 99
# define KEY_PLUS 61
# define KEY_MINUS 45

/* mouse (X11) */
# define MOUSE_UP 4
# define MOUSE_DOWN 5

typedef struct s_frac
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		bpp;
	int		line;
	int		endian;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	cr;
	double	ci;
	int		shift;
	int		max_iter;
	int		iter_bias;
}	t_frac;

typedef struct s_cpx
{
	double	r;
	double	i;
}	t_cpx;

/* init.c */
void	clean_init(t_frac *f);
void	update_iters(t_frac *f);
void	init_complex_plane(t_frac *f);
void	init(t_frac *f);

/* image.c */
int		init_img(t_frac *f);
void	reinit_img(t_frac *f);
int		iter_mandel(double cr, double ci, t_cpx *z, int max_iter);
int		iter_julia(t_frac *f, double zr, double zi, t_cpx *z);

/* render.c */
void	render(t_frac *f);

/* hooks.c */
void	present(t_frac *f);
int		on_key(int key, t_frac *f);

/* mouse_hooks.c */
int		on_mouse(int button, int x, int y, t_frac *f);
int		close_btn(t_frac *f);

/* color.c */
int		get_color(t_frac *f, int n, double zr, double zi);
int		mix_colors(int a, int b, double t);
void	color_shift(t_frac *f);

/* parse.c */
double	str_to_double(char *str);

/* utils.c */
void	clean_and_exit(int code, t_frac *f);
int	msg(char *str, int code);
void	help_msg(t_frac *f);

#endif

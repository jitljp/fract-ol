/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:41:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:38:59 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	julia_init_values(t_frac *f, char **argv)
{
	if (!ft_strchr(argv[2], '.'))
		help_msg(f);
	if (!ft_strchr(argv[3], '.'))
		help_msg(f);
	f->cr = str_to_double(argv[2]);
	f->ci = str_to_double(argv[3]);
	if (f->cr > 2.0 || f->cr < -2.0 || f->ci > 2.0 || f->ci < -2.0)
		help_msg(f);
}

static int	verify_arg(char *argv, char *str, char c)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = ft_tolower(argv[i]);
		i++;
	}
	if (ft_strncmp(argv, str, ft_strlen(str) + 1) == 0)
		return (1);
	else if (argv[1] == '\0' && argv[0] == c)
		return (1);
	return (0);
}

static void	get_set(t_frac *f, char **argv)
{
	if (verify_arg(argv[1], "mandelbrot", 'm'))
		f->set = MANDELBROT;
	else if (verify_arg(argv[1], "julia", 'j'))
		f->set = JULIA;
	else
		help_msg(f);
}

static void	read_args(t_frac *f, int argc, char **argv)
{
	get_set(f, argv);
	if (f->set == JULIA)
	{
		if (argc != 2 && argc != 4)
			help_msg(f);
		if (argc == 4)
			julia_init_values(f, argv);
		else
		{
			f->cr = 0.355;
			f->ci = -0.3842;
		}
	}
	else if (argc != 2)
		help_msg(f);
}

int	main(int argc, char **argv)
{
	t_frac	f;

	if (argc < 2)
		help_msg(&f);
	clean_init(&f);
	read_args(&f, argc, argv);
	init(&f);
	if (init_img(&f))
		clean_and_exit(1, &f);
	render(&f);
	mlx_put_image_to_window(f.mlx, f.win, f.img, 0, 0);
	mlx_hook(f.win, 2, 1L << 0, on_key, &f);
	mlx_mouse_hook(f.win, on_mouse, &f);
	mlx_hook(f.win, 17, 0, close_btn, &f);
	mlx_loop(f.mlx);
	return (0);
}

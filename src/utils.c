/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:52:52 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:36:58 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	clean_and_exit(int code, t_frac *f)
{
	if (!f)
		exit(code);
	if (f->img && f->mlx)
	{
		mlx_destroy_image(f->mlx, f->img);
		f->img = NULL;
	}
	if (f->win && f->mlx)
	{
		mlx_destroy_window(f->mlx, f->win);
		f->win = NULL;
	}
	if (f->mlx)
	{
		mlx_loop_end(f->mlx);
		mlx_destroy_display(f->mlx);
		free(f->mlx);
		f->mlx = NULL;
	}
	exit(code);
}

int	msg(char *s1, char *s2, int code)
{
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	return (code);
}

void	help_msg(t_frac *f)
{
	ft_putstr_fd("\nUsage: ./fractol <set> [params]\n", 2);
	ft_putstr_fd("  mandelbrot | m\n", 2);
	ft_putstr_fd("  julia      | j   <cr> <ci>\n", 2);
	ft_putstr_fd("\nExamples:\n", 2);
	ft_putstr_fd("  ./fractol mandelbrot\n", 2);
	ft_putstr_fd("  ./fractol julia 0.355 -0.3842\n\n", 2);
	clean_and_exit(1, f);
}

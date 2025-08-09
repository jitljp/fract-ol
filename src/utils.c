/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:52:52 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:19:06 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Closes the program cleanly by freeing allocated memory,
destroying all MiniLibX resources, and ending the MLX loop.
Resources are released in reverse creation order:
free heap memory (palette), destroy image, destroy window,
end the event loop, destroy the display, and free the MLX
connection before exiting with the given status code.
 */

void	clean_and_exit(int exit_code, t_frac *f)
{
	if (!f)
		exit(exit_code);
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
	exit(exit_code);
}

/*
Prints an error message to standard error in the format:
"Fractol: " + str1 + str2
Returns the given exit_code without exiting.
*/
int	msg(char *str1, char *str2, int exit_code)
{
	ft_putstr_fd("Fractol: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	return (exit_code);
}

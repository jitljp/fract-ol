/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:41:06 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 13:30:10 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
If non-default c-values are given, verifies them
and converts them from ASCII to doubles.
Accepted values: >-2.0 and <2.0
*/
static void	julia_init_values(t_frac *f, int argc, char **argv)
{
	if (!ft_strchr(argv[2], '.'))
		help_msg(f);
	if (!ft_strchr(argv[3], '.'))
		help_msg(f);
	f->cr = str_to_double(argv[2]);
	f->ci = str_to_double(argv[3]);
	if (f->cr > 2.0 || f->cr < -2.0
		|| f->ci > 2.0 || f->ci < -2.0)
		help_msg(f);
}

/*
Checks whether the given argument selects a target set.
1) Converts each argument to lowercase (modifies it in memory)
2) Checks for a full name match between first arg and str
	*ft_strncmp returns 0 for a match.
3) Checks for a single-char match between argv and c or n
Returns 1 on match, 0 otherwise.
*/
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

/*
Determines which fractal set to render from argv[1].
Accepts "mandelbrot"/'m'/'1', "julia"/'j'/'2', "mandelbox"/'x'/'3'.
On invalid input, prints the help message and exits cleanly.
*/
static void	get_set(t_frac *f, char **argv)
{
	if (verify_arg(argv[1], "mandelbrot", 'm'))
		f->set = MANDELBROT;
	else if (verify_arg(argv[1], "julia", 'j'))
		f->set = JULIA;
	else
		help_msg(f);
}

/*
Reads and validates the program arguments:
1) Determines the fractal set to render from the first argument.
2) Checks that the number of arguments matches the selected set.
	- Non-Julia sets require exactly 1 parameter (the set name).
	- Julia sets require either 1 parameter (default values) or
		3 parameters (set name + 2 values for c's real and imaginary parts).
3) Initializes Julia values if needed, otherwise sets default constants.
*/

static void	read_args(t_frac *f, int argc, char **argv)
{
	get_set(f, argv);
	if (f->set == JULIA)
	{
		if (argc != 2 && argc != 4)
			help_msg(f);
		if (argc == 4)
			julia_init_values(f, argc, argv);
		else
		{
			f->cr = 0.355;
			f->ci = -0.3842;
		}
	}
	else
	{
		if (argc != 2)
			help_msg(f);
	}
}

int	main(int argc, char **argv)
{
	t_frac	f;

	if (argc < 2)
		help_msg(&f);
	clean_init(&f);
	read_args(&f, argc, argv);
	init(&f);
	render(&f);
}

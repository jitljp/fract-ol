/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:31:33 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/14 12:08:57 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Skips optional leading sign, sets sign if needed.
Increments index if sign is found.
*/
static void	sign_check(char *str, int *sign, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

/*
Converts a numeric string to a double.
Accepts an optional leading sign, then digits, then a decimal,
	then fractional digits.
NO whitespace or trailing characters allowed.
Returns -42 on invalid format (outside of valid >-2.0 and <2.0 range).
*/
double	str_to_double(char *str)
{
	int		i;
	double	nb;
	int		sign;
	double	div;

	i = 0;
	nb = 0;
	sign = 1;
	div = 0.1;
	sign_check(str, &sign, &i);
	while (ft_isdigit(str[i]))
		nb = (nb * 10.0) + (str[i++] - '0');
	if (str[i] != '.')
		return (-42);
	i++;
	while (ft_isdigit(str[i]))
	{
		nb += (str[i++] - '0') * div;
		div *= 0.1;
	}
	if (str[i] != '\0')
		return (-42);
	return (nb * sign);
}

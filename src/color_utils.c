/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:20 by mjeremy           #+#    #+#             */
/*   Updated: 2025/08/09 14:20:58 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* mix_colors:
*	Linear blend between two RGB colors. t in [0,1].
*/
int	mix_colors(int a, int b, double t)
{
	int		res;
	int		av;
	int		bv;
	int		t8;

	res = 0;
	t8 = (int)(t * 256.0);
	av = (a >> 16) & 255;
	bv = (b >> 16) & 255;
	res |= ((av + (((bv - av) * t8) >> 8)) << 16);
	av = (a >> 8) & 255;
	bv = (b >> 8) & 255;
	res |= ((av + (((bv - av) * t8) >> 8)) << 8);
	av = a & 255;
	bv = b & 255;
	res |= (av + (((bv - av) * t8) >> 8));
	return (res);
}

/* color_shift:
*	Rotate the palette (bonus: color range shift).
*/
void	color_shift(t_frac *f)
{
	f->shift = (f->shift + 10) % 360;
}

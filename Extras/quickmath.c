/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickmath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:53:39 by mresch            #+#    #+#             */
/*   Updated: 2024/06/28 18:26:33 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extras.h"
#include "../cube.h"

//best call like this:
//map( (t_m) {VAL, a, b, A, B} );
double   map(t_m in)
{
	double	ret;
	double	steps;

	steps = (in.new_max - in.new_min) / (in.prev_max - in.prev_min);
	ret = in.val - in.prev_min;
	ret = ret * steps + in.new_min;
	return (ret);
}

double	degr(double rad)
{
	return (map((t_m){rad, 0, 2 * PI, 0, 360}));
}
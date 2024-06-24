/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:05:08 by mresch            #+#    #+#             */
/*   Updated: 2024/06/24 15:28:17 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUICKMATH_H
# define QUICKMATH_H
# include "../cube.h"

typedef struct s_m
{
	double	val;
	double	prev_min;
	double	prev_max;
	double	new_min;
	double	new_max;
}   t_m;

double	map(t_m in);

#endif

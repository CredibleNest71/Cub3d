/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:05:08 by mresch            #+#    #+#             */
/*   Updated: 2024/06/28 18:27:00 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUICKMATH_H
# define QUICKMATH_H

typedef struct s_m
{
	double	val;
	double	prev_min;
	double	prev_max;
	double	new_min;
	double	new_max;
}   t_m;

double	map(t_m in);
double	degr(double rad);
int	is_char(char c, char *chars);

#endif

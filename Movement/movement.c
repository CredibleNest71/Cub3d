/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:19:55 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 13:39:38 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_forward(t_player *p)
{
	p->px += cos(p->rad) * SPEED;
	p->py += sin(p->rad) * SPEED;
}

void	turn_left(t_player *p)
{
	p->rad -= SPIN;
}

void	turn_right(t_player *p)
{
	p->rad += SPIN;
}
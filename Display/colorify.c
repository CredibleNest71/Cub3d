/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:33:02 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 15:58:04 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	colorize(char *buffer, int color, int endian)
{
	if (!buffer)
		return ;
	if (endian == 1)
	{
		buffer[0] = (color >> 24);
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else if (endian == 0)
	{
		buffer[0] = (color) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[3] = (color >> 24);
	}
	return ;
}

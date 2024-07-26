/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:29:13 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:21 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free_and_null((void **)&words[i]);
		i++;
	}
	free_and_null((void **)&words);
}
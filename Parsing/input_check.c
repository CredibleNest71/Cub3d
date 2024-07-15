/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:31 by mesenyur          #+#    #+#             */
/*   Updated: 2024/07/15 13:06:58 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool    name_check(char **av)
{
    char    *ext;

    ext = ft_strchr(av[1], '.');
    if (!ext || ft_strlen(ext) != 4 || ft_strncmp(ext + 1, "cub", 4) != 0)
        ft_error(NULL, "Wrong Extension(.cub)");
    if (*(ext - 1) == '/' || ext == av[1])
        ft_error(NULL, "Forgot the name of the map?");
    return (0);
    
}
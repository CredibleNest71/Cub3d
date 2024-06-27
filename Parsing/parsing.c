/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/06/26 15:21:21 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cube.h"

int	fin_read(t_tex *tex)
{
	if (!tex->C)
		return (0);
	if (!tex->F)
		return (0);
	if (!tex->NO)
		return (0);
	if (!tex->WE)
		return (0);
	if (!tex->EA)
		return (0);
	if (!tex->SO)
		return (0);
	return (1);
}

static	char **identify(t_tex *tex, char *line, int *color)
{
	*color = 0;
	if (!ft_strncmp(line, "NO", 2) && !tex->NO)
		return (&tex->NO);
	if (!ft_strncmp(line, "SO", 2) && !tex->SO)
		return (&tex->SO);
	if (!ft_strncmp(line, "EA", 2) && !tex->EA)
		return (&tex->EA);
	if (!ft_strncmp(line, "WE", 2) && !tex->WE)
		return (&tex->WE);
	if (!ft_strncmp(line, "F", 1) && !tex->F)
	{
		*color = 1;
		return (&tex->F);
	}
	if (!ft_strncmp(line, "C", 1) && !tex->C)
	{
		*color = 1;
		return (&tex->C);
	}
	write(2, "Error: couldnt identify!", 24);
	return (NULL);
}

static	int	add_to_textures(t_tex *tex, char *line)
{
	char	**curr;
	char	*found;
	char	*path;
	int		color;
	
	curr = identify(tex, line, &color);
	if (!curr)
		return (free(line), 0);
	if (!color)
		found = ft_strchr(line, '.');
	else
		found = line;
	if (!found)
		return (free(line), 0);
	path = ft_strdup(found);
	if (!path)
		return (free(line), 0);
	*curr = path;
	return (1);
}
// 0 = ALL GOOD
// ANYTHING ELSE = ERROR
int    get_textures(int fd, t_tex *tex)
{
    char    *line;

    while (!fin_read(tex))
    {
        line = get_next_line(fd);
        if (!line)
            return (1);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
        if (!add_to_textures(tex, line))
			return (write(2, "An Error occurred\n", 18));
    }
	return 0;
}

void	print_tex(t_tex *tex)
{
	printf("NO:	%s", tex->NO);
	printf("SO:	%s", tex->SO);
	printf("WE:	%s", tex->WE);
	printf("EA:	%s", tex->EA);
	printf("F:	%s", tex->F);
	printf("C:	%s", tex->C);
}
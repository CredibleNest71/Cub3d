/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:56 by mresch            #+#    #+#             */
/*   Updated: 2024/07/17 16:57:27 by mresch           ###   ########.fr       */
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
	
	if (!line)
		return (0);
	curr = identify(tex, line, &color);
	if (!curr)
		return (free_and_null((void **)&line), 0);
	if (!color)
		found = ft_strchr(line, '.');
	else
		found = line;
	if (!found)
		return (free_and_null((void **)&line), 0);
	path = ft_strdup(found);
	if (path)
		path[ft_strlen(path) - 1] = 0;
	free_and_null((void **)&line);
	*curr = path;
	return (1);
}
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	string_to_rgb(char *str)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (ft_isalpha(str[i]) || str[i] == ' ')
		i++;
	rgb[0] = ft_atoi(&str[i]);
	i = ft_strchr(&str[i], ',') - str + 1;
	rgb[1] = ft_atoi(&str[i]);
	i = ft_strchr(&str[i], ',') - str + 1;
	rgb[2] = ft_atoi(&str[i]);
	printf("r: %d | g: %d | b: %d \n", rgb[0], rgb[1], rgb[2]);
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

void	convert(t_game *g, t_tex *tex)
{
	int	h;
	int	w;

	tex->NO_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->NO /*"./textures/pixelverlauf1.xpm"*/, &h, &w);
	tex->SO_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->SO /*"./textures/pixelverlauf2.xpm"*/, &h, &w);
	tex->EA_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->EA /*"./textures/pixelverlauf3.xpm"*/, &h, &w);
	tex->WE_img = mlx_xpm_file_to_image(g->minilibx.mlx, tex->WE /*"./textures/pixelverlauf4.xpm"*/, &h, &w);
	printf("W%d\n", w);
	printf("H%d\n", h);
	printf("TEX: |%s|\n", tex->SO);
	printf("TEX: %p\n", tex->SO_img);
}
void	print_tex(t_tex *tex)
{
	printf("NO:	|%s|\n", tex->NO);
	printf("SO:	|%s|\n", tex->SO);
	printf("WE:	|%s|\n", tex->WE);
	printf("EA:	|%s|\n", tex->EA);
	printf("F:	|%s|\n", tex->F);
	printf("C:	|%s|\n", tex->C);
}

// 0 = ALL GOOD
// ANYTHING ELSE = ERROR
int    get_textures(int fd, t_tex *tex, t_game *g)
{
    char    *line;

    while (!fin_read(tex))
    {
        line = get_next_line(fd);
        if (!line)
            return (1);
		if (line[0] == '\n')
		{
			free_and_null((void **)&line);
			continue ;
		}
        if (!add_to_textures(tex, line))
			return (write(2, "An Error occurred\n", 18));
    }
	print_tex(tex);
	g->tex.C_rgb = string_to_rgb(tex->C);
	g->tex.F_rgb = string_to_rgb(tex->F);
	convert(g, tex);
	return 0;
}

void	delete_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i++]);
	}
	free(map);
}

void	delete_tex(t_tex *tex)
{
	if (tex->C)
		free(tex->C);
	if (tex->F)
		free(tex->F);
	if (tex->NO)
		free(tex->NO);
	if (tex->SO)
		free(tex->SO);
	if (tex->EA)
		free(tex->EA);
	if (tex->WE)
		free(tex->WE);
}

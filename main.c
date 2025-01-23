#include "cub3d.h"

int return_error(char *error_str)
{
    printf("Error: %s\n", error_str);
    exit(0);
}

int return_free_error(char *error_str, t_cub3d *game)
{
	char **temp;
	int i;

	i = 0;
	temp = game->cub;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
    printf("Error: %s\n", error_str);
    exit(0);
}

int check_textures(t_cub3d game)
{
    
    ;
    return (1);
}

int check_map(char *map)
{
    ;
    return (1);
}

int count_heigh(char *file)
{
    int count;
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (count);
}

char **read_file(char *file)
{
    char    **cub;
    char    *line;
    int     fd;
    int     i;
    int height;

    i = 0;
    height = count_heigh(file);
    fd = open(file, O_RDONLY);
    cub = (char **)malloc((height + 1) * sizeof(char *));
    if (cub == NULL)
        return (NULL);
    line = get_next_line(fd);
    while (line)
    {
        cub[i] = ft_strdup(line);
        i++;
        free(line);
        line = get_next_line(fd);
    }
    cub[i] = NULL;
    if (line != NULL)
		free(line);
	close(fd);
	return (cub);
}

void    init_data(t_cub3d *game)
{
	int i;
	i = 0;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	while (i < 3)
	{
		game->f_color[i] = -1;
		game->c_color[i] = -1;
		i++;
	}
	game->cub_map = NULL;
	game->map_heigh = 0;
	game->map_width = 0;
}
// no---->1
// so---->2
// we---->3
// ea---->4
// f ---->5
// c ---->6
// map--->7

int	is_not_map(char *line)
{
	if (line[0] == '1')
		return (1);
	return (0);
}

int	is_a_texture(char *line)
{
	if (!line)
		return (0);
	if(!ft_strncmp(line, "NO ", 3))
		return(1);
	else if(!ft_strncmp(line, "SO ", 3))
		return(2);
	else if(!ft_strncmp(line, "WE ", 3))
		return(3);
	else if(!ft_strncmp(line, "EA ", 3))
		return(4);
	else if(!ft_strncmp(line, "F ", 2))
		return(5);
	else if(!ft_strncmp(line, "C ", 2))
		return(6);
	else if (is_not_map(line) == 1)
		return (7);
	else
		return (0);
}

int	is_empty(char *line)
{
	if(line[0] == '\n' && line[1] == '\0')
		return (0);
	return (1);
}

int	check_fc_empty(char *colorf, char *colorc)
{
	if (colorf != NULL)
		return (1);
	if (colorf != NULL)
		return (2);
	return (0);
	
}

int parce_f_color(char *colorf, t_cub3d *game)
{
	int		i;
	int		j;
	int		count;
	char	*my_color;
	int		my_int;
	
	i = 0;
	j = 0;
	count = 0;
	while(i < 3)
	{
		if (game->f_color[i] != -1)
			return (0);
		i++;
	}
	i = 0;
	/// read colors;
	while (colorf[count] != '\0' && i < 3)
	{
		j = 0;
		while (colorf[i] && colorf[count] != ',')
		{
			my_color[j] == colorf[count];
			count++;
			j++;
		}
		my_color[j] = '\0';
		my_int = ft_my_atoi(my_color);
		if (my_int == -1)
			return (free(colorf), 0);
		game->f_color[i] = my_int;
		i++;
	}
	if (colorf[count] == '\0' || i == 3)
		return (1);
}

int parce_c_color(char *colorc, t_cub3d *game)
{
	int		i;
	int		j;
	int		count;
	char	*my_color;
	int		my_int;
	
	i = 0;
	j = 0;
	count = 0;
	while(i < 3)
	{
		if (game->c_color[i] != -1)
			return (0);
		i++;
	}
	i = 0;
	/// read colors;
	while (colorc[count] != '\0' && i < 3)
	{
		j = 0;
		while (colorc[i] && colorc[count] != ',')
		{
			my_color[j] == colorc[count];
			count++;
			j++;
		}
		my_color[j] = '\0';
		my_int = ft_my_atoi(my_color);
		if (my_int == -1)
			return (free(colorc), 0);
		game->c_color[i] = my_int;
		i++;
	}
	if (colorc[count] == '\0' || i == 3)
		return (1);
}

int	parse_fc_colors(char *colorf, char *colorc, t_cub3d *game)
{
	int		checker;

	if (!colorf && !colorc)
		return (1);
	checker = check_fc_empty(colorf, colorc);
	if (checker == 0)
		return (-1);
	if (checker == 1)
	{
		if (parce_f_color(colorf, game) == 0)
			return (0);
	}
	if (checker == 2)
	{
		if (parce_c_color(colorc, game) == 0)
			return (0);
	}
	
	/// don't forget to free colorf-and-c
	free(colorc);
	free(colorf);
	return (1);
}

int	parse_texture(t_cub3d *game, int texture_type, int i)
{
	char	**textures[6];
	char	**my_texture;
	char	*c_color = NULL;
	char	*f_color = NULL;
	int		start;

	start = 3;
	textures[0] = &game->no_texture;
	textures[1] = &game->so_texture;
	textures[2] = &game->we_texture;
	textures[3] = &game->ea_texture;
	textures[4] = &f_color;
	textures[5] = &c_color;
	if (texture_type > 0 && texture_type < 7)
	{
		if (texture_type > 4)
			start = 2;
		my_texture = textures[texture_type - 1];
		if (*my_texture != NULL)
			return (0);
		else
			*my_texture = ft_substr(game->cub[i], start, ft_strlen(game->cub[i]) - 3);
		printf("---%s\n", *my_texture);
	}
	if (parse_fc_colors(f_color, c_color, game) == 0)
		return (0);
	return (1);
}

int	split_my_elements(t_cub3d *game)
{
	char **read_cub;
	int my_texture;
	int i;

	read_cub = game->cub;
	my_texture = 0;
	i = 0;
	if (!read_cub[i][0])
		return (0);
	while(read_cub[i])
	{
		while(read_cub[i] && !is_empty(read_cub[i]))
			i++;
		my_texture = is_a_texture(read_cub[i]);
		if (!my_texture)
			return_free_error("invalid map", game);
		else if(my_texture > 0 && my_texture < 7)
		{
			if (parse_texture(game, my_texture, i) == 0)
				return_free_error("Invalid textures!", game);
		}
		else
			break;
		i++;
		// exit(65);
	}
	// return(fill_cub_map());
	return (1);
}

int main(int ac, char *av[])
{
    t_cub3d game;

    if (ac != 2)
        return_error("Arguments not valid!");
    if (check_file_valid(av[1]) == 0)
        return_error("Cannot open file!");
    game.cub = read_file(av[1]);
	if (!game.cub)
		return_error("Invalid map!");
	init_data(&game);
	if (!split_my_elements(&game))/// this function split the textures from the map and put each on the appropriate place
		return_free_error("Invalid map!", &game);
	// printf("---- c is: %s\n", game.so_texture);
	return_free_error("EVERY THING IS GoooooD\n", &game);
	return (54);
    // if (check_textures(game) == 0)
    //     return_error("wrong textures!");
    // if (check_map(av[1]) == 0)
    //     return_error("map not valid!");

}

/////// IT IS A MUST TO ASSIGN ALL THE CUB3D ELEMENT TO NULLLLLLLLLL
////// THEN START READING THE MAPPPP 
/////  TRUST ME DO THAT FIRST..

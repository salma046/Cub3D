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
	if (line[0] == '1' || line[0] == '\0')
		return (1);
	return (0);
}

int	is_a_texture(char *line)
{
	while(!is_not_map(line))
	{
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
		else
			return (0);
	}
	return (7);
}

int	is_empty(char *line)
{
	if(line[0] == '\n' && line[1] == '\0')
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
	while(read_cub[i])
	{
		printf("hello world\n");
		while(!is_empty(read_cub[i]))
			i++;
		my_texture = is_a_texture(read_cub[i]);
		if (!my_texture)
			return_free_error("invalid map", game);
		i++;
		// else if(my_texture == 7)
		// 	return(fill_cub_map());
		// else
		// 	assign_cub_texture();
	}
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
		return_error("invalid map!");
	init_data(&game);
	if (!split_my_elements(&game))
		return_free_error("invalid map!", &game);
	printf("---- c is: %s\n", game.so_texture);
	printf("all good\n");
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

int	parse_fc_colors(char *colorf, char *colorc, t_cub3d *game)
{
	char	*read_color;
	char	*my_color;
	int		*my_int;
	int		checker;
	int		i;

	i = 0;
	if (!colorf && !colorc)
		return (1);
	checker = check_fc_empty(colorf, colorc);
	// if (checker == 1)
	// {
	// 	my_color = colorf;
	// 	my_int = game->f_color;
	// }
	// else if (checker == 2)
	// {
	// 	my_color = colorc;
	// 	my_int = game->c_color;
	// }
	// else
	// 	return (-1);
	while(i < 3)
	{
		printf("uuuuuuu\n");
		if (game->f_color[i] == -1)
			printf("helllo woroooold\n");
		i++;
	}
	/// don't forget to free colorf-and-c
	free(colorc);
	free(colorf);
	return (1);
}

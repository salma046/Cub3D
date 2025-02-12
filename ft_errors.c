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
	i = 0;
	while (game->cub_map && game->cub_map[i])
	{
		free(game->cub_map[i++]);
	}
	free(game->cub_map);
	i = 0;
	while (game->cub_copymap && game->cub_copymap[i])
	{
		free(game->cub_copymap[i++]);
	}
	free(game->cub_copymap);
	if (error_str[0] != '\0')
		printf("Error: %s\n", error_str);
	exit(0);
}

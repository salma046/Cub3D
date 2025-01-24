#include "../cub3d.h"

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

void    cub_extention(char *file)
{
    int i;
    i = ft_strlen(file);
    if (file[i - 4] != '.' || file[i - 3] != 'c')
		return_error("invalid file extention!");
	if (file[i - 2] != 'u' || file[i - 1] != 'b')
		return_error("invalid file extention!");
}

int check_file_valid(char *file)
{
    int fd;
    cub_extention(file);
	fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

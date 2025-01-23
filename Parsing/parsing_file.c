#include "../cub3d.h"

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

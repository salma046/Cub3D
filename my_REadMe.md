/// I still have a segfaul when putting spaces in front of a texture
///TO REMEMBER


the map should not have empty lines without spaces on it
the map can have spaces on it's lines
if 0 is found check up and down it u should find no spaces only 1ones or 0's not '\0'

<!-- 
j = 0;
		while(j == 0 || read_cubmap[i][j] == '\n')
		{
			while (read_cubmap[i][j + 1] && ft_isspace(read_cubmap[i][j], 0))
				j++;
			if (read_cubmap[i][j] && read_cubmap[i][j] != '1' && read_cubmap[i][j] != '\n')
				return (0);
			if (read_cubmap[i][j] == '\n')
				j = 0;
		} -->

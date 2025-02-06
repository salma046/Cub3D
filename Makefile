SRC = main.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		Parsing/parsing_file.c libft/ft_strncmp.c \
		libft/ft_substr.c  libft/ft_atoi.c \
		Parsing/parsing_textures.c Parsing/parsing_map.c \
		Parsing/parsing_colors.c libft/ft_isspace.c \
		libft/ft_strjoin.c libft/ft_memset.c ft_errors.c \
		Parsing/init_data2.c Parsing/init_data.c
NAME = Cub3D
cc = cc
FLAGS= -Wall -Wextra -Werror
MINILIBX= -L/usr/local/lib -lmlx -lX11 -lXext -lm
SRC_o := $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(SRC_o)
	$(cc) $(FLAGS) -o $(NAME) $(SRC_o) $(MINILIBX)
%.o: %.c
	$(cc) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(SRC_o)

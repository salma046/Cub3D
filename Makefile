SRC = mandatory/main.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		Parsing/parsing_file.c libft/ft_strncmp.c \
		libft/ft_substr.c  libft/ft_atoi.c \
		Parsing/parsing_textures.c Parsing/parsing_map.c \
		Parsing/parsing_colors.c libft/ft_isspace.c \
		libft/ft_strjoin.c libft/ft_memset.c ft_errors.c \
		Parsing/init_data2.c Parsing/init_data.c \
		mandatory/raycasting/raycasting.c mandatory/raycasting/move_utils.c \

SRCB = bonus/main.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		Parsing/parsing_file.c libft/ft_strncmp.c \
		libft/ft_substr.c  libft/ft_atoi.c \
		Parsing/parsing_textures.c Parsing/parsing_map.c \
		Parsing/parsing_colors.c libft/ft_isspace.c \
		libft/ft_strjoin.c libft/ft_memset.c ft_errors.c \
		Parsing/init_data2.c Parsing/init_data.c \
		bonus/raycasting/raycasting.c bonus/raycasting/move_utils.c \
		bonus/raycasting/drawing.c \
		bonus/gaming/animation.c bonus/gaming/animation_frames.c

NAMEBONUS = Cub3D_bonus
NAME = Cub3D
cc = cc
FLAGS= -Wall -Wextra -Werror
MINILIBX= -L/usr/local/lib -lmlx -lX11 -lXext -lm
SRC_o := $(SRC:.c=.o)
SRCB_o := $(SRCB:.c=.o)

all : $(NAME)
bonus : $(NAMEBONUS)

$(NAME): $(SRC_o)
	$(cc) $(FLAGS) -o $(NAME) $(SRC_o) $(MINILIBX)

$(NAMEBONUS): $(SRCB_o)
	$(cc) $(FLAGS) -o $(NAMEBONUS) $(SRCB_o) $(MINILIBX)

%.o: %.c
	$(cc) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_o)
	rm -f $(SRCB_o)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMEBONUS)

re: fclean all bonus

.SECONDARY: $(SRC_o)
.SECONDARY: $(SRCB_o)

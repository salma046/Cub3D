SRC = main.cpp ClapTrap.cpp
NAME = ClapTrap
cc = c++
FLAGS= -Wall -Wextra -Werror -std=c++98
SRC_o := $(SRC:.cpp=.o)

all : $(NAME)

$(NAME): $(SRC_o)
	$(cc) $(FLAGS) -o $(NAME) $(SRC_o)
%.o: %.cpp
	$(cc) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(SRC_o)

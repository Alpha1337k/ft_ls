NAME=ft_ls

CC=gcc
FLAGS=-Wall -Werror -Wextra -g
DEBUG_FLAGS=-g -fsanitize=address
SRC=src/*.c libft/*.c
LIBS=-I .
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME)

NAME=ft_ls

CC=gcc
FLAGS=-Wall -Werror -Wextra -O3 -Wno-unused-result  -D st_mtim=st_mtimespec
DEBUG_FLAGS=-g -fsanitize=address
SRC=	libft/list.c		\
		libft/longlen.c		\
		libft/memcpy.c		\
		libft/memset.c		\
		libft/putnumbr.c	\
		libft/puts.c		\
		libft/strcmp.c		\
		libft/strdup.c		\
		libft/strjoin.c		\
		libft/strlen.c		\
		libft/substr.c		\
		src/getter.c		\
		src/main.c			\
		src/parser.c		\
		src/printer.c		\
		src/sort.c			
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

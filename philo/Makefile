NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC = main.c \
	init.c \
	utils.c \
	food.c \
	routine.c \
	monitoring.c \
	print.c \
	parsing.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
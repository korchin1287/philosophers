NAME = philo_three
SRCS = main.c init.c exit.c utils.c print_status.c live.c
	
OBJ = $(SRCS:.c=.o)

INCLUDES = ./
FLAGS = -Wall -Wextra -Werror -g
all: $(NAME)

$(NAME):$(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean:clean
	/bin/rm -f $(NAME)

re:fclean all
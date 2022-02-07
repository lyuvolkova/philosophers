NAME = philo

CC = gcc 
FLAGS = -Wall -Wextra -Werror
SRCS = philo.c using.c eat_think.c philo_process.c init.c
HEADER = philo.h

OBJ = $(SRCS:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)
	 
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o  $(NAME) 

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
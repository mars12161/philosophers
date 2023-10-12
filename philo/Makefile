# Constants

HEADERS = philosophers.h

NAME = 	philosophers

SRC = 	philo_error.c \
		philo_init.c \
		philo_routine.c \
		philo_time_utils.c \
		philo_utils.c \
		philo_utils2.c \
		philo_input.c \
		philosophers.c
		


OBJS = $(SRC:.c=.o)

# Compiler

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Colors

RED = \033[0;31m
GREEN = \033[0;32m

# Rules

all : $(NAME)

%.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread
	@echo "$(GREEN)$(NAME) compiled"

clean :
	@rm -f $(OBJS)
	@echo "$(RED)$(NAME) objects deleted"

fclean : clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted"

re : fclean all

.PHONY : all clean fclean re
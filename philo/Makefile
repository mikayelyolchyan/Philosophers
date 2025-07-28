NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I$(HDRS_DIR)

SRCS_DIR = sources/
UTILS_DIR = sources/utils/
HDRS_DIR = includes/headers/

SRCS = $(SRCS_DIR)main.c \
		$(UTILS_DIR)ft_atoi.c

HDRS = $(HDRS_DIR)philo.h

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

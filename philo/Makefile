NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(HDRS_DIR) -g3 -fsanitize=address

SRCS_DIR = sources/
UTILS_DIR = sources/utils/
HDRS_DIR = includes/headers/

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)alloc_init.c \
		$(SRCS_DIR)free.c \
		$(SRCS_DIR)create_join.c \
		$(UTILS_DIR)ft_atoi.c \
		$(UTILS_DIR)ft_putchar_fd.c \
		$(UTILS_DIR)ft_putendl_fd.c \
		$(UTILS_DIR)ft_putnbr_fd.c \
		$(UTILS_DIR)ft_putstr_fd.c \
		$(UTILS_DIR)ft_strlen.c

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

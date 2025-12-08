NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(HDRS_DIR)

SRCS_DIR = sources/
UTILS_DIR = sources/utils/
HDRS_DIR = includes/headers/

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)alloc_init.c \
		$(SRCS_DIR)one_philo.c \
		$(SRCS_DIR)free.c \
		$(SRCS_DIR)create_join.c \
		$(SRCS_DIR)philo_life.c \
		$(SRCS_DIR)philo_life_utils.c \
		$(SRCS_DIR)mutex_init.c \
		$(SRCS_DIR)mutex_destroy.c \
		$(SRCS_DIR)parse.c \
		$(SRCS_DIR)philo_print.c \
		$(SRCS_DIR)take_put_forks.c \
		$(SRCS_DIR)take_put_utils.c \
		$(SRCS_DIR)time_control.c \
		$(SRCS_DIR)time.c \
		$(SRCS_DIR)death_monitor.c \
		$(UTILS_DIR)ft_atoi.c \
		$(UTILS_DIR)ft_putchar_fd.c \
		$(UTILS_DIR)ft_putendl_fd.c \
		$(UTILS_DIR)ft_putnbr_fd.c \
		$(UTILS_DIR)ft_putstr_fd.c \
		$(UTILS_DIR)ft_strlen.c \
		$(UTILS_DIR)ft_strncmp.c

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

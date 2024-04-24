CC= cc
CFLAGS= -Wall -Wextra #-fsanitize=address #-Werror
NAME= pipex
CFILES = ft_syscalls.c  pipex.c pipex_errors.c pipex_utils.c ft_split.c ft_str_utils.c ft_str_utils_extra.c 
OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

.SECONDARY: $(OFILES)
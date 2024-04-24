CC= cc
CFLAGS= -Wall -Wextra #-fsanitize=address -Werror
NAME= pipex
BONUS = pipex_bonus
CFILES = ft_syscalls.c  pipex.c pipex_errors.c pipex_utils.c ft_split.c ft_str_utils.c ft_str_utils_extra.c execute_commands.c
BNSCFILES = ft_syscalls.c  pipex_bonus.c pipex_errors.c pipex_utils.c ft_split.c ft_str_utils.c ft_str_utils_extra.c execute_commands_bonus.c
OFILES = $(CFILES:.c=.o)
BNSOFILES = $(BNSCFILES:.c=.o)

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
$(BONUS): $(BNSOFILES)
	$(CC) $(CFLAGS) $(BNSOFILES) -o $(BONUS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)
	rm -rf $(BNSOFILES)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re

.SECONDARY: $(OFILES)
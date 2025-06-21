GREEN = \033[32m
RESET = \033[0m
UNDER = \033[4m
BY = By: $(UNDER)$(GREEN)sael-kha®️$(RESET) && $(UNDER)$(GREEN)imatouil®️$(RESET)

MINI = "$(GREEN)\
+==================================================+\\n\
||      __  __ _       _     _          _ _       ||\n\
||     |  \\/  (_)_ __ (_)___| |__   ___| | |      ||\n\
||     | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |      ||\n\
||     | |  | | | | | | \\__ \\ | | |  __/ | |      ||\n\
||     |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|      ||\n\
+==================================================+\n\
$(RESET)====>>                    $(BY)"




CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(HOME)/mylibs/readline/include
READLINE_LIB = -L$(HOME)/mylibs/readline/lib -lreadline
LIBFT = ./ft_libft/libft.a
NAME = minishell

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(GREEN)Futur is loading...$(RESET)"
	@$(MAKE) -C ./ft_libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -o $(NAME)
	@echo $(MINI)
	@echo "$(GREEN)Enjoy !$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C ./ft_libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./ft_libft fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
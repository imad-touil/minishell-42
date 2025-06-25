CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(HOME)/mylibs/readline/include
READLINE_LIB = -L$(HOME)/mylibs/readline/lib -lreadline
LIBFT = ./ft_libft/libft.a
NAME = minishell

SRCS =	builts0.c		ft_env.c			ft_pwd.c	mk_token_tools.c \
		check_sintax.c	ft_envariements.c	ft_setenv.c mk_token_tools_2.c\
		execute.c		ft_exit.c			ft_unset.c	parc_token.c\
		execute_tools.c ft_export.c			main.c		parc_token_tools.c\
		f_norminette.c	ft_get_env.c		signals.c	mk_token.c\
		ft_cd.c			ft_give_env.c		ft_echo.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C ./ft_libft

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -o $(NAME)

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
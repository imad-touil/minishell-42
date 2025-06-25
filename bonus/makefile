CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_INC = -I$(HOME)/mylibs/readline/include
READLINE_LIB = -L$(HOME)/mylibs/readline/lib -lreadline
LIBFT = ./ft_libft/libft.a
NAME = minishell_bonus

SRCS =	builts0_bonus.c			ft_env_bonus.c			ft_pwd_bonus.c		mk_token_tools_bonus.c \
		check_sintax_bonus.c	ft_envariements_bonus.c	ft_setenv_bonus.c	mk_token_tools_2_bonus.c\
		execute_bonus.c			ft_exit_bonus.c			ft_unset_bonus.c	parc_token_bonus.c\
		execute_tools_bonus.c 	ft_export_bonus.c		main_bonus.c		parc_token_tools_bonus.c\
		f_norminette_bonus.c	ft_get_env_bonus.c		signals_bonus.c		mk_token_bonus.c\
		ft_cd_bonus.c			ft_give_env_bonus.c		ft_echo_bonus.c	
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./ft_libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./ft_libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./ft_libft fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
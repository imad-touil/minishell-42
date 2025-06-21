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

all:
	@echo "$(GREEN)Futur is loading...$(RESET)"
	@$(MAKE) -C ./mandatory
	@mv ./mandatory/minishell .
	@echo $(MINI)
	@echo "$(GREEN)Enjoy !$(RESET)"

bonus:
	@$(MAKE) -C ./bonus
	@mv ./bonus/minishell_bonus .

clean:
	@$(MAKE) -C ./mandatory clean

clean_bonus:
	@$(MAKE) -C ./bonus clean
	@rm -f minishell_bonus
	@rm -f minishell

fclean: clean
	@$(MAKE) -C ./mandatory fclean
	@rm -rf minishell

fclean_bonus: clean_bonus
	@$(MAKE) -C ./bonus fclean

re: fclean all

mk: all clean
	@./minishell

norm:
	@norminette

re_bonus: fclean_bonus bonus

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re re_bonus norm mk

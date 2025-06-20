all:
	$(MAKE) -C ./mandatory
	mv ./mandatory/minishell .

bonus:
	$(MAKE) -C ./bonus
	mv ./bonus/minishell_bonus .

clean:
	$(MAKE) -C ./mandatory clean
	rm -f minishell

clean_bonus:
	$(MAKE) -C ./bonus clean
	rm -f minishell_bonus

fclean: clean
	$(MAKE) -C ./mandatory fclean

fclean_bonus: clean_bonus
	$(MAKE) -C ./bonus fclean

re: fclean all

mk: all clean
	./minishell
norm:
	norminette
re_bonus: fclean_bonus bonus

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re re_bonus
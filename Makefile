SRCS = mshell.c syntax_check/syntax_are_you_good.c syntax_check/syntax_quotes.c syntax_check/syntax_check_sequence.c check_utils/check_some_utills.c ft_strcmp.c init/init_cmds.c\
		parser/parse_dollar.c parser/parse_exchange_dollar.c heredoc/heredoc_fucking.c heredoc/heredoc_exchange.c get_next_line.c parser/parse_dollar_if_next_quotes.c\
		parser/parse_find_word.c check_rdrct_files.c init/init_prog_name.c init/init_prog_args.c init/init_prog_way.c check_utils/check_build_func.c heredoc/heredoc_get_params.c\
		mshell_utills.c go_execute.c utills_history_list.c check_utils/check_rdrct_utils.c env_update_params.c utils_cd.c utils_env_list.c utils.c\
		one_cmd/one_cmd_exec_our_func.c  one_cmd/one_cmd_exec_cd.c one_cmd/one_cmd_exec_echo.c one_cmd/one_cmd_exec_env.c one_cmd/one_cmd_exec_export.c one_cmd/one_cmd_exec_unset.c\
		del_matrix.c one_cmd/one_cmd_exec_exit.c one_cmd/one_cmd_exec_pwd.c one_cmd/one_cmd.c one_cmd/one_cmd_exec_history.c signal_on.c\
		many_cmd/many_cmds.c many_cmd/many_cmd_exec_our_func.c many_cmd/many_cmd_exec_echo.c many_cmd/many_cmd_exec_cd.c many_cmd/many_cmd_exec_exit.c many_cmd/many_cmd_exec_env.c many_cmd/many_cmd_exec_export.c\
		many_cmd/many_cmd_exec_unset.c many_cmd/many_cmd_exec_pwd.c many_cmd/many_cmd_exec_history.c

OBJS = $(SRCS:%.c=%.o)

HEADER = shell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

LIB = libft/libft.a

READLINE = -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.2/lib/

RM = rm -f

all		:		$(NAME)

$(NAME)	:		$(OBJS)
			$(CC)  $(FLAGS) -I $(HEADER) $(READLINE) $(OBJS) $(LIB) -o $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	:		clean
	$(RM) $(NAME)

re		:	fclean all

readline	:
				brew install readline
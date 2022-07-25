#ifndef SHELL_LIB_H
# define SHELL_LIB_H
/**
STANDART LIBS
**/
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
/**
MACROSI
**/
# define KEY 0
# define VALUE 1
# define EQUAL 0
# define EMPTY 0
# define FAIL -1
# define NEWLINEFLAG 1
# define INVALID 1

/**
HISTORY LIST
**/
typedef struct s_hist
{
	int		cmd_num;
	char	*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}	t_hist;

/**
ENV ONE LIST
**/
typedef struct t_node
{
	char			*key;
	char			*value;
	struct t_node	*next;
	struct t_node	*prev;
}	t_node;

/**
PO SUTI UKAZATEL NA PERVIY I POSLEDNIY LISTI
(NO TIPA V ODNOY SCTUCTURE, HZ, UDOBNO)
**/
typedef struct t_env
{
	int		size;
	t_node	*head;
	t_node	*tail;
}	t_env;

/**
ARGUMENTI PROGRAMMOK
(NAPRIMER; CAT, LS, I TAK DALEE)
**/
typedef struct s_prog
{
	char	*prog_name;
	char	*prog_way;
	char	**prog_args;
}	t_prog;

/**
ARGUMENTI LOOGICHESKOY OPERACII
(VSE COMANDI CHEREZ PIPE DO ZNACHKOV '&&', '||', NU ILI DO KONCA STROKI)
**/
typedef struct s_logic
{
	int		prog_build;
	int		left_pipe;
	int		right_pipe;
	int		fd_out;
	int		fd_in;
	char	*command;
	int		pipex[2];
	t_prog	*cmd_args;
}	t_logic;

/**
NU PROSTO VSE DANNIE NASHEY PROGI
**/
typedef struct s_evrything
{
	char	**maybe;
	char	*runner;
	char	*end;
	char	*start;
	char	*str;
	char	*line;
	char	*input_str;
	char	tmp;
	int		*pid;
	int		i;
	int		n;
	int		heredoc_nbr;
	char	**heredoc_names;
	int		*pipe;
	t_logic	*lgc;
	t_env	our_env;
	t_hist	*history_list;
}	t_evrything;

/**
CHISTO STRUCTURA DLYA ODNOY FUNCII, NADO BILO VSE UKAZATELI ZAPIHAT ;(
**/
typedef struct s_word
{
	char	*join1;
	char	*runner;
	char	*join2;
	char	*tmp1;
	char	*tmp2;
	char	*new_str;
	char	*helper;
}	t_word;

/**
STATUS PROCESSA POSLE EGO ZAVERSHENIYA
(SUCCESS OR NOT, PO SUTI)
**/
int	g_status;

/**
OPERATIONS WITH LISTS + FUNKCIYA SRAVNENIYA STROK
**/
void	init_env_list(t_env *env);
t_env	copy_env(char **env);
t_node	*find_node_by_key(char *key, t_env *env_list);
void	add_new_env_node(t_env *env_list, char *key, char *value);
char	**list_to_array(t_env *env_list);
int		ft_strcmp(const char *s1, const char *s2);
/**
NNU TAMM DALSHE VSE OSTLNOE, LAN POKA YA SPAT POSHEL
**/
int		syntax_are_you_good(char *line);
char	*syntax_quotes(char *runner);
char	*syntax_left_rdrct(char *runner);
char	*syntax_right_rdrct(char *runner);
char	*syntax_logic_and(char *runner);
char	*syntax_logic_or(char *runner);
char	*syntax_pipe(char *runner);
int		check_symbol_not_in_quotes(char *symbol);
int		check_split_symbol(char *symbol);
int		check_output_file(char *name, int nbr_rdrct, int n);
int		check_rdrct_files(char	*command, int *fd_out, int *fd_in, int n);
int		check_in_out_file(char *name, int *fd_in, int n);
int		check_input_file(char *name, int *fd_in, int n);
int		check_build_func(char *prog_name);
int		check_logic_and_or(char *str);
int		check_slash_in_name(char *name);
int		check_way_build_func(char *way);

int		init_cmds(t_evrything *all);
char	*init_prog_name(char *command);
char	**init_prog_args(char *command);
char	*init_prog_way(char *prog_name, t_node *head);
char	**init_find_rdrct_arg(char *command, char **prog_args, int num_args);
void	init_left_right_pipes_fd(t_evrything *all);
void	move_str_pointer(t_evrything *all);

void	many_cmds(t_evrything *all);
void	many_cmd_exec_our_func(t_evrything *all);
void	many_cmd_exec_echo(char **args);
void	many_cmd_exec_cd(char **args, t_env *env_list);
int		many_cmd_exec_env(char **args, t_env *env_list);
void	many_cmd_exec_exit(char **args);
void	many_cmd_exec_export(char **args, t_env *env_list);
void	many_cmd_exec_unset(char **args, t_env *env_list);
int		many_cmd_exec_history(t_hist *history_list, char **args);
void	many_cmd_exec_pwd();
void	go_execute(t_evrything *all);

char	*parse_dollar(char *command, t_env our_env);
char	*digit_dollar(char *exchange, char *runner);
char	*idi_v_zad(char *exchange, char *runner);
char	*dollar_vopros(char *exchange, char *runner);
char	*good_arg_value(char *exchange, char *runner, t_env our_env);
char	*parse_dollar_if_next_quotes(char *exchange, char *runner);
char	*parse_find_word(char *start_symbol);

void	heredoc_fucking(t_evrything *all);
char	*heredoc_exchange(char *here_doc, int i, t_evrything *all);
int		heredoc_diff_nbr(char *str);
char	**heredoc_get_names(int nbr_diff_heredoc);

char	*get_next_line(int fd);
void	del_matrix(char **mtrx);
void	env_update_params(t_env *our_env);
void	free_inited_params(t_evrything *all);
t_hist	*new_history_list(char *str_input);
t_hist	*add_new_history_list(t_hist *begin, char *str_input);
void	ctrl_c(int sig);
void	ctrl_slash(int sig);
void	free_heredocs(t_evrything *all);
void	signals_go(t_evrything *all);

void	one_cmd_exec_our_func(t_evrything *all);
void	one_cmd_exec_echo(char **args);
int		one_cmd_exec_env(char **args, t_env *env_list);
void	one_cmd_exec_unset(char **args, t_env *env_list);
void	one_cmd_exec_export(char **args, t_env *env_list);
void	one_cmd_exec_cd(char **args, t_env *env_list);
void	one_cmd_exec_exit(char **args);
void	one_cmd_exec_pwd();
int		one_cmd_exec_history(t_hist *history_list, char **args);
void	one_cmd(t_evrything *all);

int		is_all_chars_valid(char *str);
char	**split_by_first_occur(char	const	*s, char c);
void	ft_perror(int count, ...);
void	get_paths(char ***oldpwd, char ***pwd, char ***home, t_env *list);
void	refresh_wd_paths(char **oldpwd, char **pwd);

#endif
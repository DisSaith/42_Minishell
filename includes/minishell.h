/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:37:21 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/10 16:39:53 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

# include <signal.h>

# include <dirent.h>

# define YES 1
# define NO 0
# define OUT 1
# define IN 0
# define CTRL_D -1

typedef struct s_expander
{
	size_t	i;
	size_t	start;
	char	quote;
}			t_expander;

typedef enum e_tok_type
{
	WORD,
	PIPE,
	HERE_IN,
	HERE_OUT,
	DELIMITER,
	APPEND,
}		t_tok_type;

typedef enum e_tok_state
{
	GENERAL,
	IN_SQUOTE,
	IN_DQUOTE,
}		t_tok_state;

typedef struct s_token
{
	char			*str;
	t_tok_type		type;
	t_tok_state		state;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**cmd_args;
	int				in;
	int				out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_cmd			*current;
	t_env			*env;
	pid_t			*pid;
	char			**envp;
	char			*prompt;
	char			*delimiter;
	char			*heredoc;
	size_t			exit_status;
	int				pipefd[2];
	int				savefd[2];
	int				heredocfd;
	int				fd_read;
	int				nbr_heredocs;
	int				nbr_cmds;
	int				started;
}					t_shell;

//main.c
void		prepare_shell(t_shell *shell, char *envp[]);
void		init_before_start(t_shell *shell, char **av);
int			main(int ac, char **av, char *envp[]);

//***************INPUTS***************/
//
//get_inputs.c
int			count_words(char *str, char c);
char		*get_pwd(char *path, int count);
char		*get_prompt(void);
int			get_inputs(t_shell *shell);
//utils_token.c
int			is_redirection(t_token *token);
int			is_quoted(char *input, size_t idx);
int			is_separator(char c, int quote);
int			error_syntax_token(char *token);
int			check_syntax_token(t_token *list);
//tokenizer_inputs.c
size_t		strlen_token(char *input, size_t idx);
t_tok_type	get_type_token(char *str);
t_tok_state	get_state_token(char c, int quoted);
t_token		*tokenizer(t_shell *shell, size_t i, char *input, t_token **list);
//list_token.c
void		free_list_token(t_token **list);
size_t		list_add_back_token(t_token **list, t_token *new_elem,
				char *input, int idx);
t_token		*create_one_token(t_shell *shell, char *input, size_t idx);
//list_cmd.c
void		close_fd_cmd(t_cmd *cmd);
void		free_list_cmd(t_cmd **list);
void		list_add_back_cmd(t_cmd **list, t_cmd *new_elem);
t_cmd		*create_one_cmd(t_shell *shell, t_token *start_cmd,
				size_t nbr_args);
//redirection.c
void		error_open(t_shell *shell, char *filename);
int			open_file_cmd(t_shell *shell, t_token *current,
				int fd, int is_next);
char		*get_filename_heredoc(t_shell *shell, int situation);
int			get_redirection_cmd(t_shell *shell, t_token *current,
				int *in, int *out);
//heredoc.c
int			return_fd_heredoc(t_shell *shell);
void		warning_message_heredoc(t_shell *shell, char *rl,
				int fd, char *expanded);
void		heredoc_quoted(t_shell *shell, char *delimiter,
				int fd, int token_state);
void		heredoc_not_quoted(t_shell *shell, char *delimiter, int fd);
int			handle_heredoc(t_shell *shell, t_token *current, int fd);
//expander.c
char		*get_env_node_content(t_shell *shell, t_env *env, char *name);
char		*get_env_content_nospaces(t_shell *shell, t_env *env, char *name);
char		*check_if_is_var_env(t_shell *shell, char *str,
				size_t *i, int quoted);
char		*expander2(t_shell *shell, char *str, char *cmd_arg, char *tmp);
char		*expander(t_shell *shell, char *str);
//utils_expander.c
char		*ft_strjoin_expander(char *s1, char *s2);
char		*ft_strdup_nospaces(char *str);
char		*protect_spaces(char *str);
void		init_struct_expander(t_expander *x);
int			is_var_char(char c);
//parser_inputs.c
int			count_nbr_cmds(t_shell *shell);
size_t		get_nbr_args_one_cmd(t_token *start_cmd, size_t count);
char		*rest_sp(char *str);
int			fill_cmd_args(t_token *start_cmd, char **cmd_args);
t_cmd		*parsing(t_token *list, t_shell *shell);

/***************EXEC_CMDS***************/
//
//exec_pipe.c
void		proc_cmd_multi_pipe2(int i, t_shell *shell, t_cmd *cmd);
int			proc_cmd_multi_pipe1(t_shell *shell);
void		waitpid_processes(t_shell *shell, int nbr_cmds);
//exec_one_cmd.c
void		execute_one_cmd(t_shell *shell, t_cmd *cmd);
int			exec_builtin_cmd(t_shell *shell, t_cmd *cmd, int pipe);
int			child_process(t_shell *shell, t_cmd *cmd, int index, int pipe);
int			builtin_process(t_shell *shell, t_cmd *cmd);
int			process_cmd(t_shell *shell);
//redirection_for_exec.c
void		redirection_infile(t_shell *shell, t_cmd *cmd);
void		redirection_outfile(t_shell *shell, t_cmd *cmd, int is_last);
int			redirection_fd(t_shell *shell, t_cmd *cmd, int is_last);
//utils_exec_cmds.c
char		*find_path(char *envp[]);
char		*return_path_cmd(char *envp[], char *cmd);
void		prepare_single_cmd(t_shell *shell);

/***************UTILITIES***************/
//
//errors.c
void		error_exit(char *error, t_shell *shell);
void		error_builtin(char *cmd, char *arg);
void		error_export(char *args);
//errors_exec.c
void		error_exit_wrong_path(char *cmd_path, t_shell *shell, t_cmd *cmd);
void		error_exit_execve(char *cmd_path, t_shell *shell, t_cmd *cmd);
void		error_exit_execve_path(char *cmd_path, t_shell *shell, t_cmd *cmd);
//free.c
void		*free_tab_tab(char **tab);
void		*free_str(char *str);
void		free_all(t_shell *shell);
void		free_for_cd(char *pwd, char *path, char *tmp);
void		free_heredoc(t_shell *shell, char *expanded, char *rl);
//utils_minishell.c
t_shell		*get_shell_ptr(t_shell *ptr);
char		*strjoin_minishell(char *s1, char *s2, size_t n);
char		*remove_quotes2(char *str, size_t i, size_t j, char *new_str);
char		*remove_quotes(char *str, size_t i, size_t j);
void		close_all(t_shell *shell);

/*****************SIGNAL******************/
//
//signal_minishell.c
int			set_signal_capture(void);
void		sigint_handler(int signal);
void		sigint_signal_ignore(void);
void		sigint_signal_action(void);
void		set_signal_exec(void);
//signal_heredoc.c
void		sigint_handler_heredoc(int signal);
void		set_signal_heredoc(void);

/*****************BUILT-IN******************/
//
//exit.c
long long	check_long_long_limits(char *arg);
int			get_exit_status(char *arg, int argc, t_shell *shell);
void		perror_ft_exit(t_shell *shell, t_cmd *cmd, int pipe);
size_t		ft_exit(t_shell *shell, t_cmd *cmd, int pipe);
//echo.c
int			check_flag_echo(char *flag);
int			execute_echo(t_cmd *cmd, int i);
int			echo(t_cmd *cmd);
//cd.c
int			change_directory(t_cmd *cmd, int pipe);
//env.c
t_env		*ft_env_lstnew(char *str);
int			ft_init_env(t_shell *shell, char **envp, t_env **env);
int			ft_env(t_env *env, t_cmd *cmd);
char		**ft_env_to_tab(t_env *env);
void		ft_env_lstadd_back(t_env **env, t_env *new_node);
//utils_env.c
int			ft_env_size(t_env *env);
int			ft_append_env_node(t_env **env, t_env **last, char *str);
void		free_env(t_shell *shell, t_env **env);
int			ft_is_valid_identifier(char *name);
//utils_env_empty.c
void		ft_update_underscore(t_shell *shell, char *value);
int			ft_empty_env(t_shell *shell, t_env **env);
//export.c
char		**export_to_tab(t_env *env);
char		*format_export_str(t_env *node);
int			ft_export(t_env **env, char **args);
int			ft_fill_export(t_env **env, char *str);
int			ft_update_env_node(t_env *env, char *str);
//utils_export.c
char		*ft_str_surround(char *str, char c);
int			export_size(t_env *env);
void		print_export(char **tab);
void		sorted_env(t_env *env);
t_env		*ft_get_env_node(t_env *env, char *name);
//unset.c
void		ft_free_node(t_env *node);
int			ft_unset_var(t_env **env, char *str);
int			ft_unset(t_env **env, char **argv);
//pwd.c
int			ft_pwd(void);
//utils_built_in.c
int			is_builtin_cmd(char *str);
int			is_good_arg(char *arg);
int			get_nbr_args_cmd(t_cmd *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:34:52 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/07 16:48:23 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Counts the number of words based on char c for get_inputs function
*/
int	count_words(char *str, char c)
{
	int	i;
	int	count;
	int	in_word;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	in_word = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

/*
//Get the pwd (absolute path of the current position) for get_prompt function
*/
char	*get_pwd(char *path, int count)
{
	char	*pwd;
	int		i;
	int		j;

	if (!path)
		return (NULL);
	i = 0;
	while (path && path[i] && count != 3)
	{
		if (path[i] == '/')
			count++;
		i++;
	}
	if (count != 3)
		return (path);
	i--;
	count = ft_strlen(&path[i]);
	pwd = malloc(sizeof(char) * (count + 1));
	if (!pwd)
		return (NULL);
	j = 0;
	while (j <= count)
		pwd[j++] = path[i++];
	return (free(path), pwd);
}

/*
//Create and get the prompt for minishell (similar to BASH version used by 42)
*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	char	*tmp;
	int		count;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	count = count_words(tmp, '/');
	if (count == 2)
	{
		prompt = ft_strjoin(getenv("USER"), ":~$ ");
		free(tmp);
	}
	else
	{
		pwd = get_pwd(tmp, 0);
		prompt = ft_strjoin(getenv("USER"), ":~");
		tmp = ft_strjoin_gnl(prompt, pwd);
		free(pwd);
		prompt = ft_strjoin_gnl(tmp, "$ ");
	}
	return (prompt);
}

/*
//Gets the input of the user then tokenize and parse it
*/
int	get_inputs(t_shell *shell)
{
	char	*rl;

	if (!shell)
		return (-1);
	shell->prompt = get_prompt();
	if (!shell->prompt)
		return (0);
	rl = readline(shell->prompt);
	if (!rl)
		return (free(rl), free(shell->prompt), CTRL_D);
	if (rl[0] == '\0')
		return (free(rl), free(shell->prompt), 0);
	add_history(rl);
	shell->tokens = tokenizer(shell, 0, rl, &shell->tokens);
	if (!shell->tokens)
		return (free(rl), free(shell->prompt), 0);
	shell->cmds = parsing(shell->tokens, shell);
	if (!shell->cmds)
		return (free(rl), free(shell->prompt),
			free_list_token(&shell->tokens), 0);
	shell->nbr_cmds = count_nbr_cmds(shell);
	return (free(rl), free(shell->prompt), free_list_token(&shell->tokens), 1);
}

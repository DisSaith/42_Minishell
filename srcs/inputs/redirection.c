/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/03/09 15:48:58 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Error message if open failed
*/
void	error_open(t_shell *shell, char *filename)
{
	if (!filename || shell->exit_status == 130)
		return ;
	write(2, "minishell: ", 11);
	perror(filename);
	shell->exit_status = 1;
}

/*
//Return the good filename to open a temp file for a heredoc
*/
char	*get_filename_heredoc(t_shell *shell, int situation)
{
	char	*heredoc;

	heredoc = ft_strdup(".heredoc_tmp");
	if (!heredoc)
		return (NULL);
	heredoc = ft_strjoin_expander(heredoc, ft_itoa(shell->nbr_heredocs));
	if (!heredoc)
		return (NULL);
	if (situation == 1)
		shell->nbr_heredocs++;
	else
		shell->nbr_heredocs--;
	return (heredoc);
}

/*
//Open/close the file and return the fd, -1 if error, -2 for pipe
*/
int	open_file_cmd(t_shell *shell, t_token *current, int fd, int is_next)
{
	if (!current->str || current->str[0] == '\0')
		return (-1);
	if (fd > 2)
		close(fd);
	if (is_next == HERE_IN && current->type == WORD)
		fd = open(current->str, O_RDONLY);
	else if (is_next == HERE_OUT && current->type == WORD)
		fd = open(current->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is_next == APPEND && current->type == WORD)
		fd = open(current->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_next == DELIMITER && current->type == WORD)
	{
		shell->heredoc = get_filename_heredoc(shell, 1);
		shell->heredocfd = open(shell->heredoc,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		shell->heredocfd = handle_heredoc(shell, current, shell->heredocfd);
		shell->heredoc = free_str(shell->heredoc);
	}
	if (shell->heredocfd >= -1)
	{
		fd = shell->heredocfd;
		shell->heredocfd = -2;
	}
	return (fd);
}

/*
//Check and return the redirection (file descripter open) based on current token
*/
int	get_redirection_cmd(t_shell *shell, t_token *current, int *in, int *out)
{
	int	is_next;

	if (!current || !current->str)
		return (-1);
	is_next = 0;
	while (current && current->type != PIPE)
	{
		if (current->type != WORD && current->type != PIPE)
			is_next = current->type;
		if (current->type == WORD && is_next)
		{
			if (is_next == HERE_IN || is_next == DELIMITER)
				*in = open_file_cmd(shell, current, *in, is_next);
			else if (is_next == HERE_OUT || is_next == APPEND)
				*out = open_file_cmd(shell, current, *out, is_next);
			if (*in == -1 || *out == -1)
				return (error_open(shell, current->str), 0);
			is_next = 0;
		}
		current = current->next;
	}
	return (1);
}

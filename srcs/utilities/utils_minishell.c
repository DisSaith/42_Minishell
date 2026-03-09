/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:11:30 by acohaut           #+#    #+#             */
/*   Updated: 2026/03/09 09:01:11 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
//Function to get and store the pointer of the struct list shell
*/
t_shell	*get_shell_ptr(t_shell *ptr)
{
	static t_shell	*shell;

	if (ptr)
		shell = ptr;
	return (shell);
}

/*
//strjoin modified to retrieve the remainder of a string to exec a cmd
*/
char	*strjoin_minishell(char *s1, char *s2, size_t n)
{
	char	*result;
	size_t	i;
	size_t	j;

	if ((!s1 && !s2) || n <= 0)
		return (NULL);
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	while (s1 && s1[i] && (j < n))
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] && (j < n))
		result[j++] = s2[i++];
	result[j] = '\0';
	if (s1)
		free(s1);
	return (result);
}

/*
//Closes every fd opened 
*/
void	close_all(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmds;
	while (current)
	{
		if (current->in > 2)
			close(current->in);
		if (current->out > 2)
			close(current->out);
		current = current->next;
	}
	if (shell->pipefd[0] >= 0)
		close(shell->pipefd[0]);
	if (shell->pipefd[1] >= 0)
		close(shell->pipefd[1]);
	if (shell->fd_read >= 0)
		close(shell->fd_read);
}

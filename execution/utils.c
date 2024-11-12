/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:09:31 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/11 22:21:37 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_fds	*initiate_fds(void)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(1);
	fds->prev_pfd = -1;
	fds->pfd[0] = -1;
	fds->pfd[1] = -1;
	return (fds);
}

void	fds_dupping(t_fds *fds, t_command *cmd)
{
	if (fds->prev_pfd != -1)
	{
		dup2(fds->prev_pfd, cmd->fd_in);
		close(fds->prev_pfd);
	}
	if (cmd->next != NULL)
	{
		dup2(fds->pfd[1], cmd->fd_out);
		close(fds->pfd[1]);
	}
	close(fds->pfd[0]);
	close(fds->pfd[1]);
}

void	write_in_file(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
}

void	process_heredoc_line(t_command *cmd, char *line, int fd, t_data *data)
{
	t_tkn_lst	*tkn;
	char		*full_line;

	full_line = NULL;
	if (cmd->heredoc_delimiters->state == 1)
	{
		tkn = lexer(line);
		if (!tkn)
		{
			free_tkn_lst(&tkn);
			free(line);
			return ;
		}
		full_line = get_heredoc_content(tkn, data);
		write_in_file(full_line, fd);
		free(full_line);
		free_tkn_lst(&tkn);
	}
	else
		write_in_file(line, fd);
}

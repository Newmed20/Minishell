/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:19:00 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/10 07:22:54 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	dup_close_out(int fd , t_command *cmd)
{
	if (dup2(fd, cmd->fd_out) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

void	dup_close_in(int fd , t_command *cmd)
{
	if (dup2(fd, cmd->fd_in) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}


int	ft_output(t_redir *output_files , t_command *cmd)
{
	int	fd = -1;

	while (output_files)
	{
		if (fd != -1)
			close(fd);
		if (output_files->type == REDIR_OUT)
			fd = open(output_files->content, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			fd = open(output_files->content, O_WRONLY 
					| O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		output_files = output_files->next;
	}
	dup_close_out(fd , cmd);
	return (0);
}

int	ft_input(t_redir *input_file , t_command *cmd)
{
	int	fd = -1;

	while (input_file)
	{
		if (fd != -1)
			close(fd);
		fd = open(input_file->content, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		input_file = input_file->next;
	}
	dup_close_in(fd , cmd);
	return (0);
}

void ft_pipe_redirection(t_command *cmd)
{
	if (cmd->input_files)
		ft_input(cmd->input_files , cmd);
	if (cmd->oa_files)
		ft_output(cmd->oa_files , cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:01:59 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/10 19:55:45 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_child(t_fds *fds, t_command *cmd, t_data *data, char **env)
{
	signal (SIGINT, controlc_handler);
	signal(SIGQUIT, SIG_DFL);
	fds_dupping(fds, cmd);
	if (cmd->input_files || cmd->oa_files)
		ft_pipe_redirection(cmd , 1);
	if (ft_isbuitin(cmd->command))
	{
		execute_builtins(data, cmd);
		exit(g_exit_status);
	}
	if (cmd->command == NULL)
		exit(0);
	if (!cmd->full_path)
		exit(g_exit_status);
	if (cmd->full_path)
	{
		if (execve(cmd->full_path, cmd->args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	multiple_parent(t_fds *fds)
{
	if (fds->prev_pfd != -1)
		close(fds->prev_pfd);
	fds->prev_pfd = dup(fds->pfd[0]);
	close(fds->pfd[0]);
	close(fds->pfd[1]);
}

void	waiting(t_command *cmd)
{
	int	signum;

	while (cmd)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(cmd->pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
		{
			signum = WTERMSIG(g_exit_status);
			handle_signal_exit_status(signum);
		}
		cmd = cmd->next;
	}
	signal(SIGINT, controlc_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	before_child(t_fds *fds, t_command *cmd, t_data *data)
{
	if (cmd->next && pipe(fds->pfd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (cmd->heredoc_delimiters)
		ft_multiple_heredoc(cmd, data, 1);
	cmd->pid = fork();
}

void	execute_multiple(t_data *data, char **env)
{
	t_fds		*fds;
	t_command	*cmd;
	t_command	*head;
	int			original_stdin;

	original_stdin = dup(STDIN_FILENO);
	cmd = data->cmd;
	head = cmd;
	fds = initiate_fds();
	while (cmd)
	{
		before_child(fds, cmd, data);
		if (cmd->pid == 0)
			multiple_child(fds, cmd, data, env);
		else
			multiple_parent(fds);
		cmd = cmd->next;
	}
	waiting(head);
	free(fds);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
}

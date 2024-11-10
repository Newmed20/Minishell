/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 07:59:06 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/10 16:49:19 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc3(t_command *cmd, int fd, t_data *data)
{
	char	*line;

	line = readline(">");
	while (line && ft_strncmp(line, cmd->heredoc_delimiters->content,
			ft_strlen(cmd->heredoc_delimiters->content) + 1))
	{
		if (cmd->heredoc_delimiters->next == NULL && line)
			process_heredoc_line(cmd, line, fd, data);
		line = readline(">");
	}
	free_str(&line);
}

void	herdoc_child(int fd, t_command *cmd, t_data *data, int flag)
{
	if (flag == 0)
		signal (SIGINT, sig_one);
	else
		signal(SIGINT, sig_pipe);
	while (cmd->heredoc_delimiters)
	{
		unlink("/tmp/heredoc.txt");
		fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_heredoc3(cmd, fd, data);
		close(fd);
		cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
	}
	cmd->heredoc_delimiters = NULL;
	exit(g_exit_status);
}

void	ft_herdoc1(t_command *cmd, t_data *data, int flag)
{
	int		pid;
	int		fd;
	t_redir	*tmp;

	fd = 0;
	tmp = cmd->heredoc_delimiters;
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		herdoc_child(fd, cmd, data, flag);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
	}
}

void	ft_multiple_heredoc(t_command *cmd, t_data *data, int flag)
{
	if (!cmd->heredoc_delimiters)
		return ;
	if (g_exit_status == 24)
		return ;
	ft_herdoc1(cmd, data, flag);
	if (g_exit_status == 1)
		exit (1);
	cmd->fd_in = open("/tmp/heredoc.txt", O_RDONLY);
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(cmd->fd_in); 
	}
}

void	ft_heredoc(t_command *cmd, t_data *data, int flag)
{
	int	fd;

	if (!cmd->heredoc_delimiters)
		return ;
	if (g_exit_status == 24)
		return ;
	ft_herdoc1(cmd, data, flag);
	if (g_exit_status == 1)
		exit (1);
	fd = open("/tmp/heredoc.txt", O_RDONLY);
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(fd); 
	}
}

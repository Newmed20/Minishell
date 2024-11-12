/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:47:21 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/12 03:16:37 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

char	**ft_transform_env(t_env *env)
{
	char	**env_copy;
	int		i;
	char	*key;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		env_copy[i] = ft_strjoin(key, tmp->value);
		free(key);
		i++;
		tmp = tmp->next;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void	one_child(t_command *comand, t_data *data)
{
	char	**env;

	env = ft_transform_env(data->env_copy);
	signal(SIGQUIT, SIG_DFL);
	if (comand->heredoc_delimiters)
		ft_heredoc(comand, data, 0);
	signal (SIGINT, controlc_handler);
	if (comand->input_files || comand->oa_files)
		ft_redirection(comand, 0);
	if (comand->command == NULL)
		exit(g_exit_status);
	if (comand->full_path)
	{
		if (execve(comand->full_path, comand->args, env) == -1)
		{
			if (g_exit_status != 127 && g_exit_status != 126)
				perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	if (g_exit_status == 127 || g_exit_status == 126)
		exit (g_exit_status);
	else
		exit(EXIT_FAILURE);
}

void	one_parent(int pid)
{
	int	signum;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		signum = WTERMSIG(g_exit_status);
		sig_exit(signum);
	}
}

void	execute_one(t_data *data)
{
	t_command	*comand;
	int			pid;

	comand = data->cmd;
	if (ft_isbuitin(comand->command))
		execute_builtins(data, comand);
	else
	{
		pid = fork();
		if (pid == 0)
			one_child(comand, data);
		else
			one_parent(pid);
		signal(SIGINT, controlc_handler);
	}
}

int	ft_execute(t_data *data)
{
	t_command	*cmd;
	char		**env;

	env = ft_transform_env(data->env_copy);
	cmd = data->cmd;
	if (!cmd->pipe_out)
		execute_one(data);
	else
		execute_multiple(data, env);
	free_split(env);
	return (0);
}

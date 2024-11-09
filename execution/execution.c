/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:47:21 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/08 22:04:58 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status = 0;

char **ft_transform_env(t_env *env)
{
	char	**env_copy;
	int		i;
	char	*key;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	while(tmp)
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

int	execute_one(t_data *data , char **env )
{
	t_command *comand;
	int pid;
		
	comand = data->cmd;
	comand->fd_in = STDIN_FILENO;
	comand->fd_out = STDOUT_FILENO;
	if(ft_isbuitin(comand->command))
	{
		execute_builtins(data, comand);
		return (0);
	}
	pid = fork();
	if(pid == 0)
	{
		if(comand->heredoc_delimiters)
			ft_heredoc(comand, comand->heredoc_delimiters->state, data);
		if(comand->input_files || comand->oa_files)
			ft_redirection(comand);
		if(comand->full_path)
			execve(comand->full_path, comand->args, env);
		else
			exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &exit_status, 0);
	return (0);
}


int	ft_execute(t_data *data)
{
	t_command *cmd;
	char **env;

	env = ft_transform_env(data->env_copy);
	cmd = data->cmd;
	if(!cmd->pipe_out)
		execute_one(data , env);
	else
		execute_multiple(data , env);
	free_split(env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:01:59 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/06 16:43:31 by mjadid           ###   ########.fr       */
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


void execute_multiple(t_data *data, char **env)
{
    t_fds *fds;
	int status;
    t_command *cmd;
	t_command *head;
	int original_stdin;


	original_stdin = dup(STDIN_FILENO);

    cmd = data->cmd;
	head = cmd;
    fds = initiate_fds();
	fds->prev_pfd = -1;

    while (cmd)
    {
		data->cmd = cmd;
		 if (cmd->next && pipe(fds->pfd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        cmd->fd_in = STDIN_FILENO;
        cmd->fd_out = STDOUT_FILENO;
		// handler_signal(0);
		if (cmd->heredoc_delimiters)
			ft_multiple_heredoc(cmd, 0 , data);
		cmd->pid = fork();
		if (cmd->pid == 0)
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
			if (cmd->input_files || cmd->oa_files)
				ft_redirection(cmd);
			if(ft_isbuitin(cmd->command))
			{
				execute_builtins(data);
				exit(exit_status);
			} 
			if (cmd->command == NULL)
				exit(exit_status);
			if (cmd->command[0] == '\0')
			{
				perror("Command not found");
				exit(127);
			}
            env = ft_transform_env(data->env_copy);
            if(cmd->full_path)
            {
                if (execve(cmd->full_path , cmd->args,env) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }     
            }
		}
		else
		{
			if (fds->prev_pfd != -1)
				close(fds->prev_pfd);
			fds->prev_pfd = dup(fds->pfd[0]);
			close(fds->pfd[0]);
			close(fds->pfd[1]);
		}
        cmd = cmd->next;
    }
	cmd = head;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			// handler_signal(1);
			// if (WIFEXITED(status))
			// 	(*env)->exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
}



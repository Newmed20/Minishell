/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:51:55 by mjadid            #+#    #+#             */
/*   Updated: 2024/11/04 19:38:19 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_fds	*initiate_fds(void)
{
	
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(1);
	fds->prev_pfd[0] = -1;
	fds->prev_pfd[1] = -1;
	fds->pfd[0] = -1;
	fds->pfd[1] = -1;
	return (fds);
}
void     execute_multiple(t_data *data, char **env)
{

	t_fds *fds;
    t_command   *current ;
    int         pid;
	
	fds = initiate_fds();
	current = data->cmd;
    while (current)
    {
        if (current->next && pipe(fds->pfd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            if(current->heredoc_delimiters)
                ft_heredoc(current, current->heredoc_delimiters->state, data);
            if (current->next)
            {
                dup2(fds->pfd[1], STDOUT_FILENO);
                close(fds->pfd[1]);
            }
            if (current != data->cmd)
                dup2(fds->prev_pfd[0], STDIN_FILENO);

            close(fds->prev_pfd[0]);
            close(fds->prev_pfd[1]);
            close(fds->pfd[0]);
            if (current->input_files || current->oa_files)
                ft_redirection(current);
            execve(current->full_path, current->args, env);
            perror("execve");
            exit(1);
        }
        else
        {
            close(fds->prev_pfd[0]);
            close(fds->prev_pfd[1]);
            fds->prev_pfd[0] = fds->pfd[0];
            fds->prev_pfd[1] = fds->pfd[1];
            wait(NULL);
        }
        current = current->next;
    }
    close(fds->prev_pfd[0]);
    close(fds->prev_pfd[1]);
}

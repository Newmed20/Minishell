/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:47:21 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/11 00:02:17 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status = 0;

char **ft_transform_env(t_env *env)
{
    char **env_copy;
    int i;
    t_env *tmp;

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
        env_copy[i] = ft_strjoin(tmp->key, "=");
        env_copy[i] = ft_strjoin(env_copy[i], tmp->value);
        i++;
        tmp = tmp->next;
    }
    env_copy[i] = NULL;
    return (env_copy);
}

void ft_redirection(t_command *cmd)
{
    int fd;
    t_redir *redir;
    redir = cmd->input_files;
    while(redir)
    {
        fd = open(redir->content, O_RDONLY);
        dup2(fd, 0);
        close(fd);
        redir = redir->next;
    }
    redir = cmd->oa_files;
    while(redir)
    {
        if(redir->type == REDIR_OUT )
            fd = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if(redir->type == APPEND)
            fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);
        close(fd);
        redir = redir->next;
    }
}


void	write_in_file(char *line)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
	close(fd);
}

void	handler_heredoc(t_command *cmd)
{
	char	*line;
    
		while (cmd->heredoc_delimiters)
		{
			unlink("/tmp/heredoc.txt");
			line = readline(">");
			while (ft_strncmp(line, cmd->heredoc_delimiters->content, 
					ft_strlen(cmd->heredoc_delimiters->content) + 1))
			{
				if (cmd->heredoc_delimiters->next == NULL)
					write_in_file(line);
				add_history(line);
				free(line);
				line = readline(">");
			}
			free(line);
			cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
		}
		// exit(0);
}

void	ft_herdoc(t_command *cmd)
{
	int	fd;
	handler_heredoc(cmd);
	fd = open("/tmp/heredoc.txt",  O_RDWR);
	if (fd == -1)
		exit(0);
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

int     ft_execute(t_data *data)
{
    t_command *comand;
    char **env;
    
    comand = data->cmd; 
    env = ft_transform_env(data->env_copy);
    
    int pid;
    pid = fork();
    
    
    if(pid == 0)
    {
        if(comand->input_files || comand->oa_files)
            ft_redirection(comand);
        if(comand->heredoc_delimiters)
            ft_herdoc(comand);    
        execve(comand->full_path, comand->args, env);
    }
    
    else
        waitpid(pid, &exit_status, 0);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:47:21 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/09 22:09:56 by mjadid           ###   ########.fr       */
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
        else if(redir->type == DREDIR_OUT)
            fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);
        close(fd);
        redir = redir->next;
    }
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
        execve(comand->full_path, comand->args, env);
    }
    else
    {
        waitpid(pid, &exit_status, 0);
    }
    return (0);
}
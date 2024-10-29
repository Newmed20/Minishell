/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:19:00 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 07:19:28 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
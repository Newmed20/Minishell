/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:26:37 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/31 21:24:21 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h" 

int  ft_isbuitin(char *cmd)
{
    if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else
		return (0);
}

void  ft_builtins(t_data *data)
{
    t_command *cmd;
    
    cmd = data->cmd;
    if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = ft_cd(data, cmd);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = ft_echo(cmd);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = ft_pwd();
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_status = ft_env(data);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_status = ft_export(data);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		exit_status = ft_unset(data);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		ft_exit(data);
}

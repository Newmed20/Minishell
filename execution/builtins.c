/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 07:26:37 by mjadid            #+#    #+#             */
/*   Updated: 2024/10/29 09:15:46 by mjadid           ###   ########.fr       */
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
    t_env *env;
    
    cmd = data->cmd;
    env = data->env_copy;
    
    if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = ft_cd(cmd);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = ft_echo(cmd);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = ft_pwd();
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_status = ft_env(data);
	// else if (!ft_strncmp(cmd->command, "export", 7))
	// 	exit_status = ft_export(data);
	// else if (!ft_strncmp(cmd->command, "unset", 6))
	// 	exit_status = ft_unset(data);
	// else if (!ft_strncmp(cmd->command, "exit", 5))
	// 	ft_exit(data);
}

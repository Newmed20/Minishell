/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:47:26 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/12 01:19:36 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ifif2(t_command *cmd, t_data *data)
{
	if (cmd->command[0] == '.')
	{
		if (access(cmd->command, X_OK) != 0 && access(cmd->command, F_OK) == 0)
		{
			printf("minishell: %s: Permission denied\n", cmd->command);
			g_exit_status = 126;
		}
		else if (is_executable(cmd, cmd->command) == 0)
		{
			printf("minishell: %s: No such file or directory\n", cmd->command);
			g_exit_status = 127;
		}
	}
	else if (!ft_is_command(data, cmd, cmd->command)
		&& !ft_isbuitin(cmd->command))
	{
		printf("minishell: %s: command not found\n", cmd->command);
		g_exit_status = 127;
	}
}

void	ifif(t_command *cmd, t_data *data)
{
	if (!cmd->command && !cmd->vid)
		cmd->cmd_found = false;
	else if (is_direcotry(cmd->command)
		&& (cmd->command[0] == '/' || cmd->command[0] == '.'))
	{
		printf("minishell: %s: is a direcotry\n", cmd->command);
		g_exit_status = 126;
	}
	else if (cmd->command[0] == '/')
	{
		if (access(cmd->command, X_OK) == 0)
			cmd->full_path = ft_strdup(cmd->command);
		else if (access(cmd->command, F_OK) != 0)
		{
			printf("minishell: %s: No such file or directory\n", cmd->command);
			g_exit_status = 127;
		}
		else
		{
			printf("minishell: %s: Permission denied\n", cmd->command);
			g_exit_status = 126;
		}
	}
	else
		ifif2(cmd, data);
}

t_command	*create_command(t_data *data, t_command *cmd, t_token **token)
{
	char	*command;
	char	*full_command;

	command = NULL;
	full_command = NULL;
	if (!cmd->cmd_found)
	{
		if (!only_quotes(*token))
			cmd->vid = 1;
		get_string(token, data, &full_command, &command);
		cmd->command = command;
		cmd->cmd_found = true;
		if (cmd->command[0] == '\0' && cmd->vid)
		{
			g_exit_status = 127;
			return (printf("minishell: : command not found\n"), cmd);
		}
		else
			ifif(cmd, data);
	}
	fill_args(token, cmd, data);
	return (cmd);
}

void	_first_arg(t_command *cmd, char ***args)
{
	if (!cmd->command)
		return ;
	*args = malloc(sizeof(char *) * 2);
	if (!args)
		return ;
	(*args)[0] = ft_strdup(cmd->command);
	if (!(*args)[0])
		return ;
	(*args)[1] = NULL;
	cmd->args = *args;
	cmd->arg_count++;
}

void	tokens_loop(t_data *data, t_token **tmp, t_command **cmd)
{
	while (*tmp)
	{
		if ((*tmp)->type == WORD || (*tmp)->type == ENV 
			|| (*tmp)->state == IN_SQUOTE || (*tmp)->state == IN_DQUOTE
			|| (*tmp)->type == D_QUOTE || (*tmp)->type == S_QUOTE)
		{
			*cmd = create_command(data, *cmd, tmp);
			if (!*tmp)
				break ;
		}
		if (is_redir(*tmp))
		{
			handle_redirections_heredoc(tmp, *cmd, data);
			if (!*tmp)
				break ;
		}
		if ((*tmp)->type == PIPE_LINE)
		{
			lst_add_back(&data->cmd, *cmd);
			(*cmd)->pipe_out = 1;
			*cmd = init_command();
		}
		*tmp = (*tmp)->next;
	}
}
